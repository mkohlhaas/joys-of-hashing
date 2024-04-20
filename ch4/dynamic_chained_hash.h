#pragma once

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct linked_list *subtable;

typedef struct hash_table
{
  subtable *tables;
  uint32_t  table_bits;
  uint32_t  k;
  uint32_t  subtable_mask;
  uint32_t  old_tables_mask;
  uint32_t  new_tables_mask;
  uint32_t  allocated_tables;
  uint32_t  split_count;
  uint32_t  max_bin_initialised;
} hash_table_t;

hash_table_t *empty_table (size_t table_bits);
void          delete_table (hash_table_t *table);
void          insert_key (hash_table_t *table, uint32_t key);
bool          contains_key (hash_table_t *table, uint32_t key);
void          delete_key (hash_table_t *table, uint32_t key);
