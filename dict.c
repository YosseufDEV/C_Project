#include "dict.h"
#include <string.h>
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

Dict* initialize_dict(int capacity) {
    if(capacity <= 0) {
        printf("Error: Invalid capacity for dictionary\n");
        return NULL;
    }

    Dict *dict = malloc(sizeof(Dict));

    if(dict == NULL) {
        printf("Error: Memory allocation failed for dictionary\n");
        return NULL;
    }

    dict->table = calloc(capacity, sizeof *dict->table);
    dict->indicies = calloc(capacity, sizeof *dict->table);

    if(dict->table == NULL || dict->indicies == NULL) {
        printf("Error: Memory allocation failed for dictionary table or indicies\n");
        return NULL;
    }

    dict->size = 0;
    dict->capacity = capacity;

    for(int i = 0; i < capacity; i++) {
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

int insert_element(Dict *dict, char *key, void* value, NODE_VALUE_TYPE type) {
    int index = hash(key, dict->capacity);
    Node* node = malloc(sizeof(Node));

    if(node == NULL) {
        printf("Memory allocation for Node failed!\n");
        return -1;
    }

    node->value = value;
    node->key = key;
    node->type=type;

    // INFO : Collision Logic
    if(dict->table[index] != NULL) {
        printf("Collision for key %s with key %s at index %d\n", key, dict->table[index]->key, index);

        print_dict_by_index(dict);

        printf("\n");
        while(dict->table[index] != NULL) {
            index = (index+1)%dict->capacity; 
        }

        printf("Found empty spot at i{%d}\n", index);

    }

    dict->size++;
    dict->table[index] = node;

    printf("\nindex i{%d}, inserted key %s\n", index, dict->table[index]->key);
    print_dict_by_index(dict);
    printf("\n");

    // dict->indicies[dict->size]=index;

    if(dict->table[index] == NULL) {
        printf("Error: Memory allocation failed for node\n");
        return -1;
    }

    printf("%f %% load_factor\n", (float)(dict->size)/(dict->capacity)*100);
    if((float)(dict->size)/(dict->capacity) >= LOAD_FACTOR) {
        resize_dict(dict);
    }

    return index;
}

int resize_dict(Dict *dict) {
    int old_capacity = dict->capacity;
    int new_capacity = ceil((double)old_capacity/LOAD_FACTOR); 

    Node **new_table = calloc(new_capacity, sizeof(*new_table));
    int *new_indicies = calloc(new_capacity, sizeof(*new_indicies));

    printf("Expanding Dict! new capcaity %d \n", new_capacity);

    if(new_table == NULL) {
        printf("Error: Reallocation of memory failed!");
        return -1;
    }

    for(int i = 0, k=0; i < old_capacity; i++) {
        if(dict->table[i] != NULL) {
            Node* n = dict->table[i];
            int index = hash(n->key, new_capacity);

            if(new_table[index] != NULL) {
                while(new_table[index] != NULL) {
                    index = (index+1)%new_capacity; 
                }
            }

            new_table[index] = n;

            printf("Rehashsed key %s from old index %d to new index %d\n", n->key, i, index);

        }
    }

    free(dict->table);
    dict->capacity = new_capacity;
    dict->table = new_table;

    printf("New Dict after resizing:\n");
    print_dict_by_index(dict);

    dict->indicies = new_indicies;

    return new_capacity;
}

void* get_element(Dict *dict, char *key) {
    int index = hash(key, dict->capacity);

    Node* n = dict->table[index];

    if(n == NULL) {
        printf("Key does not exist in this dict!\n");
        return NULL;
    }

    if(strcmp(n->key, key) != 0) {
        printf("\n=======\n");
        printf("Key %s at index %d is not the same as the requested key. Searching for the correct key...\n", key, index);
        printf("=======\n\n");

        for(int i = 0; i < dict->capacity; i++) {
            Node* s = dict->table[i];
            if(s != NULL && strcmp(s->key, key) == 0 ) {
                return &(s->value); 
            }
        }

        printf("Key does not exist in this dict!\n");
        return NULL;
    }

    return &n->value;

}

void print_dict(Dict *dict) {
    printf("=======\n");
    for(int i = 0; i<dict->size;i++) {
        int index = dict->indicies[i];
        if(dict->table[index]!=NULL) {
            switch(dict->table[index]->type) {
                case PTR_INT:
                    printf("i{%d}:- (%s): %d\n", index, dict->table[index]->key, *(int*)dict->table[index]->value);
                    break;
                case PTR_STR:
                    printf("i{%d}:- (%s): %s\n", index, dict->table[index]->key, (char*)dict->table[index]->value);
                    break;
                default:
                    printf("UNHANDLED_TYPE\n");
                    break;
            }
            printf("i{%d}:- (%s): %d\n", index, dict->table[index]->key, *(int*)dict->table[index]->value);
        }
    }
    printf("=======\n");
}

void print_dict_by_index(Dict *dict) {
    printf("=======\n");
    for(int i = 0; i<dict->capacity;i++) {
        if(dict->table[i]!=NULL) {
            switch(dict->table[i]->type) {
                case PTR_INT:
                    printf("i{%d}:- (%s): %d\n", i, dict->table[i]->key, *(int*)dict->table[i]->value);
                    break;
                case PTR_STR:
                    printf("i{%d}:- (%s): %s\n", i, dict->table[i]->key, (char*)dict->table[i]->value);
                    break;
                default:
                    printf("UNHANDLED_TYPE\n");
                    break;
            }
        }
    }
    printf("=======\n");
}

int main() {
    Dict *d = initialize_dict(1);

    insert_element(d, "test1", &(int){169}, PTR_INT);
    insert_element(d, "test2", "Test", PTR_STR);

    print_dict_by_index(d);

    free_map(d);

    return 0;
}
