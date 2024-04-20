#include "chained_hash.h"
#include "linked_lists.h"
#include <stdlib.h>

hash_table_t *
empty_table (size_t size)
{
  hash_table_t *table = malloc (sizeof (hash_table_t));
  table->table        = malloc (size * sizeof (linked_list_t *));
  for (size_t i = 0; i < size; ++i)
    {
      table->table[i] = new_linked_list ();
    }
  table->size = size;
  return table;
}

void
delete_table (hash_table_t *table)
{
  for (size_t i = 0; i < table->size; ++i)
    {
      delete_linked_list (table->table[i]);
    }
  free (table->table);
  free (table);
}

void
insert_key (hash_table_t *table, uint32_t key)
{
  uint32_t mask  = table->size - 1;
  uint32_t index = key & mask;
  if (!contains_element (table->table[index], key))
    {
      add_element (table->table[index], key);
    }
}

bool
contains_key (hash_table_t *table, uint32_t key)
{
  uint32_t mask  = table->size - 1;
  uint32_t index = key & mask;
  return contains_element (table->table[index], key);
}

void
delete_key (hash_table_t *table, uint32_t key)
{
  uint32_t mask  = table->size - 1;
  uint32_t index = key & mask;
  delete_element (table->table[index], key);
}
