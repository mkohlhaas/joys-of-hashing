#pragma once

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct linked_list
{
  uint32_t            hash_key;
  void               *key;
  void               *value;
  struct linked_list *next;
} linked_list_t;

typedef void (*destructor_func) (void *);
typedef bool (*compare_func) (void *, void *);

linked_list_t *new_linked_list ();
void           delete_linked_list (linked_list_t *, destructor_func, destructor_func, bool free_resouces);
void           list_add_map (linked_list_t *list, uint32_t hash_key, void *key, void *value);
linked_list_t *list_lookup_key (linked_list_t *list, uint32_t hash_key, void *key, compare_func);
bool           list_delete_key (linked_list_t *, uint32_t, void *key, compare_func, destructor_func, destructor_func);
