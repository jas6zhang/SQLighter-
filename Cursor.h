#pragma once
#include "Table.h"
#include "Node.h"

Cursor *start_of_table(Table *table);
Cursor *end_of_table(Table *table);
void cursor_advance(Cursor *cursor);
