#include "dict.h"
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int hash(char *key, int capacity) {
    int s = 0;
    unsigned long hash = 5381;

    while (key[s++] != '\0'); 

    for(int i = 0; i < s; i++) {
        hash = ((hash<<5) + hash) + key[i];
    }

    return hash % capacity;
}

Dict* initialize_map() {
    Dict *dict = malloc(sizeof(Dict));

    if(dict == NULL) {
        printf("Error: Memory allocation failed for dictionary\n");
        return NULL;
    }

    dict->table = calloc(CAPACITY, sizeof *dict->table);
    dict->indicies = calloc(CAPACITY, sizeof *dict->table);

    dict->size = 0;
    dict->capacity = CAPACITY;
    for(int i = 0; i < CAPACITY; i++) {
        dict->table[i] = NULL;
    }
    return dict;
}

void free_map(Dict *dict) {
    for(int i = 0; i < dict->capacity; i++) {
        if(dict->table[i] != NULL) {
            free(dict->table[i]);
        }
    }
    free(dict);
}

Node* insert_element(Dict *dict, char *key, int value) {
    int index = hash(key, dict->capacity);

    if(dict->table[index] != NULL) {
        printf("Error: Key collision at index %d for key '%s'\n", index, key);
    }

    Node* node = dict->table[index] = malloc(sizeof(Node));
    dict->indicies[dict->size]=index;

    if(dict->table[index] == NULL) {
        printf("Error: Memory allocation failed for node\n");
        return 0;
    }

    node->value = value;
    node->key = key;

    dict->size++;

    if((float)(dict->size)/(dict->capacity) > LOAD_FACTOR) {
        // print_dict(dict);
        expand_dict(dict);
    }

    return dict->table[index];
}

void expand_dict(Dict *dict) {
    int old_capacity = dict->capacity;
    int new_capacity = ceil((double)(old_capacity/LOAD_FACTOR)); 

    Node **new_table = calloc(new_capacity, sizeof(*new_table));
    int *new_indicies = calloc(new_capacity, sizeof(*new_indicies));

    printf("Expanding Dict! new capcaity %d \n", new_capacity);

    if(new_table == NULL) {
        printf("Error: Reallocation of memory failed!");
        return;
    }

    for(int i = 0, k=0; i < dict->capacity; i++) {
        const int i_index = dict->indicies[i];
        if(dict->table[i_index] != NULL) {
            Node* n = dict->table[i_index];
            int index = hash(n->key, new_capacity);
            new_table[index] = n;
            new_indicies[k++] = index;
        }
    }

    dict->table = new_table;
    dict->indicies = new_indicies;
    dict->capacity = new_capacity;
}

int get_element(Dict *dict, char *key) {
    int index = hash(key, dict->capacity);
    return dict->table[index]->value;
}

void print_dict(Dict *dict) {
    printf("=======\n");
    for(int i = 0; i<dict->size;i++) {
        int index = dict->indicies[i];
        if(dict->table[index]!=NULL) {
            printf("i{%d}: %d\n", index, dict->table[index]->value);
        }
    }
    printf("=======\n");
}

int main() {
    Dict *d = initialize_map();

    insert_element(d, "key1", 1);
    insert_element(d, "key2", 2);
    insert_element(d, "key3", 3);
    insert_element(d, "key4", 4);
    insert_element(d, "key5", 5);
    insert_element(d, "key6", 6);
    insert_element(d, "key7", 7);
    insert_element(d, "key8", 8);
    print_dict(d);

    free_map(d);

    return 0;
}
