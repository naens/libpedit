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
void ch_ucs32_to_utf8(uint32_t chr, int *sz, uint8_t *buf);
uint8_t *ch_utf8_to_ucs32(uint8_t *p8, uint32_t *ch32);

void str_ucs32_to_utf8(uint32_t *st32, int *sz, uint8_t *str8);
void str_utf8_to_ucs32(uint8_t *str8, int *sz, uint32_t *str32);

int utf8chrlen(uint8_t *chr);
int utf8strlen(uint8_t *str);
int ucs32strlen(uint32_t *str);

#endif /* PEDIT_H */
