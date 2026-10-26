#ifndef DICT_H
#define DICT_H

#define CAPACITY 100
#define LOAD_FACTOR 0.75

typedef enum : unsigned char {
    PTR_STR,
    PTR_INT,
    PTR_FLOAT,
    PTR_DOUBLE,
    PTR_CHAR,
} NODE_VALUE_TYPE;


typedef struct Value {
    NODE_VALUE_TYPE type;
    union {
        char* str;
        int* integer;
        float* float_;
        double* double_;
        char* character;
    } ptr;
} Value;

typedef struct Node {
    Value value;
    char* key;
} Node;

typedef struct Dict Dict;

Dict* initialize_dict(int);
void free_dict(Dict *);
int resize_dict(Dict *);
void print_dict_unordered(Dict *);
void print_dict_ordered(Dict *);
void print_value(Value);
int set(Dict *, char *key, Value);
int len(Dict *);
int capacity(Dict *);
void* get(Dict *, char *key);
int hash(char *key, int capacity);

Value integer(int);
Value character(char);

#endif
