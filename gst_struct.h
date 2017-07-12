#ifndef GST_STRUCT_H
#define GST_STRUCT_H

struct node
{
  int id;
  int edge_list_sz;
  struct edge **edge_list;
  struct node *sl;
  int sid_list_sz;
  int *sid_list;
  struct node *parent;
};

struct ap
{
  struct node *node;
  uint32_t ch;
  int pos;
};

struct edge
{
  int sid;
  int from;
  int to;
  struct node *end;
};

struct gst
{
  int *sa_sid_sz;		/* size of each sa[sid] */
  uint32_t **sa;
  int sid;
  int n;
  int rem;
  int nid;
  struct ap *ap;
  struct node *root;
};

#endif /* GST_STRUCT_H */
