import cs50

# Prompt the user untel valid value is inputed
while True:
    height = cs50.get_int("Height: ")

    if height >= 0 and height <= 23:
        break

# Start of the row
for n in range(height, 0, -1):
    # print spaces
    for space in range(0, n - 1):
        print(" ", end="")
    # print blocks 2 times
    for times in range(0, 2):
        # print actual blocks
        for block in range(0, height - n + 1):
            print("#", end="")
        # print middle gap if is the first time, new line if the second
        if times == 0:
            print("  ", end="")
        else:
            print("")