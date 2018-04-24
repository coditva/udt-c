#include <stdlib.h>

#include "util.h"
#include "buffer.h"

static buffer_t buffer;

int user_buffer_add(char *data, int len)
{
    block_t *block = (block_t *) malloc(sizeof(block_t));
    if (block == NULL) return -1;
    block -> data = data;
    block -> len = len;

    linked_list_add(buffer, block);

    return 0;
}

int user_buffer_read(char *data, int len)
{
    return 0;
}
