#pragma once

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "Constants.h"
#include "Pager.h"


typedef struct {
  uint32_t id;
  // +1 for null char
  char username[COLUMN_USERNAME_SIZE + 1];
  char email[COLUMN_EMAIL_SIZE + 1];
} Row;

typedef struct {
  uint32_t root_page_num;
  Pager* pager;
} Table;

typedef struct {
  Table *table;
  uint32_t page_num;
  uint32_t cell_num;
  bool end_of_table; // Past last element in table (potentially for insert)
} Cursor;

Table* new_table();
void free_table(Table* table);

void* row_location(Table* table, uint32_t row_num);
void compress_row(Row *source, void *destination);
void decompress_row(void *source, Row *destination);
void print_row(Row *row);
 
void* cursor_val(Cursor *cursor);
