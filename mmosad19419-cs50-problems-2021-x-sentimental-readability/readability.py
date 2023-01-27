import cs50

# define main function


def main():
    # Get Text from the user
    text = cs50.get_string("Text: ")

    # Count letters --> letters_c function
    letters = letters_c(text)

    # Count words --> words_c function
    words = words_c(text)

    # Count sentences --> sentences_c function
    sentences = sentences_c(text)

    # calculate l & s for index equ
    l = (letters * 100) / words
    s = (sentences * 100) / words

    # Calculate the index
    index = .0588 * l - .296 * s - 15.8
    # Calculate the grade
    grade = round(index)

    # Print the result
    if grade < 1:
        print("Before Grade 1...")
    elif grade > 16:
        print("Grade 16+")
    else:
        print("Grade {}".format(grade))


# Define letters count function


def letters_c(text):
    l = 0
    for i in range(len(text)):
        if text[i].isalpha():
            l += 1
    return l

# Define words count function


def words_c(text):
    w = 1
    for i in range(len(text)):
        if text[i] == " ":
            w += 1
    return w

# Define sentences count function


def sentences_c(text):
    s = 0
    for i in range(len(text)):
        if text[i] == '.' or text[i] == '?' or text[i] == '!':
            s += 1
    return s


if __name__ == "__main__":
    main()