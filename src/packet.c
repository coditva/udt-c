#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "packet.h"

int packet_is_data(packet_t packet)
{
    return (packet.sequence_number & PACKET_TYPE_MASK) ? 0 : 1;
}

int packet_is_control(packet_t packet)
{
    return (packet.sequence_number & PACKET_TYPE_MASK) ? 1 : 0;
}


int32_t packet_get_seq (packet_t packet)
{
    return (packet.sequence_number & PACKET_SEQ_MASK);
}

void packet_deserialize(packet_t *packet, int len)
{
    uint32_t *block = &(packet -> _head0);
    while (len > 0) {
        *block = ntohl(*block);
        block++;
        len -= 8;
    }
}

void packet_serialize(packet_t *packet, int len)
{
    uint32_t *block = &(packet -> _head0);
    while (len > 0) {
        *block = htonl(*block);
        block++;
        len -= 8;
    }
}

packet_t * packet_new(char *buffer, int len)
{
    uint32_t *block = NULL;
    int i = 0;
    packet_t *packet = NULL;

    if (len > MAX_DATA_SIZE * 8) {
        return NULL;
    }

    packet = (packet_t *) malloc(sizeof(packet_t));
    if (packet == NULL) return NULL;

    memset(packet, 0, sizeof(packet_t));

    block = (uint32_t *) buffer;
    while (len >= 0) {
        sscanf((char *)block, "%u", &(packet -> data[i]));
        i++;
        len -= 8;
    }

    return packet;
}
