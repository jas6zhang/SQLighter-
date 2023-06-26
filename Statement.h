#pragma once
#include "Input_buffer.h"
#include "Table.h"

typedef enum {
STATEMENT_INSERT, 
STATEMENT_SELECT 
} StatementType;

typedef struct {
  StatementType type;
  Row row_to_insert;
} Statement;

typedef enum {
  PREPARE_SUCCESS,
  PREPARE_UNRECOGNIZED,
  PREPARE_SYNTAX_ERROR
} StatementPrepareStatus;

StatementPrepareStatus prepare_statement(InputBuffer* input_buffer, Statement *statement);
