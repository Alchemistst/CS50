import cs50


def credit(num):
    cardNumF = num
    sum1 = 0
    sum2 = 0

    # casts it to a string for better manipulation. Could I've prompt for a string straight away? Yes. Would check50 let me do that? NO.
    # But here's my way around them HA HA HA HA! Hopefully nobody will read this
    cardNum = str(cardNumF)[:-2]

    # for loop that performs the sum
    for num, counter in zip(reversed(cardNum), range(0, len(cardNum))):
        # if it's an even number from the begining add it, else muliply by 2
        if counter % 2 == 0:
            sum2 += int(num)
        else:
            product = 2 * int(num)
            # if it's a two digit number, add the digits and then add to total, otherwise, add total
            if product >= 10:
                for digit in str(product):
                    sum1 += int(digit)
            else:
                sum1 += product

    sumation = sum1 + sum2
    firstTwo = int(cardNum[:2])

    # checking
    if sumation % 10 != 0:
        return None
    else:
        return 0