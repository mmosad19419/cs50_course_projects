#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

//functions declarations
int count_l(string text);
int count_w(string text);
int count_s(string text);



int main(void)

{
//get the text input from the user
    string t = get_string("Text:");

//count the letters
    int letter = count_l(t);

//count the words
    int word = count_w(t);

// count the number of sentences
    int sentence = count_s(t);


// calculete L & S for the index equation
    double l = (letter * 100) / word;

    double s = (sentence * 100) / word;


//claculate the index & round it
    double index = 0.0588 * l - 0.296 * s - 15.8;

    index = round(index - .05);

    int grade = index;

//print the result
    if (grade < 1)
    {
        printf("Before Grade 1...\n");
    }
    else if (grade > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf(" Grade %i\n", grade);
    }  
}




//count the letters (function)
int count_l(string text)
{
    int l = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (isalpha(text[i]))
        {
            l++;
        }
    }
    return l;
}


//count the words (function)
int count_w(string text)
{
    int w = 1;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (text[i] == ' ')
        {
            w++;
        }
    }
    return w;
}

// count the number of sentences (function)
int count_s(string text)
{
    int s = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (text[i] == '.' || text[i] == '?' || text[i] == '!')
        {
            s++;
        }
    }
    return s;
}