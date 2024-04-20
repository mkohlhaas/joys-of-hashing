#pragma once

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct bin
{
  int      is_free : 1;
  int      is_deleted : 1;
  uint32_t key;
} bin_t;

typedef struct hash_table
{
  bin_t *table;
  size_t size;
} hash_table_t;

hash_table_t *empty_table (size_t size);
void          delete_table (hash_table_t *table);
void          insert_key (hash_table_t *table, uint32_t key);
bool          contains_key (hash_table_t *table, uint32_t key);
void          delete_key (hash_table_t *table, uint32_t key);
