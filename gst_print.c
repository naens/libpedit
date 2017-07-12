#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#include "pedit.h"
#include "gst_struct.h"

char utf8buf[0x100];

void print_strings(struct gst *gst)
{
  int i;
  for (i = 0; i <= gst->sid; i++)
  {
    str_ucs32_to_utf8(gst->sa[i], utf8buf);
    printf("\tsid=%d\t%s\n", i, utf8buf);
  }
}

int print_node_info(struct node *node)
{
  char sids[0x100];
  int i = 0;
  int j = 0;
  while (i < node->sid_list_sz)
    j += sprintf(&sids[j], "%d", node->sid_list[i++]);
  
  int l_numbers;
  if (node->parent == 0)
    l_numbers = sprintf(utf8buf, "@%d(%s)", node->id, sids);
  else
    l_numbers = sprintf(utf8buf, "@%dp%d(%s)", node->id, node->parent->id, sids);

  if (node->edge_list_sz)
    {
      printf("%s──", utf8buf);
      return l_numbers + 2;
    }
  else
    {
      printf("%s\n", utf8buf);
      return l_numbers;
    }
}

int print_edge_info(struct edge *edge, uint32_t **sa, int *sa_sid_sz)
{
  int to = edge->end ? edge->to : sa_sid_sz[edge->sid];
  
  int len = to - edge->from;
  uint32_t str32[len + 1];
  memcpy(str32, &sa[edge->sid][edge->from], len * sizeof(uint32_t));
  str32[len] = 0;
  str_ucs32_to_utf8(str32, utf8buf);

  int l_data;
  if (edge->end)
    {
      l_data = sprintf(utf8buf, "%s[%d:%d,%d]", utf8buf, edge->sid, edge->from, edge->to);
      printf("─%s──", utf8buf);
      return l_data + 3; 
    }
  else
    {
      l_data = sprintf(utf8buf, "%s[%d:%d,#]\n", utf8buf, edge->sid, edge->from);
      printf("─%s", utf8buf);
      return l_data + 1; 
    }
}

void print_node(struct node *node, uint32_t **sa, int *sa_sid_sz, int pnb, int *vlast, int *vlength)
{
  /* print node info */
  int node_length = print_node_info(node);
  if (pnb > 0)
    vlength[pnb - 1] += node_length;

  int i;
  for(i = 0; i < node->edge_list_sz; i++)
    {
      struct edge *edge = node->edge_list[i];

      /* print spaces */
      if (i > 0)	
	{
	  if (pnb == 0)
	    {
	      int k;
	      for (k = 0; k < node_length; k++)
		printf("%s", " ");
	    }
	  int j;
	  for (j = 0; j < pnb; j++)
	    {
	      printf("%s", vlast[j] ? " " : "│");
	      int k;
	      for (k = 0; k < vlength[j]; k++)
		printf("%c", ' ');
	    }
	}

      /* print link char */
      if (i == node->edge_list_sz - 1)
	printf("%s", i == 0 ? "─" : "└");
      else
	printf("%s",  i == 0 ? "┬" : "├");

      /* print edge info */
      int edge_length = print_edge_info(edge, sa, sa_sid_sz);

      if (edge->end)
	{
	  if (pnb == 0)
	    {
	      int *new_vlast = malloc(2 * sizeof(int));
	      int *new_vlength = malloc(2 * sizeof(int));
	      new_vlast[0] = 1;
	      new_vlength[0] = node_length - 1;
	      new_vlast[1] = i == node->edge_list_sz - 1;
	      new_vlength[1] = edge_length;
	      print_node(edge->end, sa, sa_sid_sz, 2, new_vlast, new_vlength);
	      free(new_vlast);
	      free(new_vlength);
	    }
	  else
	    {
	      int *new_vlast = malloc((pnb + 1) * sizeof(int));
	      int *new_vlength = malloc((pnb + 1) * sizeof(int));
	      memcpy(new_vlast, vlast, pnb * sizeof(int));
	      memcpy(new_vlength, vlength, pnb * sizeof(int));
	      new_vlast[pnb] = i == node->edge_list_sz - 1;
	      new_vlength[pnb] = edge_length;
	      print_node(edge->end, sa, sa_sid_sz, pnb + 1, new_vlast, new_vlength);
	      free(new_vlast);
	      free(new_vlength);
	    }
	}
    }
}

void gst_print_tree(struct gst *gst)
{
  print_node(gst->root, gst->sa, gst->sa_sid_sz, 0, 0, 0);
}
