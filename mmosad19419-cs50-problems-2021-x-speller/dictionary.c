// Implements a dictionary's functionality
#include <strings.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <ctype.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

typedef uint8_t BYTE;

int NUMBER = 0;

// Number of buckets in hash table
const unsigned int N = 50;

// Hash table
node *table[N + 1][LENGTH + 1];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    //hash the word
    int index = hash(word);
    int len = index % 100;
    int sum = index / 100;

    // create the search function of the linked list
    node *tmp = NULL;
    for (tmp = table[sum][len]; tmp != NULL; tmp = tmp->next)
    {
        if (strcasecmp(word, tmp->word) == 0)
        {
            return true;
        }
    }
    
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    //alocate space for the first 3 letters
    char chars[2];
    // store the word each character
    int i = -1;
    for (int l = 0; l  < 2; l++)
    {
        do
        {
            i++;
        }
        while (isalpha(*(word + i)) == 0 && i < strlen(word));

        chars[l] = toupper(*(word + i));
    }
    // Calculate the length of the string
    int len = strlen(word);
    //clalculate the sum of the first three letters
    int sum = (((int)chars[0] + (int)chars[1]) % 130);
    // concatenate the two number together
    char result[100];
    sprintf(result, "%d%d", sum, len);
    int hash = atoi(result);
    //return the hash
    return hash;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // open dictionery file
    FILE *d = fopen(dictionary, "r");
    if (d == NULL)
    {
        return false;
    }
    //create buffer to read from file
    char buffer[LENGTH + 1];
    //read from the file into the buffer
    while (fscanf(d, "%s", buffer) != EOF)
    {
        //create a node to store the word;
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return false;
        }
        // assign the value of the node
        strcpy(n->word, buffer);
        // insert the node into the linked list at table[index]
        //hash the word
        int index = hash(buffer);
        int len = index % 100;
        int sum = index / 100;
        // insert it
        n->next = table[sum][len];
        table[sum][len] = n;
        //increment the counter
        NUMBER ++;
    }
    //close the file
    fclose(d);
    return true; 
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return NUMBER;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // loop through the table
    for (int sum =  0; sum < (N + 1); sum++)
    {
        for (int len =  0; len < (LENGTH + 1); len++)
        {
            node *cursor = table[sum][len];
            node *tmp = cursor;
            while (cursor != NULL)
            {
                cursor = cursor->next;
                free(tmp);
                tmp = cursor;
            }
            free(cursor);
        }
    }
    return true;
}
