#
import cs50

# Maximum Number of hieght
MAX = 8
# Minimium Number of hieght
MINI = 1

# Define Main Function
def main():
    # Get the hieght of the pyramids
    while True:
        h = cs50.get_int("highet: ")
        if h >= MINI and h <= MAX:
            break
    # Print the double Pyramid
    print_double_pyramid(h, 0)

# Defining print_double_pyramid function (Input: hieght, S "Space incrementor")


def print_double_pyramid(height, S):
    # recursive case
    if height > MINI:
        # Space increment
        S += 1
        print_double_pyramid(height-1, S)
        # printing current line
        # print space
        for i in range(S - 1):
            print(" ", end="")
        # print the first raw
        for i in range(height):
            print("#", end="")
        # print mediate space
        print("  ", end="")
        # print first raw
        for i in range(height):
            print("#", end="")
        print()

    # base case
    else:
        # print space
        for i in range(S):
            print(" ", end="")
        # print the first raw
        for i in range(MINI):
            print("#", end="")
        # print mediate space
        print("  ", end="")
        # print first raw
        for i in range(MINI):
            print("#")
        return S
    return

    if __name__ == "__main__":
        main()

