#include <stdio.h>
#include <string.h>
#include "src/timecurses.h"

static int verify_screen_table(void)
{
   init_screen_table();
   screen_display *table = get_screen_table();
   if (table == NULL)
      return 1;

   if (get_screen_count() != 3)
      return 1;

   const char *expected_names[] = {"random", "sphere", "swirl"};
   for (int i = 0; i < 3; ++i)
   {
      if (table[i].name == NULL || strcmp(table[i].name, expected_names[i]) != 0)
         return 1;
      if (table[i].fun == NULL)
         return 1;
   }

   return 0;
}

static int verify_screen_selection(void)
{
   set_current_screen(0);
   if (get_current_screen() != 0)
      return 1;

   set_current_screen(2);
   if (get_current_screen() != 2)
      return 1;

   return 0;
}

int main(void)
{
   int failed = 0;

   failed += verify_screen_table();
   failed += verify_screen_selection();

   if (failed)
   {
      fprintf(stderr, "timecurses unit tests: %d failure(s)\n", failed);
      return 1;
   }

   return 0;
}
