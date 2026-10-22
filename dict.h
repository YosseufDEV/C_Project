#ifndef DICT_H
#define DICT_H

#define MAX_EL 1000
#define MAX_STR 1000
#define LOAD_FACTOR 0.75

/* TODO: Make this take an array of integers and a string_flag 
 * if string_flag is true, then the value will be a string instead of an integer */
typedef struct Node {
    int value;
} Node;

/* TODO: use the dynamic list to replace this static node array, so that we can have a dynamic hashmap */
typedef struct Hashmap {
    Node *table[MAX_EL];
    int size;
    int (*insert)(struct Hashmap *dict, char *key, int value);
    int (*get)(struct Hashmap *dict, char *key);
} Dict;

int insert_element(Dict *dict, char *key, int value);
int get_element(Dict *dict, char *key);

int hash(char *key);

#endif
