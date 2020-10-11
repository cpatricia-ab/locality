#include <string.h>

#include <a2plain.h>
#include "uarray2.h"

/************************************************/
/* Define a private version of each function in */
/* A2Methods_T that we implement.               */
/************************************************/
typedef A2Methods_UArray2 A2;	// private abbreviation


static A2Methods_UArray2 new(int width, int height, int size)
{
  //TODO: Implement this function and remove the dummy return statement.
  return UArray2_new(width, height, size);
}

static A2Methods_UArray2 new_with_blocksize(int width, int height, int size, int blocksize)
{
  //TODO: Implement this function and remove the dummy return statement.
  (void) blocksize;

  return NULL;
}

static void a2free(A2 * array2p)
{
	UArray2_free((UArray2_T *) array2p);
}

static int width(A2 array2)
{
	return UArray2_width(array2);
}
static int height(A2 array2)
{
	return UArray2_height(array2);
}
static int size(A2 array2)
{
	return UArray2_size(array2);
}


static A2Methods_Object *at(A2 array2, int i, int j)
{
	return UArray2_at(array2, i, j);
}

/* TODO: ...many more private (static) definitions follow */

static void map_row_major(A2Methods_UArray2 uarray2,
                          A2Methods_applyfun apply,
                          void *cl)
{
  UArray2_map_row_major(uarray2, (UArray2_applyfun*)apply, cl);
}

static void map_col_major(A2Methods_UArray2 uarray2,
                          A2Methods_applyfun apply,
                          void *cl)
{
  UArray2_map_col_major(uarray2, (UArray2_applyfun*)apply, cl);
}

struct small_closure {
  A2Methods_smallapplyfun *apply;
  void                    *cl;
};

static void apply_small(int i, int j, UArray2_T uarray2,
                        void *elem, void *vcl)
{
  struct small_closure *cl = vcl;
  (void)i;
  (void)j;
  (void)uarray2;
  cl->apply(elem, cl->cl);
}

static void small_map_row_major(A2Methods_UArray2        a2,
                                A2Methods_smallapplyfun  apply,
                                void *cl)
{
  struct small_closure mycl = { apply, cl };
  UArray2_map_row_major(a2, apply_small, &mycl);
}

static void small_map_col_major(A2Methods_UArray2        a2,
                                A2Methods_smallapplyfun  apply,
                                void *cl)
{
  struct small_closure mycl = { apply, cl };
  UArray2_map_col_major(a2, apply_small, &mycl);
}


static struct A2Methods_T uarray2_methods_plain_struct = {
    new,
    NULL, //ask is we need this or if we can just delete
    a2free,
    width,
    height,
    size,
    NULL,
    at,
    map_row_major,
    map_col_major,
    NULL,
    NULL, //what is map default?
    small_map_row_major,
    small_map_col_major,
    NULL,
    NULL,
};

// finally the payoff: here is the exported pointer to the struct

A2Methods_T uarray2_methods_plain = &uarray2_methods_plain_struct;