#include "utils.h"
#include <stdio.h>
#include <string.h>

int compare_values(Value a, Value b) {
    if(a.type != b.type) {
        return -1;
    }

    switch(a.type) {
        case PTR_INT:
            return a.ptr.integer - b.ptr.integer;
        case PTR_STR:
            return strcmp(a.ptr.string, b.ptr.string);
        case PTR_CHAR:
            return a.ptr.character - b.ptr.character;
        case PTR_FLOAT:
            return (a.ptr.float_ > b.ptr.float_) - (a.ptr.float_ < b.ptr.float_);
        case PTR_DOUBLE:
            return (a.ptr.double_ > b.ptr.double_) - (a.ptr.double_ < b.ptr.double_);
        case PTR_NULL:
            return 0; 
        case PTR_ARBITRARY:
            return (a.ptr.ptr > b.ptr.ptr) - (a.ptr.ptr < b.ptr.ptr);
        default:
            return -1;
    }
}

struct Value integer(int value) {
    struct Value i = { .ptr.integer=value, .type=PTR_INT };
    return i;
}

struct Value character(char value) {
    struct Value i = { .ptr.character=value, .type=PTR_CHAR };
    return i;
}

struct Value string(char* value) {
    struct Value i = { .ptr.string=value, .type=PTR_STR };
    return i;
}

struct Value float_(float value) {
    struct Value i = { .ptr.float_=value, .type=PTR_FLOAT };
    return i;
}

struct Value double_(double value) {
    struct Value i = { .ptr.double_=value, .type=PTR_DOUBLE };
    return i;
}

struct Value arbitrary(void* value) {
    struct Value i = { .ptr.ptr=value, .type=PTR_ARBITRARY };
    return i;
}

struct Value null(void) {
    struct Value i = { .ptr.null=1, .type=PTR_NULL };
    return i;
}

void print_value(Value value) {
    switch(value.type) {
        case PTR_INT:
            printf("%d\n", value.ptr.integer);
            break;
        case PTR_STR:
            printf("%s\n", value.ptr.string);
            break;
        case PTR_CHAR:
            printf("%c\n", value.ptr.character);
            break;
        case PTR_FLOAT: 
            printf("%f\n", value.ptr.float_);
            break;
        case PTR_DOUBLE:
            printf("%lf\n", value.ptr.double_);
            break;
        case PTR_NULL:
            printf("NULL\n");
            break;
        case PTR_ARBITRARY:
            printf("Arbitrary data type: %p\n", value.ptr.ptr);
            break;
        default:
            printf("UNHANDLED_TYPE\n");
            break;
    }
}

