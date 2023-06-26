#pragma once
#include <stdint.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include "Constants.h"

typedef struct {
  int file_desc;
  uint32_t file_len;
  uint32_t num_pages;
  void *pages[TABLE_MAX_PAGES];
} Pager;

Pager *pager_start(const char *filename);
void* get_page(Pager* pager, uint32_t page_num);
void pager_flush(Pager* pager, uint32_t page_num);
