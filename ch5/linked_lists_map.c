#include "linked_lists_map.h"
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
  sentinel->value         = 0;
  sentinel->next          = 0;
  return sentinel;
}

void
delete_linked_list (linked_list_t *list, destructor_func key_destructor, destructor_func val_destructor,
                    bool free_resources)
{
  while (list != 0)
    {
      linked_list_t *next = list->next;
      if (free_resources && key_destructor && list->key)
        {
          key_destructor (list->key);
        }
      if (free_resources && val_destructor && list->value)
        {
          val_destructor (list->value);
        }
      free (list);
      list = next;
    }
}

void
list_add_map (linked_list_t *list, uint32_t hash_key, void *key, void *value)
{
  linked_list_t *link = malloc (sizeof (linked_list_t));
  link->hash_key      = hash_key;
  link->key           = key;
  link->value         = value;
  link->next          = list->next;
  list->next          = link;
}

static linked_list_t *
get_previous_link (linked_list_t *list, uint32_t hash_key, void *key, compare_func key_cmp)
{
  while (list->next)
    {
      if (list->next->hash_key == hash_key && key_cmp (list->next->key, key))
        {
          return list;
        }
      list = list->next;
    }
  return 0;
}

bool
list_delete_key (linked_list_t *list, uint32_t hash_key, void *key, compare_func key_cmp,
                 destructor_func key_destructor, destructor_func val_destructor)
{
  linked_list_t *link = get_previous_link (list, hash_key, key, key_cmp);
  if (!link)
    {
      return false;
    }

  // we need to get rid of link->next
  linked_list_t *to_delete = link->next;
  link->next               = to_delete->next;
  if (key_destructor)
    {
      key_destructor (to_delete->key);
    }
  if (val_destructor)
    {
      val_destructor (to_delete->value);
    }
  free (to_delete);
  return true;
}

linked_list_t *
list_lookup_key (linked_list_t *list, uint32_t hash_key, void *key, compare_func key_cmp)
{
  linked_list_t *link = get_previous_link (list, hash_key, key, key_cmp);
  return link ? link->next : 0;
}
