// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include <math.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 5000;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    int n = hash(word);
    node *tmp = table[n];

    while (tmp != NULL)
    {
        if (strcasecmp(word, tmp->word) == 0)
        {
            return true;
        }
        tmp = tmp->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    int hash_value = strlen(word);
    int str_len = strlen(word);
    for (int i = 0; i < str_len; i++)
    {
        if (hash_value % 2 == 0)
            hash_value += round((toupper(word[i]) - 64) * str_len / 5);
        else
            hash_value += round((toupper(word[i]) - 64) * 17 / str_len);

        hash_value *= str_len * 25 / 7;
    }
    return hash_value % N;
}

unsigned int word_count = 0;

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Open dictionary and ensure it opened
    FILE *fp_d = fopen(dictionary, "r");
    if (fp_d == NULL)
        return false;

    // Writes each word in dictionary to BUFFER
    char BUFFER[LENGTH];

    while (fscanf(fp_d, "%s", BUFFER) != EOF)
    {
        // Get hash value for each word in dictionary
        int hash_value = hash(BUFFER);

        // Allocate space for a node to be added to a linked list, check it
        node *new_head = malloc(sizeof(node));
        if (new_head == NULL)
            return false;

        // Add word from dictionary into new head of linked list
        strcpy(new_head->word, BUFFER);

        // If the linked list isn't started, the new head won't lead anywhere
        if (table[hash_value] == NULL)
            new_head->next = NULL;

        // Otherwise, it will lead to the previous head
        else
            new_head->next = table[hash_value];

        // Store the new head as the start of the linked list
        table[hash_value] = new_head;
        word_count++;
    }

    // Once every word from dictionary is stored, dictionary can be closed
    fclose(fp_d);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return word_count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i <= N; i++)
    {
        while (table[i] != NULL)
        {
            node *tmp = table[i]->next;
            free(table[i]);
            table[i] = tmp;
        }
    }
    return true;
}
