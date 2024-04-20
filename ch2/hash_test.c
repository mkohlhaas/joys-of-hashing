#include "hash.h"
#include <stdio.h>
#include <stdlib.h>

int const n = 10;

static unsigned int
random_key ()
{
  unsigned int key = (unsigned int)random ();
  if (key == 0 || key == 1)
    {
      return 2;
    }
  return key;
}

void
print_is_key_in_table (size_t keys[n], hash_table_t *table)
{
  printf ("\n");
  for (int i = 0; i < n; ++i)
    {
      printf ("is key %zu in table? %s\n", keys[i], contains_key (table, keys[i]) ? "✓" : "✗");
    }
  printf ("\n");
}

int
main ()
{
  size_t keys[n];
  for (int i = 0; i < n; ++i)
    {
      keys[i] = random_key ();
    }

  hash_table_t *table = empty_table (32);
  for (int i = 0; i < n; ++i)
    {
      printf ("inserting key %lu\n", keys[i]);
      insert_key (table, keys[i]);
    }

  print_is_key_in_table (keys, table);

  printf ("removing keys 3 and 4 (%lu and %lu)\n", keys[3], keys[4]);
  delete_key (table, keys[3]);
  delete_key (table, keys[4]);

  print_is_key_in_table (keys, table);

  delete_table (table);
}
