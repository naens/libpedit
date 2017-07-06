#include <string.h>

#include "pedit.h"

void ch_ucs32_to_utf8(uint32_t chr, int *sz, uint8_t *buf)
{
  if (chr < 0x80)
  {
    *sz = 1;
    buf[0] = chr;
    return;
  }
  uint8_t tmpbuf[6];
  memset(tmpbuf, 0, 6);
  uint32_t tmp = chr;
  uint8_t byte1 = 0x0;
  int i = 0;
  while (tmp > 0)
  {
    tmpbuf[i] = tmp & 0x3f | 0x80;
    tmp >>= 6;
    byte1 = (byte1 >> 1) | 0x80;
    i++;
  }
  *sz = i;
  int j = 0;
  int k = i - 1;
  while (k >=0)
  {
    buf[j] = tmpbuf[k];
    j++;
    k--;
  }
  buf[0] |= byte1;
}

uint8_t *ch_utf8_to_ucs32(uint8_t *p8, uint32_t *ch32)
{
  if (*p8 < 0x80)
    *ch32 = *p8;
  else
  {
    uint32_t m = 0x80;
    *ch32 = *p8 & ~m;
    m >>= 1;
    while (*ch32 & m)
    {
      p8++;
      *ch32 = ((*ch32 & ~m) << 6) | (*p8 & 0x3f);
      m <<= 5;
    }
  }
  p8++;
  return p8;
}

void str_ucs32_to_utf8(uint32_t *str32, int *sz, uint8_t *str8)
{
  uint32_t *p32 = str32;
  uint8_t *p8 = str8;
  while (p32)
  {
    int sz;
    ch_ucs32_to_utf8(*p32, &sz, p8);
    p8 += sz;
    p32++;
  }
}

void str_utf8_to_ucs32(uint8_t *str8, int *sz, uint32_t *str32)
{
    uint8_t *p8 = str8;
    uint32_t *p32 = str32;
    while (p8)
    {
      p8 = ch_utf8_to_ucs32(p8, p32);
      p32++;
    }
}

int utf8chrlen(uint8_t *chr)
{
  return *chr == 0 ? 0
       : *chr < 0x80 ? 1
       : *chr < 0xe0 ? 2
       : *chr < 0xf0 ? 3
       : *chr < 0xf8 ? 4
       : *chr < 0xfc ? 5
       : *chr < 0xfe ? 6 : -1;
}

int utf8strlen(uint8_t *str)
{
  int res = 0;
  uint8_t *tmp = str;
  while (*(tmp += utf8chrlen(tmp)))
    res++;
  return res;
}

int ucs32strlen(uint32_t *str)
{
  int res = 0;
  uint32_t *tmp = str;
  while (*(tmp++))
    res++;
  return res;
}
