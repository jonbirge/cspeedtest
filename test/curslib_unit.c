#include <stdio.h>
#include <stdlib.h>
#include "src/curslib.h"

static int test_limiter(void)
{
   if (limiter(5, 0, 3) != 3)
      return 1;
   if (limiter(-2, -1, 2) != -1)
      return 1;
   if (limiter(1, 0, 2) != 1)
      return 1;
   return 0;
}

static int test_qlimit(void)
{
   if (!qlimit(0, 0, 5))
      return 1;
   if (qlimit(6, 0, 5))
      return 1;
   if (qlimit(-1, 0, 5))
      return 1;
   return 0;
}

static int test_rand_max(void)
{
   int max = 7;
   srand(0);
   for (int i = 0; i < 1000; ++i)
   {
      int val = rand_max(max);
      if (val < 0 || val > max)
         return 1;
   }
   return 0;
}

int main(void)
{
   int failed = 0;

   failed += test_limiter();
   failed += test_qlimit();
   failed += test_rand_max();

   if (failed)
   {
      fprintf(stderr, "curslib unit tests: %d failure(s)\n", failed);
      return 1;
   }

   return 0;
}
