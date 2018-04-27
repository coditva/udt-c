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
    new_block -> len = len;
    if (len == -1) {
        new_block -> last = 0;
        new_block -> len = PACKET_DATA_SIZE;
    } else {
        new_block -> last = 1;
    }

    linked_list_add((*buffer), new_block);

    return new_block -> len;
}

int buffer_read(buffer_t *buffer, char *data, int len)
{
    block_t *block;
    int retval = 0;
    int pos = 0;
    int last = 0;

    while (last == 0) {
        linked_list_get((*buffer), block);
        if (block == NULL) continue;

        last = block -> last;
        if (pos >= len) {
            break;
        }

        int n = ((len - pos) < block -> len) ? len - pos : block -> len;
        strncpy(data + pos, block -> data, n);
        retval += n;
        pos += n;

        free(block -> data);
        free(block);
    }

    return retval;
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
