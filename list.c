#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct DynamicList {
    void **items;
    unsigned int size;
    unsigned int capacity;
};


struct DynamicList* list_create(unsigned int initial_capacity) {
    struct DynamicList *list = malloc(sizeof(struct DynamicList));
    if (!list) return NULL;

    list->size = 0;
    list->capacity = initial_capacity > 0 ? initial_capacity : 4;
    list->items = malloc(list->capacity * sizeof(void*));

    if (!list->items) {
        free(list);
        return NULL;
    }

    return list;
}

void list_destroy(struct DynamicList *list) {
    if (!list) return;

    free(list->items); 
    free(list);        
}


int list_resize(struct DynamicList *list, unsigned int new_capacity) {
    if (!list) return 0;

    void **new_items = calloc(new_capacity, sizeof(void*));
    if (!new_items) {
        return 0; 
    }

    if (list->items && list->size > 0) {
        unsigned int items_to_copy = (list->size < new_capacity) ? list->size : new_capacity;
        memcpy(new_items, list->items, items_to_copy * sizeof(void*));
    }

    free(list->items);

    list->items = new_items;
    list->capacity = new_capacity;

    if (list->size > new_capacity) {
        list->size = new_capacity;
    }

    return 1;
}


int list_append(struct DynamicList *list, void *element) {
    if (list->size == list->capacity) {
        unsigned int new_capacity = (list->capacity == 0) ? 4 : list->capacity * 2;
        if (!list_resize(list, new_capacity)) return 0;
    }

    list->items[list->size] = element;
    list->size++;
    return 1;
}

int list_insert(struct DynamicList *list, unsigned int index, void *element) {
    if (index > list->size) {
        index = list->size;
    }

    if (list->size == list->capacity) {
        unsigned int new_capacity = (list->capacity == 0) ? 4 : list->capacity * 2;
        if (!list_resize(list, new_capacity)) return 0;
    }

    unsigned int elements_to_shift = list->size - index;
    if (elements_to_shift > 0) {
        memmove(&list->items[index + 1], 
                &list->items[index], 
                elements_to_shift * sizeof(void*));
    }

    list->items[index] = element;
    list->size++;
    return 1;
}

void* list_pop(struct DynamicList *list) {
    if (list->size == 0) {
        return NULL; 
    }

    list->size--;
    void *element = list->items[list->size];
    list->items[list->size] = NULL;
    return element;
}

void* list_pop_at(struct DynamicList *list, unsigned int index) {
    if (list->size == 0 || index >= list->size) {
        return NULL; 
    }

    void *element = list->items[index];
    unsigned int elements_to_shift = list->size - index - 1;

    if (elements_to_shift > 0) {
        memmove(&list->items[index], 
                &list->items[index + 1], 
                elements_to_shift * sizeof(void*));
    }

    list->size--;
    list->items[list->size] = NULL;
    return element;
}

int list_push(struct DynamicList *list, void *element) {
    if (!list) return 0;

    if (list->size == list->capacity) {
        unsigned int new_capacity = (list->capacity == 0) ? 4 : list->capacity * 2;
        if (!list_resize(list, new_capacity)) {
            return 0; 
        }
    }

    list->items[list->size] = element;
    list->size++;
    return 1; 
}

unsigned int list_size(const struct DynamicList *list) {
    return list ? list->size : 0;
}

void* list_get(const struct DynamicList *list, unsigned int index) {
    if (!list || index >= list->size) {
        return NULL; 
    }
    return list->items[index];
}

int list_set(struct DynamicList *list, unsigned int index, void *element) {
    if (!list || index >= list->size) {
        return 0;
    }
    list->items[index] = element;
    return 1;
}

void list_print(const struct DynamicList *list) {
    if (!list) {
        printf("List is NULL\n");
        return;
    }

    printf("[");
    for (unsigned int i = 0; i < list->size; i++) {
        if (list->items[i] == NULL) {
            printf("NULL");
        } else {
            /* Dereference void* as int* */
            printf("%d", *(int*)list->items[i]);
        }

        if (i < list->size - 1) {
            printf(", ");
        }
    }
    printf("] (size: %u, cap: %u)\n", list->size, list->capacity);
}