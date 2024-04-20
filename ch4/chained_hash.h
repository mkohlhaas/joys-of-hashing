#pragma once

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct hash_table
{
  struct linked_list **table;
  size_t               size;
  size_t               used;
} hash_table_t;

hash_table_t *empty_table (size_t size);
void          delete_table (hash_table_t *table);
void          insert_key (hash_table_t *table, uint32_t key);
bool          contains_key (hash_table_t *table, uint32_t key);
void          delete_key (hash_table_t *table, uint32_t key);
