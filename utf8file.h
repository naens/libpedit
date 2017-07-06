#ifndef UTF8FILE_H
#define UTF8FILE_H

#include <stdint.h>
#include <stdio.h>

/* read one escaped unicode or one utf8 character */
uint32_t read_char(FILE *f);

int copyutf8char(char *dest, char *src);
int getutf8pos(char *str, int pos);

/* skip bom in utf8 files, do nothing if no bom */
int utf8writebom(FILE *f);
int utf8skipbom(FILE *f);

uint32_t read_utf8(FILE *f);
void write_utf8(FILE *f, uint32_t chr);
#endif /* UTF8_FILE_H */
