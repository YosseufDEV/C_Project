#ifndef DYNAMIC_LIST_H
#define DYNAMIC_LIST_H

#include "utils.h"

typedef struct DynamicList DynamicList;

DynamicList *list_create(unsigned int initial_capacity);
void list_destroy(DynamicList *list);
int list_resize(DynamicList *list, unsigned int new_capacity);
int list_append(DynamicList *list, Value element);
int list_insert(DynamicList *list, unsigned int index, Value element);
void *list_pop(DynamicList *list);
void *list_pop_at(DynamicList *list, unsigned int index);
int list_push(DynamicList *list, Value v);
unsigned int list_size(const DynamicList *list);
Value list_get(const DynamicList *list, unsigned int index);
int list_set(DynamicList *list, unsigned int index, Value);
void list_print(const DynamicList *list);

#endif
