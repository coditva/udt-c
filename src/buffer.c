#include <stdlib.h>
#include <string.h>

#include "buffer.h"
#include "util.h"

int buffer_write(buffer_t *buffer, char *data, int len)
{
    block_t *new_block = NULL;
    char *new_data = NULL;

    new_data = strdup(data);
    if (new_data == NULL) return -1;

    new_block = (block_t *) malloc(sizeof(block_t));
    if (new_block == NULL) return -1;

    new_block -> data = new_data;
    new_block -> len  = len;

    linked_list_add((*buffer), new_block);

    return len;
}

int buffer_read(buffer_t *buffer, char *data, int len)
{
    block_t *block;

    linked_list_get((*buffer), block);
    if (block == NULL) return 0;

    if (len < block -> len) return -1;
    strcpy(data, block -> data);

    return block -> len;
}
