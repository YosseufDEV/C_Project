#ifndef DICT_H
#define DICT_H

#define CAPACITY 100
#define MAX_STR 1000
#define LOAD_FACTOR 0.75

/* TODO: Make this take an array of integers and a string_flag 
 * if string_flag is true, then the value will be a string instead of an integer */
typedef struct Node {
    int value;
    char* key;
} Node;

/* TODO: use the dynamic list to replace this static node array, so that we can have a dynamic hashmap */
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
