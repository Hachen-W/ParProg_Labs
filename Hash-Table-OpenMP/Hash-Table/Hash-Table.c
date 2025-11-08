#include <stdio.h>
#include <stdlib.h>
#include <string.h>



typedef struct Pair {
    char *key;
    char *value;
} Pair;

typedef struct HashTable {
    int capacity;
    Pair **storage;
} HashTable;

enum Errors {
    OK = 0,
    WRONG_ARGUMENTS = 1,
    OVERWRITING = 2,
};


Pair *create_pair(char *key, char *value)
{
    Pair *pair = malloc(sizeof(Pair));
    pair->key = strdup(key);
    pair->value = strdup(value);

    return pair;
}


void destroy_pair(Pair *pair)
{
    if (pair != NULL) {
        free(pair->key);
        free(pair->value);
        free(pair);
    }
}


unsigned int hash(char *str, int max)
{
    unsigned long hash = 5381;
    int c;
    unsigned char * u_str = (unsigned char *)str;

        while ((c = *u_str++)) {
        hash = ((hash << 5) + hash) + c;
    }

    return hash % max;
}


HashTable *create_hash_table(unsigned int capacity)
{
    HashTable *ht = calloc(1, sizeof(HashTable));
    Pair** storage = calloc(capacity, sizeof(Pair*));

    if (ht == NULL || storage == NULL || capacity == 0) {
        free(ht);
        free(storage);
        return NULL;
    }

    ht->capacity = capacity;
    ht->storage = storage;

    return ht;
}


unsigned int hash_table_insert(HashTable *ht, char *key, char *value)
{
    if (ht == NULL || key == NULL || value == NULL)
        return WRONG_ARGUMENTS;

    Pair* pair = calloc(1, sizeof(Pair));
    pair->key = key;
    pair->value = value;

    unsigned int index = hash(key, ht->capacity);
    Pair** ptr_pair = &(ht->storage[index]);

    if (*ptr_pair != NULL) {
        destroy_pair(*ptr_pair);
        *ptr_pair = pair;
        return OVERWRITING;
    }

    *ptr_pair = pair;
    return OK;
}


unsigned int hash_table_remove(HashTable *ht, char *key)
{
    if (ht == NULL || key == NULL)
        return WRONG_ARGUMENTS;

    unsigned int index = hash(key, ht->capacity);
    Pair** ptr_pair = &(ht->storage[index]);
    destroy_pair(*ptr_pair);
    *ptr_pair = NULL;
    return OK;
}


char *hash_table_retrieve(HashTable *ht, char *key)
{
    if (ht == NULL || key == NULL)
        return WRONG_ARGUMENTS;

    char* answer = NULL;
    unsigned int index = hash(key, ht->capacity);
    if (ht->storage[index] != NULL)
        answer = ht->storage[index]->value;

    return answer;
}


void destroy_hash_table(HashTable *ht)
{
    if (ht == NULL || ht->storage == NULL) {
        free(ht);
        return WRONG_ARGUMENTS;
    }
    for (unsigned int index = 0; index != ht->capacity; index++)
        destroy_pair(ht->storage[index]);
    free(ht);
}