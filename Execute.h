#pragma once
#include "Constants.h"
#include "Input_buffer.h"
#include "Statement.h"
#include "Table.h"
#include "Cursor.h"

typedef enum {
  META_COMMAND_SUCCESS,
  META_UNRECOGNIZED_COMMAND
} MetaCommandResult;

MetaCommandResult execute_meta_command(InputBuffer *input_buffer, Table *table);

typedef enum { 
  EXECUTE_SUCCESS,
  EXECUTE_FAIL
} ExecuteResult;

ExecuteResult execute_insert(Statement* statement, Table* table);
ExecuteResult execute_select(Statement* statement, Table* table);
ExecuteResult execute_statement(Statement *statement, Table *table);
