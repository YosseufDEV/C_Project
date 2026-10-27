#ifndef DICT_H
#define DICT_H

#include "utils.h"

#define LOAD_FACTOR 0.75

typedef struct Node {
    Value value;
    int index;
    struct Node* next;
    struct Node* prev;
    char* key;
} Node;

typedef struct Dict Dict;

int hash(char *key, int capacity);
Dict* initialize_dict(int, Node[]);
void free_dict(Dict *);
int resize_dict(Dict *);
void print_dict_unordered(Dict *);
void print_dict_ordered(Dict *);
void print_value(Value);
void clear_dict(Dict*);
Value popitem_dict(Dict *);
Value pop_dict(Dict*, char*);
int set_dict(Dict *, char *key, Value);
int len_dict(Dict *);
int capacity_dict(Dict *);
Value get_dict(Dict *, char *key);

#endif
