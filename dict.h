#define CAPACITY 10
#define MAX_STR 1000
#define LOAD_FACTOR 0.75

typedef struct Node {
    int value;
    char* key;
} Node;

typedef struct Hashmap {
    Node **table;
    int *indicies;
    int size;
    int capacity;
} Dict;

Dict* initialize_dict();
void free_dict(Dict *);
int resize_dict(Dict *);
void print_dict(Dict *);
int insert_element(Dict *, char *key, int value);
int get_element(Dict *, char *key);
int hash(char *key, int capacity);
