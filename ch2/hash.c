#include "hash.h"
#include <stdlib.h>

hash_table_t *
empty_table (uint32_t size)
{
  hash_table_t *table = malloc (sizeof (hash_table_t));
  table->table        = malloc (size * sizeof (bin_t));
  for (uint32_t i = 0; i < size; ++i)
    {
      bin_t *bin   = &table->table[i];
      bin->is_free = true;
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
  uint32_t mask  = table->size - 1;
  uint32_t index = key & mask; // or key % table->size;
  bin_t   *bin   = &table->table[index];
  if (bin->is_free)
    {
      bin->key     = key;
      bin->is_free = false;
    }
  else
    {
      // There is already a key here, so we have a
      // collision. We cannot deal with this yet.
    }
}

bool
contains_key (hash_table_t *table, uint32_t key)
{
  uint32_t mask  = table->size - 1;
  uint32_t index = key & mask; // or key % table->size;
  bin_t   *bin   = &table->table[index];
  if (!bin->is_free && bin->key == key)
    {
      return true;
    }
  else
    {
      return false;
    }
}

void
delete_key (hash_table_t *table, uint32_t key)
{
  uint32_t mask  = table->size - 1;
  uint32_t index = key & mask; // or key % table->size;
  bin_t   *bin   = &table->table[index];
  if (bin->key == key)
    {
      bin->is_free = true;
    }
}
