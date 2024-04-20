#pragma once

typedef struct array
{
  int         *array;
  unsigned int size;
  unsigned int used;
} array_t;

array_t *new_array (int initial_size);
void     delete_array (array_t *array);
void     append (array_t *array, int value);
int      get (array_t *array, int index);
void     set (array_t *array, int index, int value);
int      pop (array_t *array);
