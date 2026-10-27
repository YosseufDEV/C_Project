#include "dict.h"
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

struct Dict {
    Node **table;
    Node* first;
    Node* last;
    int size;
    int capacity;
};

int hash(char *key, int capacity) {
    int s = 0;
    unsigned long hash = 5381;

    while (key[s++] != '\0'); 

    for(int i = 0; i < s; i++) {
        hash = ((hash<<5) + hash) + key[i];
    }

    return hash % capacity;
}

Dict* initialize_dict(int values_size, Node values[]) {
    if(values_size < 0) {
        printf("Error: Invalid values_size for dictionary\n");
        return NULL;
    }

    const int capacity = ceil((double)values_size/LOAD_FACTOR);

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

    if(dict->table == NULL) {
        printf("Error: Memory allocation failed for dictionary table or indicies\n");
        return NULL;
    }

    dict->size = 0;
    dict->capacity = capacity;

    for(int i = 0; i < capacity; i++) {
        dict->table[i] = NULL;
    }

    for(int k = 0; k < values_size; k++) {
        if(values[k].key != NULL) {
            set_dict(dict, values[k].key, values[k].value);
        }
    }

    return dict;
}
int set_dict(Dict *dict, char *key, Value value) {
    int index = hash(key, dict->capacity);
    Node* node = malloc(sizeof(Node));

    if(node == NULL) {
        printf("Memory allocation for Node failed!\n");
        return -1;
    }

    node->value = value;
    node->key = key;
    node->value=value;

    // INFO : Collision Logic
    if(dict->table[index] != NULL) {
        printf("Collision for key %s with key %s at index %d\n", key, dict->table[index]->key, index);

        print_dict_unordered(dict);

        printf("\n");
        while(dict->table[index] != NULL) {
            index = (index+1)%dict->capacity; 
        }

        printf("Found empty spot at i{%d}\n", index);

    }

    node->index=index;
    dict->table[index] = node;
    dict->size++;

    if(dict->size==1){
        dict->first = dict->last = node;
        node->prev = NULL;
    } else {
        dict->last->next = node;
        node->prev = dict->last;
        dict->last = node;
        node->next = NULL;
    }

    printf("\nindex i{%d}, inserted key %s\n", index, dict->table[index]->key);
    print_dict_unordered(dict);
    printf("\n");


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

    printf("Expanding Dict! new capcaity %d \n", new_capacity);

    if(new_table == NULL) {
        printf("Error: Reallocation of memory failed!");
        return -1;
    }

    Node *n = dict->first;

    while(n != NULL) {
        int index = hash(n->key, new_capacity);

        if(new_table[index] != NULL) {
            while(new_table[index] != NULL) {
                index = (index+1)%new_capacity; 
                // printf("%d\n", index);
            }
        }

        n->index = index;
        printf("Rehashing key %s to index %d\n", n->key, index);
        new_table[index] = n;

        n = n->next;
    }

    free(dict->table);

    dict->capacity = new_capacity;
    dict->table = new_table;

    printf("New Dict after resizing:\n");
    print_dict_unordered(dict);

    return new_capacity;
}

Value get_dict(Dict *dict, char *key) {
    int index = hash(key, dict->capacity);
    Node* n = dict->table[index];

    if(n == NULL) {
        printf("Key does not exist in this dict!\n");
        return null();
    }

    if(strcmp(n->key, key) != 0) {
        printf("\n=======\n");
        printf("Key %s at index %d is not the same as the requested key. Searching for the correct key...\n", key, index);
        printf("=======\n\n");

        for(int i = 0; i < dict->capacity; i++) {
            Node* s = dict->table[i];
            if(s != NULL && strcmp(s->key, key) == 0 ) {
                return s->value; 
            }
        }

        printf("Key does not exist in this dict!\n");
        return null();
    }

    return n->value;
}

Value popitem_dict(Dict* d) {
    if(d->last == NULL) {
        printf("Dictionary is empty!");
        return null();
    }

    Value last_value = d->last->value;

    Node* t = d->last->prev;

    free(d->last);

    if(t != NULL) {
        d->last = t;
        d->last->next=NULL;
    }

    d->last=d->first=NULL;

    return last_value;
}

void print_dict_ordered(Dict *dict) {
    printf("=======\n");
    // for(int i = 0; i<len_dict(dict);i++) {
    //     int index = dict->indicies[i];
    //     if(dict->table[index]!=NULL) {
    //         printf("i{%d}:- (%s): ", index, dict->table[index]->key);
    //         print_value(dict->table[index]->value);
    //     }
    // }
    Node *n = dict->first;

    while(n!= NULL) {
        printf("i{%d}:- (%s): ", n->index, n->key);
        print_value(n->value);
        n = n->next;
    }

    printf("=======\n");
}

void print_dict_unordered(Dict *dict) {
    printf("=======\n");
    for(int i = 0; i<dict->capacity;i++) {
        if(dict->table[i]!=NULL) {
            printf("i{%d}:- (%s): ", i, dict->table[i]->key);
            print_value(dict->table[i]->value);
        }
    }
    printf("=======\n");
}

void clear_dict(Dict *dict) {
    Node* temp = dict->last;
    while(temp != NULL) {
        temp = temp->prev;
        free(dict->last);
        dict->last = temp;
    }
    dict->last = dict->first = NULL;
    // dict->last = dict->first = NULL;
}

void free_dict(Dict *dict) {
    clear_dict(dict);
    free(dict);
}

int len_dict(Dict *dict) {
    return dict->size;
}

int capacity(Dict *dict) {
    return dict->capacity;
}
