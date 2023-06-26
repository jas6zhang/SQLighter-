#include <stdio.h>
#include "Input_buffer.h"
#include "Statement.h"
#include "Execute.h"
#include "Table.h"

int main(int argc, char* argv[]) {
    if (argc != 2) {
      printf("No database filename given!\n");
      exit(EXIT_FAILURE);
    }
    char *db_file_name = argv[1];
    InputBuffer *input_buffer = create_input_buffer();
    Table *table = new_table(db_file_name);
    while (1) {
       printf("db > ");
       read_input(input_buffer);
       if (input_buffer->buffer[0] == '.') {
         switch (execute_meta_command(input_buffer, table)) {
          case META_COMMAND_SUCCESS:
            continue;
          case META_UNRECOGNIZED_COMMAND:
            printf("Unrecognized meta command!\n");
            continue;
         }
       }

      Statement statement;
      switch(prepare_statement(input_buffer, &statement)) {
        case PREPARE_SUCCESS:
          break;
        case PREPARE_SYNTAX_ERROR:
          printf("Syntax error!\n");
          continue;
        case PREPARE_UNRECOGNIZED:
          printf("Unrecognized command!\n");
          continue;
      }
      
      switch(execute_statement(&statement, table)){
        case(EXECUTE_SUCCESS):
          printf("Executed statement!\n");
          break;
        case(EXECUTE_FAIL):
          printf("Error executing statemenT!\n");
          break;
    } 
  }
}
