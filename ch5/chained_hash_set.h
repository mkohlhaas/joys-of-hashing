#pragma once

#include <stdbool.h>
#include <stdint.h>

typedef uint32_t (*hash_func) (void *);
typedef void (*destructor_func) (void *);
typedef bool (*compare_func) (void *, void *);

typedef struct hash_table
{
  struct linked_list **table;
  uint32_t             size;
  uint32_t             used;
  compare_func         cmp;
  destructor_func      destructor;
} hash_table_t;

hash_table_t *empty_table (uint32_t size, compare_func cmp, destructor_func destructor);
void          delete_table (hash_table_t *table);
void          insert_key (hash_table_t *table, uint32_t hash_key, void *key);
bool          contains_key (hash_table_t *table, uint32_t hash_key, void *key);
void          delete_key (hash_table_t *table, uint32_t hash_key, void *key);
