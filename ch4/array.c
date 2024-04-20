#include "array.h"
#include <assert.h>
#include <stdlib.h>

array_t *
new_array (int initial_size)
{
  array_t *array = malloc (sizeof (array_t));
  array->array   = malloc (initial_size * sizeof (int));
  array->used    = 0;
  array->size    = initial_size;
  return array;
}

void
delete_array (array_t *array)
{
  free (array->array);
  free (array);
}

static void
resize (array_t *array, unsigned int new_size)
{
  assert (new_size >= array->used);
  array->array = (int *)realloc (array->array, new_size * sizeof (int));
}

void
append (array_t *array, int value)
{
  if (array->used == array->size)
    {
      resize (array, 2 * array->size);
    }
  array->array[array->used++] = value;
}

int
get (array_t *array, int index)
{
  assert (array->used > index);
  return array->array[index];
}

void
set (array_t *array, int index, int value)
{
  assert (array->used > index);
  array->array[index] = value;
}

int
pop (array_t *array)
{
  assert (array->used > 0);
  int top = array->array[--(array->used)];
  if (array->used < array->size / 4)
    {
      resize (array, array->size / 2);
    }
  return top;
}
