import os

from cs50 import SQL
from datetime import datetime
from pytz import timezone
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from jinja2 import Environment
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd
from credit import credit

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Ensure responses aren't cached


@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


# Custom filter
app.jinja_env.filters["usd"] = usd
app.jinja_env.filters["lookup"] = lookup

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    portfolio = db.execute(
        "SELECT SUM(amount_shares) AS shares, stock AS symbol FROM purchases WHERE user_id = :user_id GROUP BY stock", user_id=session["user_id"])

    quoteResult = {}
    cash = db.execute("SELECT cash FROM users WHERE id = :user_id", user_id=session["user_id"])[0]["cash"]
    total = []

    return render_template("index.html", portfolio=portfolio, quoteResult=quoteResult, cash=cash, total=total)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        if not request.form.get("symbol"):
            return apology("Symbol field can't be empty", 400)

        quoteResult = lookup(request.form.get("symbol"))

        """In case quote is not found"""
        if quoteResult == None:
            return apology("you must provide a valid stock symbol", 400)

        if not request.form.get("shares"):
            return apology("Shares field can't be empty", 400)

        if not request.form.get("shares").isnumeric():
            return apology("Enter a valid number of shares", 400)
        elif float(request.form.get("shares")) <= 0 or float(request.form.get("shares")) % 1 != 0:
            return apology("Enter a valid number of shares", 400)

        """calculate price"""
        quantity = request.form.get("shares")
        total = quoteResult["price"] * float(quantity)
        user_id = session["user_id"]
        current = db.execute("SELECT cash FROM users WHERE id = :user_id", user_id=user_id)[0]["cash"]

        if total > current:
            return apology("not enough cash pal!", 403)

        """if all good then input in the database the purchase"""
        db.execute("INSERT INTO purchases VALUES (:user_id, datetime('now'), :quantity, :priceps, :stock)",
                   user_id=user_id, quantity=quantity, priceps=quoteResult["price"], stock=quoteResult["symbol"])

        """Update cash"""
        current -= total
        db.execute("UPDATE users SET cash = :current WHERE id = :user_id", current=current, user_id=user_id)

        """Show notification and redirect"""
        flash("Bought!")
        return redirect("/")
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    history = db.execute(
        "SELECT date, amount_shares AS shares, priceps AS price, stock AS symbol FROM purchases WHERE user_id = :user_id", user_id=session["user_id"])

    return render_template("history.html", history=history)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":

        """In case empty request"""
        if not request.form.get("symbol"):
            return apology("you must provide a stock symbol", 400)

        quoteResult = lookup(request.form.get("symbol"))

        """In case quote is found and not found"""
        if quoteResult != None:
            quoteResult["price"] = usd(quoteResult["price"])
            return render_template("quoted.html", quoteResult=quoteResult)
        else:
            return apology("you must provide a valid stock symbol", 400)

    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    """Set behaviour for POST and GET requests on /register"""
    if request.method == "POST":

        """"Username and passwords requirements"""
        if not request.form.get("username"):
            return apology("must provide username", 400)

        elif len(db.execute("SELECT username FROM users WHERE username = :username", username=request.form.get("username"))) != 0:
            return apology("username already exists", 400)

        elif not request.form.get("password"):
            return apology("must provide password", 400)

        elif request.form.get("password") != request.form.get("confirmation"):
            return apology("passwords don't match", 400)

        """If we got here, means everything went all right with password and user, so lets hash and store in the database baby!"""
        db.execute("INSERT INTO users (username, hash) VALUES (:username, :hashPass)", username=request.form.get(
            "username"), hashPass=generate_password_hash(request.form.get("password"), method='pbkdf2:sha256', salt_length=8))
        return render_template("login.html")

    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    if request.method == "POST":

        if not request.form.get("symbol"):
            return apology("You must pick a stock value", 403)

        if len(db.execute("SELECT DISTINCT(stock) FROM purchases WHERE user_id = :user_id AND stock = :symbol", user_id=session["user_id"], symbol=request.form.get("symbol"))) == 0:
            return apology("You don't own selected stock", 403)

        """Ammount of shares for the requested stock"""
        amount_shares = db.execute("SELECT SUM(amount_shares) AS shares FROM purchases WHERE user_id = :user_id and stock = :symbol GROUP BY stock",
                                   user_id=session["user_id"], symbol=request.form.get("symbol"))[0]["shares"]
        """Amount of shares that the user wants to sell"""
        amount_sale = float(request.form.get("shares"))

        if amount_sale > amount_shares:
            return apology("Not enough shares", 400)

        """Amount of money we'll get from sale of the stock"""
        sale_price = amount_sale * lookup(request.form.get("symbol"))["price"]

        """Current amount of cash"""
        current = db.execute("SELECT cash FROM users WHERE id = :user_id", user_id=session["user_id"])[0]["cash"]

        total = current + sale_price

        """Insert transaction"""
        db.execute("INSERT INTO purchases VALUES (:user_id, datetime('now'), :quantity, :priceps, :stock)",
                   user_id=session["user_id"], quantity=-amount_sale, priceps=sale_price, stock=request.form.get("symbol"))
        """Update cash"""
        db.execute("UPDATE users SET cash = :current WHERE id = :user_id", current=total, user_id=session["user_id"])

        """Show notification and redirect"""
        flash("Sold!")
        return redirect("/")
    else:
        symbols = db.execute("SELECT DISTINCT(stock) FROM purchases WHERE user_id = :user_id", user_id=session["user_id"])
        return render_template("sell.html", symbols=symbols)


@app.route("/add_cash", methods=["GET", "POST"])
@login_required
def add_cash():
    """Add cash"""
    # Behavieour for POST, else, GET
    if request.method == "POST":

        if not request.form.get("card_num"):
            return apology("Card number field can't be empty", 400)
        if not request.form.get("amount"):
            return apology("Amount fild can't be empty", 400)

        if not request.form.get("card_num").isnumeric():
            return apology("Invalid card number", 400)
        elif credit(request.form.get("card_num")) != 0:
            return apology("Invalid card number", 400)

        """Update cash"""
        current = db.execute("SELECT cash FROM users WHERE id = :user_id", user_id=session["user_id"])[0]["cash"]
        total = current + float(request.form.get("amount"))
        db.execute("UPDATE users SET cash = :current WHERE id = :user_id", current=total, user_id=session["user_id"])

        amount = usd(float(request.form.get("amount")))

        flash(f"{amount} added!")
        return redirect("/")

    else:
        return render_template("add_cash.html")


def errorhandler(e):
    """Handle error"""
    return apology(e.name, e.code)


# listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
