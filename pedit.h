#ifndef PEDIT_H
#define PEDIT_H

#include <stdint.h>

/* GST FUNCTIONS */
struct gst;

struct gst *gst_new();
void gst_free(struct gst *gst);
void gst_print_tree(struct gst *gst);

void gst_add_char(struct gst *gst, uint32_t ch);
void gst_add_string(struct gst *gst, uint32_t *str);
void gst_line_end(struct gst *gst);
void gst_get_strings(struct gst *gst, int *count, uint32_t ***strings);
void gst_get_longest_strings(struct gst *gst, int *count, uint32_t ***strings);

/* UTF8 FUNCTIONS */
void ucs32_to_utf8(uint32_t chr, int *sz, uint8_t *buf);
uint32_t utf8_to_ucs32(int sz, uint8_t *chr);

#endif /* PEDIT_H */
