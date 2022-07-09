// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <strings.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

//Dictionary word counter
int counter = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    //Hash word
    int hashNumber = hash(word);
    //Set cursor to first item in linked list
    node *cursor = table[hashNumber];
    //Traverse linked list, looking for the word
    while (cursor != NULL)
    {
        if (strcasecmp(cursor->word, word) == 0)
        {
            return true;
        }
        cursor = cursor->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    return toupper(word[0]) - 'A';
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    //Open dictionary file
    FILE *dic = fopen(dictionary, "r");
    if (dic == NULL)
    {
        return false;
    }

    //Read strings from file one at a time
    char tmpWord[LENGTH +1];
    while (fscanf(dic,"%s",tmpWord) != EOF)
    {
        //Create a new node for each word
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return false;
        }
        strcpy(n->word,tmpWord);
        n->next = NULL;
        //Hash word to obtain a hash value
        int hashNumber = hash(tmpWord);
        //Insert node into hash table at that location
        if (table[hashNumber] == NULL)
        {
            table[hashNumber] = n;
        }
        else
        {
        n->next = table[hashNumber]->next;
        table[hashNumber]->next = n;
        }

        //global counter for words in my dictionary
        counter++;
    }
    fclose(dic);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return counter;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    node *cursor = NULL;
    node *tmp = NULL;
    for (int i = 0; i < N; i++)
    {
        cursor = table[i];

        while (cursor != NULL)
        {
            tmp = cursor;
            cursor = cursor->next;
            free(tmp);
        }
    }
    return true;
}
