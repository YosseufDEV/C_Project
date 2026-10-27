#ifndef TUPLE_H
#define TUPLE_H

#include "utils.h"

typedef struct Tuple Tuple;

Tuple* initialize_tuple(unsigned, Value[]);
Value get_tuple(Tuple *, int);
unsigned len_tuple(Tuple *);
unsigned count_tuple(Tuple *, Value);
int index_tuple(Tuple *, Value);
void sort_tuple(Tuple *);
Tuple* sorted_tuple(Tuple *);

#endif
