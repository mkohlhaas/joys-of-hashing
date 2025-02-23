#include "open_addressing_set.h"
#include <stdlib.h>

static uint32_t
p (uint32_t k, unsigned int i, unsigned int m)
{
  return (k + i) & (m - 1);
}

static void
resize (hash_table_t *table, uint32_t new_size)
{
  // Remember the old bins until we have moved them.
  bin_t   *old_bins = table->table;
  uint32_t old_size = table->size;

  // Update table so it now contains the new bins
  table->table = malloc (new_size * sizeof (bin_t));
  bin_t *end   = table->table + new_size;
  for (bin_t *bin = table->table; bin != end; ++bin)
    {
      bin->is_free    = true;
      bin->is_deleted = false;
    }
  table->size   = new_size;
  table->active = table->used = 0;

  // Move the values from the old bins to the new,
  // using the table's insertion function
  end = old_bins + old_size;
  for (bin_t *bin = old_bins; bin != end; ++bin)
    {
      if (bin->is_free || bin->is_deleted)
        {
          continue;
        }
      insert_key (table, bin->hash_key, bin->key);
    }

  // Finally, free memory for old bins
  free (old_bins);
}

hash_table_t *
empty_table (uint32_t size, compare_func cmp, destructor_func destructor)
{
  hash_table_t *table = malloc (sizeof (hash_table_t));
  table->table        = malloc (size * sizeof (bin_t));
  bin_t *end          = table->table + size;
  for (bin_t *bin = table->table; bin != end; ++bin)
    {
      bin->is_free    = true;
      bin->is_deleted = false;
    }
  table->size   = size;
  table->active = table->used = 0;
  table->cmp                  = cmp;
  table->destructor           = destructor;
  return table;
}

void
delete_table (hash_table_t *table)
{
  if (table->destructor)
    {
      bin_t *end = table->table + table->size;
      for (bin_t *bin = table->table; bin != end; ++bin)
        {
          if (bin->is_free || bin->is_deleted)
            {
              continue;
            }
          table->destructor (bin->key);
        }
    }
  free (table->table);
  free (table);
}

void
insert_key (hash_table_t *table, uint32_t hash_key, void *key)
{
  uint32_t index;
  bool     contains = contains_key (table, hash_key, key);
  for (uint32_t i = 0; i < table->size; ++i)
    {
      index      = p (hash_key, i, table->size);
      bin_t *bin = &table->table[index];

      if (bin->is_free)
        {
          bin->hash_key = hash_key;
          bin->key      = key;
          bin->is_free = bin->is_deleted = false;

          // we have one more active element
          // and one more unused cell changes character
          table->active++;
          table->used++;
          break;
        }

      if (bin->is_deleted && !contains)
        {
          bin->hash_key = hash_key;
          bin->key      = key;
          bin->is_free = bin->is_deleted = false;

          // we have one more active element
          // but we do not use more cells since the
          // deleted cell was already used.
          table->active++;
          break;
        }

      if (bin->hash_key == hash_key)
        {
          if (table->cmp (bin->key, key))
            {
              delete_key (table, hash_key, key);
              insert_key (table, hash_key, key);
              return; // Done
            }
          else
            {
              // we have found the key but with as
              // different value...
              // find an empty bin later.
              continue;
            }
        }
    }

  if (table->used > table->size / 2)
    {
      resize (table, table->size * 2);
    }
}

bool
contains_key (hash_table_t *table, uint32_t hash_key, void *key)
{
  for (uint32_t i = 0; i < table->size; ++i)
    {
      uint32_t index = p (hash_key, i, table->size);
      bin_t   *bin   = &table->table[index];
      if (bin->is_free)
        {
          return false;
        }
      if (!bin->is_deleted && bin->hash_key == hash_key && table->cmp (bin->key, key))
        {
          return true;
        }
    }
  return false;
}

void
delete_key (hash_table_t *table, uint32_t hash_key, void *key)
{
  for (uint32_t i = 0; i < table->size; ++i)
    {
      uint32_t index = p (hash_key, i, table->size);
      bin_t   *bin   = &table->table[index];

      if (bin->is_free)
        {
          return;
        }

      if (!bin->is_deleted && bin->hash_key == hash_key && table->cmp (bin->key, key))
        {
          bin->is_deleted = true;
          if (table->destructor)
            {
              table->destructor (table->table[index].key);
            }
          table->active--;
          break;
        }
    }

  if (table->active < table->size / 8)
    {
      resize (table, table->size / 2);
    }
}
