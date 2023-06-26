#include "Table.h"


Table* new_table(const char *filename) {
  Pager* pager = pager_start(filename);
  Table* table = (Table *) malloc(sizeof(Table));
  table->pager = pager;

  table->root_page_num = 0;

  if (pager->num_pages == 0) {
    // New database file.
    void* root_node = get_page(pager, 0);
    initialize_leaf_node(root_node);
  }
  return table;
}

void compress_row(Row *source, void *destination){
  memcpy(destination + ID_OFFSET, &(source->id), ID_SIZE);
  memcpy(destination + USERNAME_OFFSET, &(source->username), USERNAME_SIZE);
  memcpy(destination + EMAIL_OFFSET, &(source->email), EMAIL_SIZE);
}
void decompress_row(void *source, Row *destination){
  memcpy(&(destination->id), source + ID_OFFSET, ID_SIZE);
  memcpy(&(destination->username), source + USERNAME_OFFSET, USERNAME_SIZE);
  memcpy(&(destination->email), source + EMAIL_OFFSET, EMAIL_SIZE);
}

void print_row(Row *row){
  printf("(%d, %s, %s)\n", row->id, row->username, row->email);
}

void* cursor_val(Cursor *cursor) {
  uint32_t page_num = cursor->page_num;
  void* page = get_page(cursor->table->pager, page_num);
  // Will be leaf node
  return leaf_node_value(page, cursor->cell_num);
}

void free_table(Table* table) {
  Pager* pager = table->pager;

  for (uint32_t i = 0; i < pager->num_pages; i++) {
    if (pager->pages[i] == NULL) {
      continue;
    }
    pager_flush(pager, i);
    free(pager->pages[i]);
    pager->pages[i] = NULL;
  }

  int result = close(pager->file_desc);
  if (result == -1) {
    printf("Error closing db file.\n");
    exit(EXIT_FAILURE);
  }
  for (uint32_t i = 0; i < TABLE_MAX_PAGES; i++) {
    void* page = pager->pages[i];
    if (page) {
      free(page);
      pager->pages[i] = NULL;
    }
  }
  free(pager);
  free(table);
}
