#pragma once

#include <stdbool.h>
#include <stdint.h>

typedef void (*destructor_func) (void *);
typedef bool (*compare_func) (void *, void *);

typedef struct bin
{
  bool     is_free : 1;
  bool     is_deleted : 1;
  uint32_t hash_key;
  void    *key;
  void    *value;
} bin_t;

typedef struct hash_table
{
  bin_t          *table;
  uint32_t        size;
  uint32_t        used;
  uint32_t        active;
  compare_func    key_cmp;
  destructor_func key_destructor;
  destructor_func val_destructor;
} hash_table_t;

hash_table_t *empty_table (uint32_t size, compare_func, destructor_func, destructor_func);
void          delete_table (hash_table_t *table);
void          add_map (hash_table_t *table, uint32_t hash_key, void *key, void *value);
void          delete_key (hash_table_t *table, uint32_t hash_key, void *key);
void         *lookup_key (hash_table_t *table, uint32_t hash_key, void *key);
