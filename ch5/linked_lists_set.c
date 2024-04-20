#include "linked_lists_set.h"
#include <assert.h>

/* We represent linked lists using a sentinel link at the beginning of the list.
   This makes it easier to insert and remove elements without having to return
   updated lists.
 */

linked_list_t *
new_linked_list ()
{
  linked_list_t *sentinel = malloc (sizeof (linked_list_t));
  sentinel->hash_key      = 0;
  sentinel->key           = 0;
  sentinel->next          = 0;
  return sentinel;
}

void
delete_linked_list (linked_list_t *list, destructor_func destructor, bool free_keys)
{
  while (list)
    {
      linked_list_t *next = list->next;
      if (free_keys && destructor && list->key)
        {
          destructor (list->key);
        }
      free (list);
      list = next;
    }
}

static linked_list_t *
get_previous_link (linked_list_t *list, uint32_t hash_key, void *key, compare_func cmp)
{
  while (list->next)
    {
      if (list->next->hash_key == hash_key && cmp (list->next->key, key))
        {
          return list;
        }
      list = list->next;
    }
  return 0;
}

void
list_insert_key (linked_list_t *list, uint32_t hash_key, void *key, compare_func cmp)
{
  // build link and put it at the front of the list.
  // the hash table checks for duplicates if we want to avoid those
  linked_list_t *new_link = malloc (sizeof (linked_list_t));
  new_link->hash_key      = hash_key;
  new_link->key           = key;
  new_link->next          = list->next;
  list->next              = new_link;
}

void
list_delete_key (linked_list_t *list, uint32_t hash_key, void *key, compare_func cmp, destructor_func destructor)
{
  linked_list_t *link = get_previous_link (list, hash_key, key, cmp);
  if (!link)
    {
      return;
    }

  linked_list_t *to_delete = link->next;
  link->next               = to_delete->next;
  if (destructor)
    {
      destructor (to_delete->key);
    }
  free (to_delete);
}

bool
list_contains_key (linked_list_t *list, uint32_t hash_key, void *key, compare_func cmp)
{
  return get_previous_link (list, hash_key, key, cmp) != 0;
}
