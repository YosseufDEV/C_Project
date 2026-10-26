#define CAPACITY 100
#define LOAD_FACTOR 0.75

typedef enum {
    PTR_STR,
    PTR_INT,
    PTR_FLOAT,
    PTR_DOUBLE,
    PTR_CHAR,
} NODE_VALUE_TYPE;

typedef struct Node {
    void* value;
    NODE_VALUE_TYPE type;
    char* key;
} Node;

typedef struct Hashmap {
    Node **table;
    int *indicies;
    int size;
    int capacity;
} Dict;

Dict* initialize_dict(int);
void free_dict(Dict *);
int resize_dict(Dict *);
void print_dict_by_index(Dict *);
void print_dict(Dict *);
int insert_element(Dict *, char *key, void* value, NODE_VALUE_TYPE);
void* get_element(Dict *, char *key);
int hash(char *key, int capacity);
