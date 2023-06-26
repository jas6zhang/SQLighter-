#include "Input_Buffer.h"

InputBuffer *create_input_buffer() {
  InputBuffer *input_buffer = (InputBuffer *)malloc(sizeof(InputBuffer));

  input_buffer->buffer = NULL;
  input_buffer->buffer_len = 0;
  input_buffer->input_len = 0;

  return input_buffer;
}

void free_input_buffer(InputBuffer *input_buffer) {
  free(input_buffer->buffer);
  free(input_buffer);
}

int read_input(InputBuffer *input_buffer) {
  ssize_t bytes_read =
      getline(&(input_buffer->buffer), &(input_buffer->buffer_len), stdin);
  ;

  if (bytes_read <= 0) {
    return 1;
  }
  input_buffer->input_len = bytes_read - 1;
  input_buffer->buffer[bytes_read - 1] = 0;
  return 0;
}
