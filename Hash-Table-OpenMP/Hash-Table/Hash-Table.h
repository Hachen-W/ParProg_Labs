#ifndef hashtable_h
#define hashtable_h

typedef struct Pair {
    char *key;
    char *value;
} Pair;

typedef struct HashTable {
    unsigned int capacity;
    Pair **storage;
} HashTable;


HashTable *create_hash_table(unsigned int capacity);

unsigned int hash_table_insert(HashTable *ht, char *key, char *value);

unsigned int hash_table_remove(HashTable *ht, char *key);

char *hash_table_retrieve(HashTable *ht, char *key);

unsigned int destroy_hash_table(HashTable *ht);


#endif