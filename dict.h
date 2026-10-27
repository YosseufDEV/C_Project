#ifndef DICT_H
#define DICT_H

#include "utils.h"

#define CAPACITY 100
#define LOAD_FACTOR 0.75

typedef struct Node {
    Value value;
    char* key;
} Node;

typedef struct Dict Dict;

Dict* initialize_dict(int, Node[]);
void free_dict(Dict *);
int resize_dict(Dict *);
void print_dict_unordered(Dict *);
void print_dict_ordered(Dict *);
void print_value(Value);
int set(Dict *, char *key, Value);
int len(Dict *);
int capacity(Dict *);
Value get(Dict *, char *key);
int hash(char *key, int capacity);

#endif
