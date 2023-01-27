#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>


// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};
char chart[] = { 'A', 'B', 'C', 'D', 'E','F','G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

int array_sum(int lenght, int array[]);
int compute_score(string word);

int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // TODO: Print the winner
    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }
    else if (score2 > score1)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }
}

//create compute score function
int compute_score(string word)
{
    // make all the string Uppercase
    for (int i = 0, n = strlen(word); i < n; i++)
    {
        word[i] = toupper(word[i]);
    }

    //Define the letter and call its value
    int sum = 0;
    int n = 0;

    //define the char & checking if it alphapet pr not
    for (int i = 0; i < strlen(word); i++)
    {
        if (isalpha(word[i]))
        {
            while (word[i] != chart[n] && word [i] != 0)
            {
                n++;
            }
            sum = sum + POINTS[n];
            n = 0;
        }
    }
    //return the score of th word
    return sum;
}