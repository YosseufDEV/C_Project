#include "dict.h"
#include <stdio.h>

int main() {
    Dict *d = initialize_dict(1);

    {
        set(d, "test1", integer(169));
        set(d, "j@()JD!()*@HJRF(*!@YHR()*!@HD(*!@Hd98!@&Hdfska", string("Test"));
        set(d, "klaskdaop", integer(1229));
        set(d, "\0i22-_901jf90c1jrf091h298h59e812hd19287hd912@", character('s'));
        set(d, "12903981290-id21k90kd+_)21k9-d()@$!)@(JD1289dj1", character('2'));
        set(d, "jd21309dk2901gj9302g89h02fwoifj012jj0@()!(J(@j", integer(22));
    }

    print_dict_ordered(d);

    {
        Value value = get(d, "12903981290-id21k90kd+_)21k9-d()@$!)@(JD1289dj1");

        if(value.ptr.null != 1) {
            print_value(value);
        } else {
            printf("Key does not exist in dict!\n");
        }
    }

    free_dict(d);

    return 0;    
}

