#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "pedit.h"

int main(int argc, char **argv)
{
  if (argc == 1)
  {
    printf("args: string to lcs\n");
    return 1;
  }

  uint32_t *strs32[argc - 1];
  for (int i = 0; i < argc - 1; i++)
  {
    uint8_t *utf8str = argv[i + 1];
    int sz = strlen(utf8str);
    int len8 = utf8strlen(utf8str);

    strs32[i] = malloc(sizeof (uint32_t) * (len8 + 1));
    str_utf8_to_ucs32(utf8str, strs32[i]);
  }

  struct gst *gst = gst_new();

  for (int i = 0; i < argc - 1; i++)
    {
      int j = 0;
      while (strs32[i][j])
        gst_add_char(gst, strs32[i][j++]);
      gst_line_end(gst);
      gst_print_tree(gst);
    }

  int ls_cnt;
  uint32_t **lss;
  gst_get_longest_strings(gst, &ls_cnt, &lss);

  if (ls_cnt == 0)
  {
    printf("no longest string found\n");
    gst_free(gst);
    return 0;
  }
  
  char lcs[0x1000];
  for (int i = 0; i < ls_cnt; i++)
  {
    str_ucs32_to_utf8(lss[i], lcs);
    printf("%s\n", lcs);
    free(lss[i]);
  }

  gst_free(gst);
  return 0;
}
