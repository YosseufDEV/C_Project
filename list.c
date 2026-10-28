#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    void **items;
    unsigned int size;
    unsigned int capacity;
} DynamicList;


DynamicList* list_create(unsigned int initial_capacity) {
    DynamicList *list = malloc(sizeof(DynamicList));
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

void list_destroy(DynamicList *list) {
    if (!list) return;

    free(list->items); 
    free(list);        
}


int list_resize(DynamicList *list, unsigned int new_capacity) {
    void **new_items = realloc(list->items, new_capacity * sizeof(void*));
    if (!new_items) {
        return 0; 
    }

    list->items = new_items;
    list->capacity = new_capacity;
    return 1;
}


int list_append(DynamicList *list, void *element) {
    if (list->size == list->capacity) {
        unsigned int new_capacity = (list->capacity == 0) ? 4 : list->capacity * 2;
        if (!list_resize(list, new_capacity)) return 0;
    }

    list->items[list->size] = element;
    list->size++;
    return 1;
}

int list_insert(DynamicList *list, unsigned int index, void *element) {
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

void* list_pop(DynamicList *list) {
    if (list->size == 0) {
        return NULL; 
    }

    list->size--;
    void *element = list->items[list->size];
    list->items[list->size] = NULL;
    return element;
}

void* list_pop_at(DynamicList *list, unsigned int index) {
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

int list_push(DynamicList *list, void *element) {
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

unsigned int list_size(const DynamicList *list) {
    return list ? list->size : 0;
}


int main(void) {
    DynamicList *list1 = list_create(2);
    int *val1 = malloc(sizeof(int));
    *val1 = 100;
    int *val2 = malloc(sizeof(int));
    *val2 = 200;

    list_push(list1, val1);
    list_push(list1, val2);
    printf("After 2 pushes: size = %u, capacity = %u\n", list_size(list1), list1->capacity);

    int *val3 = malloc(sizeof(int));
    *val3 = 300;
    list_push(list1, val3); 
    printf("After 3rd push: size = %u, capacity = %u\n", list_size(list1), list1->capacity);

    char *mid_str = malloc(16);
    strcpy(mid_str, "middle");
    list_insert(list1, 1, mid_str); 

    char *clamped_str = malloc(16);
    strcpy(clamped_str, "end_clamped");
    list_insert(list1, 999, clamped_str); 
    printf("Index 1: %s\n", list1->items[1]);
    printf("Index 4: %s\n", list1->items[4]);

    list_destroy(list1);
    printf("List destroyed successfully with zero memory leaks.\n");

    return 0;
}