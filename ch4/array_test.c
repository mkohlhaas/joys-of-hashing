#include "array.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int
main ()
{
  array_t *array = new_array (1);

  for (int i = 0; i < 10; ++i)
    {
      append (array, i);
    }
  for (int j = 0; j < 10; ++j)
    {
      int i = get (array, j);
      assert (i == j);
      printf ("Expected %d and got %d.\n", j, i);
    }
  for (int j = 0; j < 10; ++j)
    {
      set (array, j, 10 * j);
      int i = get (array, j);
      assert (i == 10 * j);
      printf ("Expected %d and got %d.\n", 10 * j, i);
    }

  free (array);
}
