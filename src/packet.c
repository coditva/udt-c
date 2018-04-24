#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "config.h"
#include "packet.h"
#include "buffer.h"

#define PACKET_MASK_CTRL 0x80000000
#define PACKET_MASK_SEQ  0x7FFFFFFF
#define PACKET_MASK_TYPE 0x7FFF0000

#define packet_is_control(PACKET) \
    (PACKET.header._head0 & PACKET_MASK_CTRL)

#define packet_get_type(PACKET) \
    (PACKET.header._head0 & PACKET_MASK_TYPE) \

void packet_deserialize(packet_t *packet)
{
    uint32_t *block = &(packet -> header._head0);
    for (int i = 0; i < PACKET_HEADER_SIZE; ++i) {
        *block = ntohl(*block);
        block++;
    }
}

void packet_serialize(packet_t *packet)
{
    uint32_t *block = &(packet -> header._head0);
    for (int i = 0; i < PACKET_HEADER_SIZE; ++i) {
        *block = htonl(*block);
        block++;
    }
}

int packet_new(packet_t *packet, packet_header_t *header,
               char *buffer, int len)
{
    if (len > sizeof(packet -> data)) return -1;

    memset(packet, 0, sizeof(packet_t));
    packet -> header = *header;
    strcpy(packet -> data, buffer);

    return len;
}

void packet_parse(packet_t packet)
{
    packet_header_t header;
    char buffer[PACKET_DATA_SIZE];
    uint32_t type = 0,
             isn = 0,
             mss = 0,
             flight_flag_size = 0,
             id = 0,
             req_type = 0,
             cookie = 0;

    packet_deserialize(&packet);
    if (packet_is_control(packet)) {                    /* control packet */
        switch (packet_get_type(packet)) {

        case 0:                                 /* handshake */
            header = packet.header;
            sprintf(buffer, "%u%u%u%u%u%u%u%u",
                    UDT_VERSION,
                    type,
                    isn,
                    mss,
                    flight_flag_size,
                    req_type,
                    id,
                    cookie);
            packet_new(&packet, &header, buffer, 8 * sizeof(uint32_t));
            packet_serialize(&packet);
            send_packet_buffer_write(&packet);
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
