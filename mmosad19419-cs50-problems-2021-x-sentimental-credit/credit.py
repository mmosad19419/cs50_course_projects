import cs50

# Define Main Function


def main():
    # Get the Number
    number = cs50.get_int("Number: ")

    # slice the credit card number into single digits
    digits = []
    i = 10
    l = 1
    while True:
        # Get the digits through mod operator
        n = int(number % i)
        d = int(n / l)
        # add the digit to the list
        digits.append(d)
        # Break condition
        if int(number / i) == 0:
            break
        # multiply the factors
        i *= 10
        l *= 10
    # multiply the digits by 2 and Sum the product digits
    sum = 0
    for i in range(1, len(digits), 2):
        product = digits[i] * 2
        # handle if the product contain 2 digits
        if product > 9:
            fdigit = int(product / 10)
            sdigit = int(product % 10)
            sum += fdigit + sdigit
        else:
            sum += product
    # add the rest of digits to sum
    for i in range(0, len(digits), 2):
        sum += digits[i]
    # print the result
    if int(sum % 10) == 0:
        if digits[len(digits) - 1] == 4 and 13 <= len(digits) >= 16:
            print("VISA")
        elif len(digits) == 16:
            print("MASTERCARD")
        elif len(digits) == 15:
            print("AMEX")
        else:
            print("INVALID")
    else:
        print("INVALID")


# Call main function
if __name__ == '__main__':
    main()