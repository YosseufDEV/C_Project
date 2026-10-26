#include "dict.h"
#include <math.h>
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

Dict* initialize_dict() {
    Dict *dict = malloc(sizeof(Dict));

    if(dict == NULL) {
        printf("Error: Memory allocation failed for dictionary\n");
        return NULL;
    }

    dict->table = calloc(CAPACITY, sizeof *dict->table);
    dict->indicies = calloc(CAPACITY, sizeof *dict->table);

    if(dict->table == NULL || dict->indicies == NULL) {
        printf("Error: Memory allocation failed for dictionary table or indicies\n");
        return NULL;
    }

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

int insert_element(Dict *dict, char *key, int value) {
    int index = hash(key, dict->capacity);
    Node* node = malloc(sizeof(Node));

    if(node == NULL) {
        printf("Memory allocation for Node failed!\n");
        return -1;
    }

    node->value = value;
    node->key = key;

    // if(dict->table[index] != NULL) {
    //     printf("Collision detected at index %d for key %s, value %d. Probing for next available index.\n", index, key, value);
    //     while(dict->table[++index] != NULL) {
    //         if(index == dict->capacity) {
    //             printf("Reached end of array resizing dict to find empty index.\n");
    //             index = resize_dict(dict)-1;
    //             break;
    //         }
    //     }
    //     printf("Found empty spot at i{%d}\n", index);
    // }

    dict->table[index] = node;

    dict->indicies[dict->size]=index;

    if(dict->table[index] == NULL) {
        printf("Error: Memory allocation failed for node\n");
        return -1;
    }

    dict->size++;

    if((float)(dict->size)/(dict->capacity) > LOAD_FACTOR) {
        resize_dict(dict);
    }

    return index;
}

int resize_dict(Dict *dict) {
    int old_capacity = dict->capacity;
    int new_capacity = old_capacity/LOAD_FACTOR; 

    Node **new_table = calloc(new_capacity, sizeof(*new_table));
    int *new_indicies = calloc(new_capacity, sizeof(*new_indicies));

    printf("Expanding Dict! new capcaity %d \n", new_capacity);

    if(new_table == NULL) {
        printf("Error: Reallocation of memory failed!");
        return -1;
    }

    Node** old_table = dict->table;

    dict->capacity = new_capacity;
    dict->table = new_table;
    // Reset the size to 0 before rehashing the elements
    dict->size=0;

    for(int i = 0, k=0; i < old_capacity; i++) {
        if(old_table[i] != NULL) {
            Node* n = old_table[i];

            int ni = insert_element(dict, n->key, n->value);

            printf("Rehashing key %s, value %d from old index %d to new index %d\n", n->key, n->value, i, ni);

            if(ni == -1) {
                printf("Error: Rehashing failed for key %s\n", n->key);
                return -1;
            }

            free(n);
            // This throws a bug for some reason!.
            // free(n);
        }
    }

    free(old_table);

    dict->indicies = new_indicies;

    return new_capacity;
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

void print_dict_by_index(Dict *dict) {
    printf("=======\n");
    for(int i = 0; i<dict->capacity;i++) {
        if(dict->table[i]!=NULL) {
            printf("i{%d}: %d\n", i, dict->table[i]->value);
        }
    }
    printf("=======\n");
}

int main() {
    Dict *d = initialize_dict();

    insert_element(d, "key1", 1);
    insert_element(d, "key2", 2);
    insert_element(d, "key3", 3);
    insert_element(d, "key4", 4);
    insert_element(d, "key5", 5);
    insert_element(d, "key6", 6);
    insert_element(d, "key7", 7);
    insert_element(d, "key8", 8);

    print_dict_by_index(d);

    free_map(d);

    return 0;
}
