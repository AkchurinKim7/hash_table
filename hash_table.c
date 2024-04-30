#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include <stdbool.h>

#include "hash_table.h"

#define FNV_OFFSET 14695981039346656037UL
#define FNV_PRIME 1099511628211UL

static uint64_t hash_key(const char* key) {
    uint64_t hash = FNV_OFFSET;
    for (const char* p = key; *p; p++) {
        hash ^= (uint64_t)(unsigned char)(*p);
        hash *= FNV_PRIME;
    }
    return hash;
}


h_table* ht_create(const size_t capacity) {
    h_table* table = (h_table*) malloc(sizeof(h_table));
    table->capacity = capacity;
    table->maxsz = capacity * 0.75;
    table->size = 0;

    table->items = (ht_item**) calloc(capacity, sizeof(ht_item*));
    for (int i = 0; i < capacity; i++)
        table->items[i] = NULL;

    return table;
}


ht_item* item_create(char* key, char* value) {
    ht_item* item = (ht_item*) malloc (sizeof(ht_item));
    item->key = key;
    item->value = value;
    item->state = true;

    return item;
}


void ht_free(h_table* table) {
    for (int i = 0; i < table->capacity; i++) {
        ht_item* item = table->items[i];
        if (item != NULL)
            free(item);
    }
    free(table->items);
    free(table);
}


void ht_resize(h_table* table, const size_t capacity) {
    h_table* tmp_table = ht_create(capacity);

    for (int n = 0; n < table->capacity; n++)
        if (table->items[n] != NULL) {
            ht_insert(tmp_table, table->items[n]->key, table->items[n]->value);
            ht_delete(table, table->items[n]->key);
        }

        free(table->items);
        table->capacity = capacity;
        table->maxsz = capacity * 0.75;
        table->items = (ht_item**) calloc(capacity, sizeof(ht_item*));
            for (int i = 0; i < capacity; i++)
                table->items[i] = NULL;
        
        for (int n = 0; n < tmp_table->capacity; n++)
            if (tmp_table->items[n] != NULL) 
                ht_insert(table, tmp_table->items[n]->key, tmp_table->items[n]->value);
            
        ht_free(tmp_table);
}


char* ht_get(h_table* table, const char* key) {
    uint64_t hash = hash_key(key);
    int index = hash % table->capacity;

    while (table->items[index] != NULL) {
        if (table->items[index]->key && strcmp(table->items[index]->key, key) == 0) 
            return table->items[index]->value;

        index++;

        if (index >= table->capacity)
            index = 0;
    }
    return NULL;
}


int item_get_index(h_table* table, char* key) {
    uint64_t hash = hash_key(key);
    int index = hash % table->capacity;

    while (table->items[index] != NULL) {
        if (strcmp(table->items[index]->key,  key) == 0)
            return index;

        index++;

        if (index >= table->capacity)
            index = 0;
    }
    return -1;
}


void ht_insert(h_table* table, char* key, char* value) {
    if (table->size+1 >= table->maxsz)
        ht_resize(table, table->capacity * 2);
    
    ht_item* item = item_create(key, value);
    int index = hash_key(key) % table->capacity;

    if (table->items[index] == NULL) {
        table->items[index] = item;
        table->size++;
    } else {
        while (table->items[index] != NULL) {
            if (table->items[index]->state == false)
                break;

            if (table->items[index]->key == key) {
                table->items[index]->value = value;
                free(item);
                return;
            }
            
            index++;

            if (index == table->capacity)
                index = 0;
            }
        table->items[index] = item;
        table->size++;
    }
}


void ht_delete (h_table* table, const char* key) {
    int index = hash_key(key) % table->capacity;

    while (table->items[index] != NULL) {
        if (table->items[index]->key == key) {
            table->items[index]->key = NULL;
            table->items[index]->value = NULL;
            table->items[index]->state = false;
            table->size--;
            return;
        }
        index++;

        if (index >= table->capacity)
            index = 0;
    }
    return;
}


size_t ht_size (h_table* table) {
    return table->size;
}


void ht_print(h_table* table) {
    printf("\nHash Table\n-------------------\n");

    for (int i = 0; i < table->capacity; i++)
        if (table->items[i] && table->items[i]->state == true)
            printf("Index:%d, Key:%s, Value:%s\n", i, table->items[i]->key, table->items[i]->value);

    printf("-------------------\n\n");
}

/*
int main() {
    h_table* table = ht_create(4);
    ht_insert(table, "Russia", "Moscow");
    ht_insert(table, "Russia", "Kotlas");
    ht_insert(table, "Italy", "Rome");
    //ht_insert(table, "UK", "London");
    //ht_insert(table, "Germany", "Bayern");
    //ht_insert(table, "Spain", "Madrid");
    ht_print(table);

    printf("Value of Russia='%s'\n", ht_get(table, "Russia"));
    printf("Index of Russia='%d\n", item_get_index(table, "Russia"));
    
    ht_delete(table, "Russia");
    ht_delete(table, "Italy");
    ht_print(table);

    ht_insert(table, "Russia", "Moscow");
    ht_print(table);


    printf("Value of 4='%s'\n", ht_get(table, "4"));
    printf("Value of Italy='%s'\n", ht_get(table, "Italy"));
    printf("Size of Table='%d'\n", ht_size(table));

    ht_free(table);
    return 0;
}*/