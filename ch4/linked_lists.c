#include "linked_lists.h"

/* We represent linked lists using a sentinel link at the beginning of the list.
   This makes it easier to insert and remove elements without having to return
   updated lists.
 */

linked_list_t *
new_linked_list ()
{
  linked_list_t *sentinel = malloc (sizeof (linked_list_t));
  sentinel->key           = 0;
  sentinel->next          = 0;
  return sentinel;
}

void
delete_linked_list (linked_list_t *list)
{
  // because of sentinel list != 0
  do
    {
      linked_list_t *next = list->next;
      free (list);
      list = next;
    }
  while (list != 0);
}

static linked_list_t *
get_previous_link (linked_list_t *list, uint32_t key)
{
  // because of sentinel list != 0
  while (list->next)
    {
      if (list->next->key == key)
        {
          return list;
        }
      list = list->next;
    }
  return 0; // if we get to list->next == 0, we didn't find the key
}

void
add_element (linked_list_t *list, uint32_t key)
{
  linked_list_t *link = get_previous_link (list, key);
  if (link)
    {
      return; // key already in list
    }

  // build link and put it at the front of the list
  link       = malloc (sizeof (linked_list_t));
  link->key  = key;
  link->next = list->next;
  list->next = link;
}

void
delete_element (linked_list_t *list, uint32_t key)
{
  linked_list_t *link = get_previous_link (list, key);
  if (!link)
    {
      return; // key isn't in the list
    }

  // we need to get rid of link->next
  linked_list_t *to_delete = link->next;
  link->next               = to_delete->next;
  free (to_delete);
}

bool
contains_element (linked_list_t *list, uint32_t key)
{
  return get_previous_link (list, key) != 0;
}
