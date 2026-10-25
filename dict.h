#ifndef DICT_H
#define DICT_H

#define CAPACITY 10
#define MAX_STR 1000
#define LOAD_FACTOR 0.75

typedef struct Node {
    int value;
    char* key;
} Node;

typedef struct Hashmap {
    Node **table;
    int *indicies;
    int size;
    int capacity;
} Dict;

Dict* initialize_dict();
void free_dict(Dict *);
void expand_dict(Dict *dict);
void print_dict(Dict *dict);
Node* insert_element(Dict *dict, char *key, int value);
int get_element(Dict *dict, char *key);
int hash(char *key, int capacity);

#endif
