#pragma once

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct linked_list
{
  uint32_t            key;
  struct linked_list *next;
} linked_list_t;

linked_list_t *new_linked_list ();
void           delete_linked_list (linked_list_t *list);
void           add_element (linked_list_t *list, unsigned int key);
void           delete_element (linked_list_t *list, unsigned int key);
bool           contains_element (linked_list_t *list, unsigned int key);
