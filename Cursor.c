#include "Cursor.h"

Cursor *start_of_table(Table *table){
  Cursor *cursor = malloc(sizeof(Cursor));
  cursor->table = table;
  cursor->page_num = table->root_page_num;
  cursor->cell_num = 0;

  void* root_node = get_page(table->pager, table->root_page_num);
  uint32_t num_cells = *leaf_node_num_cells(root_node);
  cursor->end_of_table = (num_cells == 0); 
  return cursor;
}

Cursor *end_of_table(Table *table){
  Cursor *cursor = malloc(sizeof(Cursor));
  cursor->table = table;
  cursor->page_num = table->root_page_num;
  
  void* root_node = get_page(table->pager, table->root_page_num);
  uint32_t num_cells = *leaf_node_num_cells(root_node);
  cursor->cell_num = num_cells;
  
  cursor->end_of_table = 1;
  return cursor;
}

void cursor_advance(Cursor *cursor) {
  void* node = get_page(cursor->table->pager, cursor->page_num);
  cursor->cell_num += 1;
  if (cursor->cell_num >= (*leaf_node_num_cells(node))){
    cursor->end_of_table = 1;
  }
}
