#include <stdlib.h>
#include <stdio.h>
#include "dict.h"

int hash(char *key) {
    int s = 0;
    unsigned long hash = 5381;

    while (key[s++] != '\0'); 

    for(int i = 0; i < s; i++) {
        hash = ((hash<<5) + hash) + key[i];
    }

    return hash % MAX_EL;
}

Dict* initialize_map() {
    Dict *dict = malloc(sizeof(Dict));
    dict->size = 0;
    dict->insert = insert_element;
    for(int i = 0; i < MAX_EL; i++) {
        dict->table[i] = NULL;
    }
    return dict;
}

int insert_element(Dict *dict, char *key, int value) {
    int index = hash(key);
    dict->table[index] = malloc(sizeof(Node));
    dict->table[index]->value = value;
    dict->size++;
    return 1;
}

int get_element(Dict *dict, char *key) {
    int index = hash(key);
    return dict->table[index]->value;
}

int main() {
    Dict *d = initialize_map();

    insert_element(d, "key1", 69);
    insert_element(d, "key2", 67);

    printf("%d\n", get_element(d, "key1"));
    printf("%d\n", get_element(d, "key2"));
    return 0;
}
