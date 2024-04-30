typedef struct {
    char* key;
    char* value;
    bool state; // true - элемент существует, false - элемент был удалён
} ht_item;

/*
capacity - Максимальная вместимость таблицы (2^n)
size - Текущее количество элементов в таблице
maxsz - Размер таблицы, при котором происходит 
увеличение её размера (75% от максимальной вместимости)
*/
typedef struct {
    ht_item** items;
    size_t capacity;
    size_t size;
    size_t maxsz;
} h_table;

/* Хэш-функция FNV-1a*/
static uint64_t hash_key(const char* key);

h_table* ht_create(const size_t capacity);

ht_item* item_create(char* key, char* value);

void ht_free(h_table* table);

void ht_resize(h_table* table, const size_t capacity);

char* ht_get(h_table* table, const char* key);

void ht_insert(h_table* table, char* key, char* value);

void ht_print(h_table* table);

size_t ht_size (h_table* table);

void ht_delete (h_table* table, const char* key);

int item_get_index(h_table* table, char* key);