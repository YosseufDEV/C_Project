#ifndef UTILS_H
#define UTILS_H

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

void print_value(Value);
Value string(char*);
Value integer(int);
Value float_(float);
Value arbitrary(void*);
Value double_(double);
Value character(char);
Value null(void);


#endif
