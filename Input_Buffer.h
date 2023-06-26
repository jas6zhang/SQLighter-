#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *buffer;
    size_t buffer_len;
    ssize_t input_len;
} InputBuffer;

InputBuffer* create_input_buffer();

void free_input_buffer();

int read_input(InputBuffer* input_buffer);
