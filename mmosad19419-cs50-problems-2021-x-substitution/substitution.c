#include <cs50.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>



char alphabet[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};


int main(int argc, string argv[])
{
    // checking the number of command line argumnet
    if (argc != 2)
    {
        printf("Usage : ./substitution KEY\n");
        return 1;
    }


    //checking that the key  is conating 26 characters
    if (strlen(argv[1]) != 26)
    {
        printf("Enter a valid KEY containing 26 characters\n");
        return 1;
    }


    //checking that all the key characters are alphabets
    for (int i = 0, n = strlen(argv[1]) ; i < n; i++)
    {
        if (isalpha(argv[1][i]) == 0)
        {
            printf(" KEY must ONLY containing alphabetic characters\n");
            return 1;
        }
    }

    //check if it contained each letter at least once and there is no repeat
    for (int i = 0, n = strlen(argv[1]) ; i < n; i++)
    {
        int a = -1;
        do
        {
            a++;
        }
        while (alphabet[i] !=  toupper(argv[1][a]) && a <= 27);

        if (a > 26)
        {
            printf("Enter a valid KEY containing all the 26 characters and no repeated characters\n");
            return 1;
        }
    }


    // geting the plain text from the user
    string ptext = get_string("Plain Text: ");

    //Detect the letter
    int n = 0;
    for (int i = 0; i < strlen(ptext); i++)
    {
        if (isalpha(ptext[i]))
        {
            while (toupper(ptext[i]) != alphabet[n] && ptext[i] != 0)
            {
                n++;
            }

            // cipher the text
            if (isupper(ptext[i]))
            {
                ptext[i] = toupper(argv[1][n]);
            }
            else
            {
                ptext[i] = tolower(argv[1][n]);
            }
            n = 0;
        }
    }

    //Print cipher text
    printf("ciphertext: %s\n", ptext);

    return 0;
}