#include "Execute.h"

MetaCommandResult execute_meta_command(InputBuffer *input_buffer, Table *table) {
  if (strcmp(input_buffer->buffer, ".exit") == 0) {
    free_table(table);
    free_input_buffer(input_buffer);
    exit(EXIT_SUCCESS);
    return META_COMMAND_SUCCESS;
  } else {
    return META_UNRECOGNIZED_COMMAND;
  }
}

ExecuteResult execute_insert(Statement* statement, Table* table){
 void* node = get_page(table->pager, table->root_page_num);
  if ((*leaf_node_num_cells(node) >= LEAF_NODE_MAX_CELLS)) {
    return EXECUTE_FAIL;
  } 
  Cursor *end_cursor = end_of_table(table);
  Row *new_row = &(statement->row_to_insert);
  leaf_node_insert(end_cursor, new_row->id, new_row);

  free(end_cursor);
  return EXECUTE_SUCCESS;
}

ExecuteResult execute_select(Statement* statement, Table* table) {
  Cursor* cursor = start_of_table(table);
  Row row;
  while (!(cursor->end_of_table)) {
    decompress_row(cursor_val(cursor), &row);
    print_row(&row);
    cursor_advance(cursor);
  }

  free(cursor);
  return EXECUTE_SUCCESS;
}

ExecuteResult execute_statement(Statement* statement, Table *table) {
  switch (statement->type) {
    case (STATEMENT_INSERT):
      return execute_insert(statement, table);
    case (STATEMENT_SELECT):
	    return execute_select(statement, table);
  }
}
