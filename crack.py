import crypt
import string
import sys


def main():
    # Check for correct usage
    if len(sys.argv) != 2:
        return 1

    password = sys.argv[1]
    salt = password[:2]
    match = False
    asciiAltered = [""]

    # create a list with alphabet
    for elements in list(string.ascii_letters):
        asciiAltered.append(elements)

    # list to store the combinations
    array = ["", "", "", "", ""]

    # sequence of for loops to iterate through the possible combinations
    for element0 in asciiAltered:
        array[0] = element0
        for element1 in asciiAltered:
            array[1] = element1
            for element2 in asciiAltered:
                array[2] = element2
                for element3 in asciiAltered:
                    array[3] = element3
                    asciiAltered = list(string.ascii_letters)
                    for element4 in list(string.ascii_letters):
                        array[4] = element4

                        # transform list into string nd encrypt
                        testerStr = "".join(array)
                        charsEncrypt = crypt.crypt(testerStr, salt)

                        # check for match
                        if password == charsEncrypt:
                            match = True
                            print(testerStr)
                            return 0

    return 1


if __name__ == "__main__":
    main()