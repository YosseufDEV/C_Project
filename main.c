#include "dict.h"
#include "tuple.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

int main() {
    // ## Tuple ##
    Value values_t[] = {
        integer(26),
        string("TJjiowqjdioqw"),
        character('t'),
        character('t'),
        character('t'),
        character('t'),
        character('t'),
        character('t'),
        string("TJjiowqjdioqw")
    };


    Tuple* t = initialize_tuple(sizeof(values_t)/sizeof(values_t[0]), values_t);

    print_tuple(t);

    print_value(get_tuple(t, 2), 1);
    print_value(get_tuple(t, -1), 1);
    printf("%d\n", index_tuple(t, character('t')));

    putchar('\n');

    printf("%d\n", count_tuple(t, character('t')));
    printf("%d\n", count_tuple(t, string("TJjiowqjdioqw")));
    printf("%d\n", count_tuple(t, integer(26)));

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

    popitem_dict(d);
    popitem_dict(d);
    popitem_dict(d);

    print_tuple(keys_dict(d));

    print_dict_ordered(d);
    // printf("Clearing dict...\n");
    // clear_dict(d);
    // print_dict_ordered(d);

    set_dict(d, "test1", string("This is my key"));

    {
        char*key="klaskdaop";
        pop_dict(d, key);
        Value v = get_dict(d,key);
        print_dict_ordered(d);
        print_value(v, 1);
    }

    free_dict(d);

    // # LIST;
    printf("\n\n\n");

    DynamicList *list1 = list_create(2);

    list_push(list1, integer(100));
    list_push(list1, integer(200));

    list_push(list1, string("Test")); 

    // list_insert(list1, 1, string("Yes")); 

    list_insert(list1, 999, string("clampedstring")); 
    list_insert(list1, 2, string("ajsdkajdsklajdkl")); 

    // printf("%d\n", c);
    print_value(list_get(list1, 0), 1);
    print_value(list_get(list1, 1), 1);
    print_value(list_get(list1, 2), 1);
    print_value(list_get(list1, 3), 1);
    print_value(list_get(list1, 999), 1);

    list_print(list1);

    list_destroy(list1);

    return 0;    
}

