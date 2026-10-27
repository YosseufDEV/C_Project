#ifndef DICT_H
#define DICT_H

#define CAPACITY 100
#define LOAD_FACTOR 0.75

typedef enum {
    PTR_NULL,
    PTR_STR,
    PTR_INT,
    PTR_FLOAT,
    PTR_DOUBLE,
    PTR_CHAR,
    PTR_ARBITRARY
} NODE_VALUE_TYPE;

typedef union {
    char null;
    char* string;
    int integer;
    float float_;
    double double_;
    void* ptr;
    char character;
} ValuePtr;

typedef struct Value {
    NODE_VALUE_TYPE type;
    ValuePtr ptr;
} Value;

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

Value string(char*);
Value integer(int);
Value float_(float);
Value arbitrary(void*);
Value double_(double);
Value character(char);
Value null(void);

#endif
