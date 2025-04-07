// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node {
    char word[LENGTH + 1];
    struct node *next;
} node;

// Choose number of buckets in hash table
const unsigned int N = 142993;

// Hash table
node *table[N];

// Variable to keep track of how much words were loaded so far
unsigned int wordCount = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word) {
    // Find it's position on the table
    unsigned int position = hash(word);

    // Iterate over each node of that bucket
    for (node *tmp = table[position]; tmp != NULL; tmp = tmp->next) {
        // Compare the word with bucket's word
        if(strcasecmp(word, tmp->word) == 0) {
            return true; // Return true if found
        }
    }

    // Return false if not found
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word) {
    unsigned int hashValue = 0;

    for (int i = strlen(word) - 1; i >= 0; i--) {
        hashValue *= 11;
        hashValue += tolower(word[i]) * i + 1;
    }

    return hashValue % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary) {
    // Open dictionary file
    FILE *source = fopen(dictionary, "r");
    if (source == NULL) {
        return false;
    }

    // Read strings from file one at a time
    char *str = malloc(LENGTH + 1);
    if (str == NULL) {
        fclose(source);
        return false;
    }
    while (fscanf(source, "%s", str) != EOF) {
        // Create a new node for each word
        node *n = malloc(sizeof(node));
        if (n == NULL) {
            free(str);
            fclose(source);
            return false;
        }
        n->next = NULL;
        strcpy(n->word, str);

        // Hash word and insert it at that location
        int hashValue = hash(n->word);
        if (table[hashValue] == NULL) {
            table[hashValue] = n;
        } else {
            for (node *i = table[hashValue]; i != NULL; i = i->next) {
                if (i->next == NULL) {
                    i->next = n;
                    break;
                }
            }
        }

        wordCount++;
    };

    free(str);
    fclose(source);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void) {
    return wordCount;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void) {
    node *cursor, *tmp;

    for (int i = N - 1; i >= 0; i--) {
        cursor = table[i];

        while (cursor != NULL) {
            tmp = cursor;
            cursor = cursor->next;
            free(tmp);
        }
    }

    return true;
}
