#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "packet.h"
#include "buffer.h"

#define PACKET_MASK_CTRL 0x80000000
#define PACKET_MASK_SEQ  0x7FFFFFFF
#define PACKET_MASK_TYPE 0x7FFF0000

#define packet_is_control(PACKET) \
    (PACKET._head0 & PACKET_MASK_CTRL)

#define packet_get_type(PACKET) \
    (PACKET._head0 & PACKET_MASK_TYPE) \

int32_t packet_get_seq (packet_t packet)
{
    return (packet.sequence_number & PACKET_MASK_SEQ);
}

void packet_deserialize(packet_t *packet)
{
    uint32_t *block = &(packet -> _head0);
    for (int i = 0; i < MAX_PACKET_SIZE; ++i) {
        *block = ntohl(*block);
        block++;
    }
}

void packet_serialize(packet_t *packet)
{
    uint32_t *block = &(packet -> _head0);
    for (int i = 0; i < MAX_PACKET_SIZE; ++i) {
        *block = htonl(*block);
        block++;
    }
}

packet_t * packet_new(char *buffer, int len)
{
    uint32_t *block = NULL;
    int i = 0;
    packet_t *packet = NULL;

    if (len > MAX_DATA_SIZE * 4) {
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

void packet_parse(packet_t packet)
{
    packet_deserialize(&packet);
    if (packet_is_control(packet)) {                    /* control packet */

        switch (packet_get_type(packet)) {

            case 0:                                 /* handshake */
                fprintf(stderr, "log: Handshake packet received\n");
                break;

            case 1:                                 /* keep-alive */
                break;

            case 2:                                 /* ack */
                break;

            case 3:                                 /* nak */
                break;

            case 4:                                 /* congestion-delay warn */
                break;

            case 5:                                 /* shutdown */
                break;

            case 6:                                 /* ack of ack */
                break;

            case 7:                                 /* message drop request */
                break;

            case 8:                                 /* error signal */
                break;

            default:                                /* unsupported packet type */
                printf("Unknown type: %d\n", packet_get_type(packet));
                char msg[] = "Unknown packet";
                recv_buffer_write(msg, sizeof(msg));

        }
    } else {                                            /* data packet */
        char msg[] = "Data packet";
        recv_buffer_write(msg, sizeof(msg));
    }
    return;
}
