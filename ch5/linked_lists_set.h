#pragma once

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct linked_list
{
  uint32_t            hash_key;
  void               *key;
  struct linked_list *next;
} linked_list_t;

typedef void (*destructor_func) (void *);
typedef bool (*compare_func) (void *, void *);

linked_list_t *new_linked_list ();
void           delete_linked_list (linked_list_t *list, destructor_func destructor, bool free_keys);
void           list_insert_key (linked_list_t *list, uint32_t hash_key, void *key, compare_func cmp);
bool           list_contains_key (linked_list_t *list, uint32_t hash_key, void *key, compare_func cmp);
void           list_delete_key (linked_list_t *list, uint32_t hash_key, void *key, compare_func, destructor_func);
