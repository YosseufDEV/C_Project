#include "tuple.h"
#include <stdlib.h>
#include <stdio.h>

struct Tuple {
    Value** items;
    int length;
};

Tuple* initialize_tuple(unsigned length, Value values[]) {
    if(values == NULL) {
        fprintf(stderr, "Values array must not equal NULL\n");
        exit(EXIT_FAILURE);
    }

    Tuple* t = malloc(sizeof(*t));
    Value** items = malloc(length * sizeof(Value*));

    for(int i = 0; i < length; i++) {
        items[i] = &values[i];
    }

    t->items = items;
    t->length = length;

    return t;
}

Value get_tuple(Tuple* t, int index) {
    if(t == NULL) {
        fprintf(stderr, "Tuple is NULL\n");
        exit(EXIT_FAILURE);
    }

    if(index >= t->length || -index > t->length) {
        printf("Index out of bounds: %d\n", index);
        return null();
    }

    return index >= 0 ? *t->items[index] : *t->items[t->length + index];
}

int index_tuple(Tuple* t, Value value) {
    if(t == NULL) {
        fprintf(stderr, "Tuple is NULL\n");
        exit(EXIT_FAILURE);
    }

    for(int i = 0; i < t->length; i++) {
        if(compare_values(*t->items[i], value) == 0) {
            return i;
        }
    }
    return -1;
}

unsigned count_tuple(Tuple *t, Value v) {
    if(t == NULL) {
        fprintf(stderr, "Tuple is NULL\n");
        exit(EXIT_FAILURE);
    }

    unsigned count = 0;

    for(int i = 0; i < t->length; i++) {
        if(compare_values(*t->items[i], v) == 0) {
            count++;
        }
    }
    return count;
}

