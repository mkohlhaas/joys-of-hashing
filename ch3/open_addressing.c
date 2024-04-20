#include "open_addressing.h"
#include <stdlib.h>

// Pick probing strategy
#define LINEAR_PROBING

#ifdef LINEAR_PROBING
static uint32_t
p (uint32_t k, uint32_t i, uint32_t m)
{
  return (k + i) & (m - 1);
}
#else
// DOUBLE HASHING
static uint32_t
p (uint32_t k, uint32_t i, uint32_t m)
{
  uint32_t h1 = k;
  uint32_t h2 = (k << 1) | 1;
  return (h1 + i * h2) & (m - 1);
}
#endif

hash_table_t *
empty_table (size_t size)
{
  hash_table_t *table = malloc (sizeof (hash_table_t));
  table->table        = malloc (size * sizeof (bin_t));
  for (size_t i = 0; i < size; ++i)
    {
      bin_t *bin      = &table->table[i];
      bin->is_free    = true;
      bin->is_deleted = false;
    }
  table->size = size;
  return table;
}

void
delete_table (hash_table_t *table)
{
  free (table->table);
  free (table);
}

void
insert_key (hash_table_t *table, uint32_t key)
{
  uint32_t index;
  bin_t   *bin;
  for (size_t i = 0; i < table->size; ++i)
    {
      index = p (key, i, table->size);
      bin   = &table->table[index];
      if (bin->is_free || bin->is_deleted || bin->key == key)
        {
          break;
        }
    }
  bin->is_free = bin->is_deleted = false;
  bin->key                       = key;
}

bool
contains_key (hash_table_t *table, uint32_t key)
{
  for (size_t i = 0; i < table->size; ++i)
    {
      uint32_t index = p (key, i, table->size);
      bin_t   *bin   = &table->table[index];
      if (bin->is_free)
        {
          return false;
        }
      if (!bin->is_deleted && bin->key == key)
        {
          return true;
        }
    }
  return false;
}

void
delete_key (hash_table_t *table, uint32_t key)
{
  for (size_t i = 0; i < table->size; ++i)
    {
      uint32_t index = p (key, i, table->size);
      bin_t   *bin   = &table->table[index];
      if (bin->is_free)
        {
          return;
        }
      if (bin->key == key)
        {
          bin->is_deleted = true;
          return;
        }
    }
}
