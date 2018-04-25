#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#include "buffer.h"
#include "util.h"

int buffer_init(buffer_t *buffer)
{
    pthread_mutex_init(&(buffer -> mutex), NULL);
    return 0;
}

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
    free(block -> data);
    free(block);

    return block -> len;
}

int buffer_write_packet(buffer_t *buffer, packet_t *packet)
{
    packet_block_t *new_block = NULL;

    new_block = (packet_block_t *) malloc(sizeof(packet_block_t));
    if (new_block == NULL) return -1;

    new_block -> packet = *packet;

    linked_list_add((*buffer), new_block);
    return 1;
}

int buffer_read_packet(buffer_t *buffer, packet_t *packet)
{
    packet_block_t *block = NULL;

    linked_list_get((*buffer), block);
    if (block == NULL) return 0;

    *packet = block -> packet;
    free(block);

    return 1;
}
