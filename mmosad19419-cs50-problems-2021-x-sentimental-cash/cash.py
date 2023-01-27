import cs50

# Define Main Function


def main():
    while True:
        cent = cs50.get_float("Change owed: ")
        if cent >= 0.00:
            break

    # round Cent
    cent = round(cent * 100)

    # Calculate the number of quarters (25¢).
    q = int(cent / 25)
    cent -= q * 25

    # Calculate the number of dimes (10¢).
    d = int(cent / 10)
    cent -= d * 10

    # Calculate number of nickels (5¢).
    n = int(cent / 5)
    cent -= n * 5

    # Calculate number of pennies (1¢).
    p = int(cent / 1)
    cent -= p * 1

    # Total number of coins
    coins = q + d + n + p

    # Print the result
    print(f"{coins}")


if __name__ == "__main__":
    main()