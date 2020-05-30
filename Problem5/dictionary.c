// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <strings.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} 
node;

int word_counter = 0;

// Number of buckets in hash table
const unsigned int N = 25;

// Hash table
node *table[N];

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // get the hash from the word
    int bucket_number = hash(word);
    
    // point the first word at the hash table
    node *cursor = table[bucket_number];
    
    // compare two strings case-insensitively until get NULL
    while (cursor != NULL)
    {
        if (strcasecmp(word, cursor->word) == 0)
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
    // get the first letter in the word
    char first_letter = tolower(word[0]); 
    
    // get the bucket number from the first letter
    int bucket_number = (int) first_letter - 97;
    
    // return the bucket number
    return bucket_number;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // open dictionary file
    FILE *dic = fopen(dictionary, "r");
    if (dic == NULL)
    {
        unload();
        return false;
    }
    
    // create a buffer for a string
    char *buffer_word = malloc(sizeof(char) * (LENGTH + 1));
    
    // read strings from file
    while (fscanf(dic, "%s", buffer_word) != EOF)
    {
        // create a new node
        node *new_node = malloc(sizeof(node));
        new_node->next = NULL;
        
        // copy the string from the dictionary to the new node
        strcpy(new_node->word, buffer_word);
        
        // hash the word
        int bucket_number = hash(buffer_word);
        
        // insert node into hash table
        if (table[bucket_number] != NULL)
        {
            new_node->next = table[bucket_number]->next;
            table[bucket_number]->next = new_node;
            word_counter++;
        }
        else
        {
            table[bucket_number] = new_node;
            word_counter++;
        }
    }
    
    free(buffer_word);
    fclose(dic);
    return true;    
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    if (word_counter > 0)
    {
        return word_counter;
    }
    return 0;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for (int i = 0; i < 26; i++)
    {
        // point to first bucket
        node *emancipator = table[i];
        
        // emancipate until get NULL
        while (emancipator != NULL)
        {
            node *temp = emancipator;
            emancipator = emancipator->next;
            free(temp);
        }
    }
    return true;
}
