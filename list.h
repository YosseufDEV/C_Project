#ifndef LIST_H
#define LIST_H

#include "utils.h"

typedef struct List List;

List* initialize_list(int, Value[]);
Value get_list(List *, int);
Value append_list(List *, Value);
void list_insert(List *, int, Value);
void remove_list(List *, int);
void pop_list(List *);
void clear_list(List *);
void reverse(List *);
unsigned len_list(List *);
unsigned count_list(List *, Value);
unsigned index_list(List *, Value);
void sort_list(List *);
List* sorted_list(List *);

#endif
