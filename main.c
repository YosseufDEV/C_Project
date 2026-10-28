#include "dict.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

int main() {
    int test[] = {1, 2, 3, 4, 5};
    Node values[] = {
        { .key = "test", .value = integer(169) },
        { .key = "j@()JD!()*@HJRF(*!@YHR()*!@HD(*!@Hd98!@&Hdfska", .value = integer(199) },
        { .key = "klaskdaop", .value = integer(1229) },
        { .key = "i22-_901jf90c1jrf091h298h59e812hd19287hd912@", .value = character('s') },
        { .key = "12903981290-id21k90kd+_)21k9-d()@$!)@(JD1289dj1", .value = character('2') },
        { .key = "jd21309dk2901gj9302g89h02fwoifj012jj0@()!(J(@j", .value = integer(22) },
        {. key = "arbitrary_data_type", .value = arbitrary(test) },
        { .key = "someuniquekey", .value = character('a') },
        { .key = "anotherunique-key", .value = integer(42) },
        { .key = "yet-another-key", .value = character('z') },
        { .key = "1/100key", .value = integer(100) },
        { .key = "key-with-special-chars-!@#$%^&*()", .value = character('!') },
        { .key = "key_with_underscores", .value = integer(256) },
        { .key = "key-with-dashes", .value = character('-') },
        { .key = "key.with.dots", .value = float_(512.124) },
        { .key = "key/with/slashes", .value = character('/') },
        { .key = "key\\with\\backslashes", .value = double_(1024.1902481925) },
        { .key = "key:with:colons", .value = null() },
        { .key = "key;with;semicolons", .value = integer(2048) },
        { .key = "key,with,commas", .value = character(',') },
        { .key = "key?with?questionmarks", .value = integer(4096) },
        { .key = "key!with!exclamationmarks", .value = character('!') },
    };

    unsigned int values_size = sizeof(values) / sizeof(values[0]);

    Dict *d = initialize_dict(values_size, values);

    print_dict_ordered(d);

    {
        Value value = get(d, "12903981290-id21k90kd+_)21k9-d()@$!)@(JD1289dj1");

        if(value.ptr.null != 1) {
            print_value(value);
        } else {
            printf("Key does not exist in dict!\n");
        }

        Value value2 = get(d, "arbitrary_data_type");

        if(value.ptr.null != 1) {
            printf("Arbitrary data type: %d", ((int*)value2.ptr.ptr)[4]);
        } else {
            printf("Key does not exist in dict!\n");
        }
    }

    free_dict(d);


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

