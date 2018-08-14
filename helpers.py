from enum import Enum


class Operation(Enum):
    """Operations"""

    DELETED = 1
    INSERTED = 2
    SUBSTITUTED = 3

    def __str__(self):
        return str(self.name.lower())


table = [[]]


def distances(a, b):
    """Calculate edit distance from a to b"""

    global table

    # initialize 1st row and 1st colum
    table[0].append((0, None))

    for count in range(0, len(b)):
        table[0].append((count + 1, Operation.DELETED))

    for count in range(1, len(a) + 1):
        table.append([])
        table[count].append((count, Operation.INSERTED))

    # the real-deal algorithm for filling this bad boy table
    for element in range(1, len(a) + 1):
        calcDist(element, b, a[element - 1])

    matrix = table
    table = [[]]
    return matrix

# function that calculates distances and fills the table


def calcDist(i, string, letter):

    if len(string) > 1:
        calcDist(i, string[:-1], letter)

    step = 1

    # there are 3 options: a)deletion, b)insertion, c)substitution
    a = (table[i][len(string) - 1][0] + step, Operation.INSERTED.value)
    b = (table[i - 1][len(string)][0] + step, Operation.DELETED.value)

    if string[-1:] == letter:
        step = 0

    c = (table[i - 1][len(string) - 1][0] + step, Operation.SUBSTITUTED.value)

    # select the minimum of the three
    result = min(b, a, c)

    table[i].append((result[0], Operation(result[1])))
