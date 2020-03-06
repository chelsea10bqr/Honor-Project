#include <stdint.h>
#include <stdio.h>
#include "mp4.h"
/*
 * The print_row function determines which pixels are known to be black
 * in one row of a nonogram, then prints a line indicating those pixels.
 * Up to four region sizes are given as r1, r2, r3, r4 (0 means a
 * non-existent region, and r1 must exist).  width is the number of
 * pixels in the row.  The row is printed using X to denote known black
 * pixels, and period ('.') to denote other pixels.  Finally, the
 * function returns 1 for success, or 0 if the regions cannot fit within
 * the specified width.
 */
 /*
  * The first four parameters are region sizes, allowing the row to have as many as
  *four regions. All but the
  *first region may be size 0, in which case the region does not exist
  *print a row which contains the fixed X.
  */
int32_t print_row (int32_t r1, int32_t r2, int32_t r3, int32_t r4, int32_t width)
{
  int space;            /* initilize to strore the amount of space                  */
  int difference;
  int total = width;    /* make the total as a counter to store the width of this row */
  space = 0;
  if( r2 > 0)            /* if any region has number greater than 0, the amount of space add 1*/
  {
    space = space + 1;
  }
  if( r3 > 0)
  {
    space = space + 1;
  }
  if( r4 > 0)
  {
    space = space + 1;
  }
  space = r1 + r2 + r3 + r4 + space;
  if( space > width)        /* if the sum of all region add space greater than width, impossible*/
  {
    return 0;
  }
  difference = width - space;   /* find the differece between row width and "just fit" width*/
  int r1_di;
  int r1_ne = r1 - difference;  /* find the difference between region number and "difference"*/
  for (r1_di = difference; r1_di > 0; r1_di--)
  {
    if(r1_ne <= 0 )            /* if r1_ne smaller or equal to 0  just print dot */
    {
      for (r1_di = r1+1; r1_di > 0; r1_di--)  /* use for loops to print*/
      {
        printf(".");
        total = total - 1;             /* when print 1 symbol, total minus 1*/
        if(total == 0)             /* wehn total equals 0, print done*/
        {
          printf("\n");
          return 1;
        }
      }
      break;                     /* use break to get ouf of for loop*/
    }
    printf(".");
    total = total - 1;
    if(total == 0)
    {
      printf("\n");
      return 1;
    }
  }
  if(r1_ne > 0)             /* if r1_ne greater than 0  print X*/
  {
    int symbol_1;
    for (symbol_1 = r1_ne; symbol_1 > 0; symbol_1--)
  {
    printf("X");
    total = total - 1;
    if(total == 0)
    {
      printf("\n");
      return 1;
    }
  }
    printf(".");             /* prtin the space between regions*/
    total = total - 1;
    if(total == 0)
    {
      printf("\n");
      return 1;
    }
  }
  int r2_di;
  int r2_ne = r2 - difference;  /* find the difference between region number and "difference"*/
  if(r2 != 0)
{
  for (r2_di = difference; r2_di > 0; r2_di--)
  {
    if(r2_ne <= 0 )         /* if r2_ne smaller or equal to 0  just print dot */
    {
      for (r2_di = r2+1; r2_di > 0; r2_di--)   /* use for loops to print*/
      {
        printf(".");
        total = total - 1;
        if(total == 0)
        {
          printf("\n");
          return 1;
        }
      }
      break;                    /* use break to get ouf of for loop*/
    }
    printf(".");
    total = total - 1;
    if(total == 0)
    {
      printf("\n");
      return 1;
    }
  }
  if(r2_ne > 0)
  {
    int symbol_2;
    for (symbol_2 = r2_ne; symbol_2 > 0; symbol_2--)  /* use for loops to print*/
  {
    printf("X");
    total = total - 1;
    if(total == 0)
    {
      printf("\n");
      return 1;
    }
  }
    printf(".");                /* prtin the space between regions*/
    total = total - 1;
    if(total == 0)
    {
      printf("\n");
      return 1;
    }
  }
}
  int r3_di;
  int r3_ne = r3 - difference;   /* find the difference between region number and "difference"*/
  if (r3 != 0)
  {
  for (r3_di = difference; r3_di > 0; r3_di--)
  {
    if(r3_ne <= 0 )                      /* if r3_ne smaller or equal to 0  just print dot */
    {
      for (r3_di = r3+1; r3_di > 0; r3_di--)  /* use for loops to print*/
      {
        printf(".");
        total = total - 1;
        if(total == 0)
        {
          printf("\n");
          return 1;
        }
      }
      break;             /* use break to get ouf of for loop*/
    }
    printf(".");
    total = total - 1;
    if(total == 0)
    {
      printf("\n");
      return 1;
    }
  }
  if(r3_ne > 0)
  {
    int symbol_3;
    for (symbol_3 = r3_ne; symbol_3 > 0; symbol_3--)  /* use for loops to print*/
  {
    printf("X");
    total = total - 1;
    if(total == 0)
    {
      printf("\n");
      return 1;
    }
  }
    printf(".");                      /* prtin the space between regions*/
    total = total - 1;
    if(total == 0)
    {
      printf("\n");
      return 1;
    }
  }
}
  int r4_di;
  int r4_ne = r4 - difference;   /* find the difference between region number and "difference"*/
  if (r4 != 0)
  {
  for (r4_di = difference; r4_di > 0; r4_di--)   /* use for loops to print*/
  {
    if(r4_ne <= 0 )                /* if r1_ne smaller or equal to 0  just print dot */
    {
      for (r4_di = r4; r4_di > 0; r4_di--)
      {
        printf(".");
        total = total - 1;
        if(total == 0)
        {
          printf("\n");
          return 1;
        }
      }
      break;                    /* use break to get ouf of for loop*/
    }
    printf(".");
    total = total - 1;
    if(total == 0)
    {
      printf("\n");
      return 1;
    }
  }
  if(r4_ne > 0)
  {
    int symbol_4;
    for (symbol_4 = r4_ne; symbol_4 > 0; symbol_4--)  /* use for loops to print*/
  {
    printf("X");
    total = total - 1;
    if(total == 0)
    {
      printf("\n");
      return 1;
    }
  }
  }
}
  if(difference > 0)        /* if difference greater than 0, print "difference times" space at last*/
  {
    int last;
    for (last = difference; last > 0; last--)   /* use for loops to print*/
    {
      printf(".");
      total = total - 1;
      if(total == 0)
      {
        printf("\n");
        return 1;
      }
    }
  }
  printf("\n");
  return 1;                         /* return 1 when finished print*/
}
