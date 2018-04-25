#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "config.h"
#include "packet.h"
#include "buffer.h"
#include "core.h"


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
    packet_serialize(packet);

    return len;
}

int packet_new_handshake(packet_t *packet)
{
    packet_t new_packet;
    char buffer[8 * sizeof(uint32_t)];
    uint32_t *p = NULL;
    uint32_t type = 0,
             isn = 0,
             mss = 0,
             flight_flag_size = 0,
             id = 0,
             req_type = 0,
             cookie = 0;

    packet_clear_header (new_packet);
    packet_set_ctrl     (new_packet);
    packet_set_type     (new_packet, PACKET_TYPE_HANDSHAKE);
    packet_set_timestamp(new_packet, 0);
    packet_set_id       (new_packet, 0);

    p = (uint32_t *) buffer;
    *p++ = UDT_VERSION;
    *p++ = type;
    *p++ = isn;
    *p++ = mss;
    *p++ = flight_flag_size;
    *p++ = req_type;
    *p++ = id;
    *p++ = cookie;

    return packet_new(packet, &new_packet.header, buffer, sizeof(buffer));
}

void packet_parse(packet_t packet)
{
    packet_header_t header;

    packet_deserialize(&packet);
    if (packet_is_control(packet)) {                    /* control packet */
        switch (packet_get_type(packet)) {

        case 0:                                 /* handshake */
            printf("Handshaked\n");
            if (connection.is_client) {
                handshake_terminate();
                break;
            }
            packet_new_handshake(&packet);
            send_packet_buffer_write(&packet);
            connection.is_connected = 1;
            break;

        case 1:                                 /* keep-alive */
            header = packet.header;
            packet_set_type(packet, PACKET_TYPE_KEEPALIVE);

            packet_new(&packet, &header, NULL, 0);
            send_packet_buffer_write(&packet);
            break;

        case 2:                                 /* ack */
            header = packet.header;
            packet_set_type(packet, PACKET_TYPE_ACK);

            packet_new(&packet, &header, NULL, 0);
            send_packet_buffer_write(&packet);
            break;

        case 3:                                 /* nak */
            header = packet.header;
            packet_set_type(packet, PACKET_TYPE_NAK);

            packet_new(&packet, &header, NULL, 0);
            send_packet_buffer_write(&packet);
            break;

        case 4:                                 /* congestion-delay warn */
            header = packet.header;
            packet_set_type(packet, PACKET_TYPE_CONGDELAY);

            packet_new(&packet, &header, NULL, 0);
            send_packet_buffer_write(&packet);
            break;

        case 5:                                 /* shutdown */
            header = packet.header;
            packet_set_type(packet, PACKET_TYPE_SHUTDOWN);

            packet_new(&packet, &header, NULL, 0);
            send_packet_buffer_write(&packet);
            break;

        case 6:                                 /* ack of ack */
            header = packet.header;
            packet_set_type(packet, PACKET_TYPE_ACK2);

            packet_new(&packet, &header, NULL, 0);
            send_packet_buffer_write(&packet);
            break;

        case 7:                                 /* message drop request */
            header = packet.header;
            packet_set_type(packet, PACKET_TYPE_DROPREQ);

            packet_new(&packet, &header, NULL, 0);
            send_packet_buffer_write(&packet);
            break;

        case 8:                                 /* error signal */
            header = packet.header;
            packet_set_type(packet, PACKET_TYPE_ERRSIG);

            packet_new(&packet, &header, NULL, 0);
            send_packet_buffer_write(&packet);
            break;

        default:                                /* unsupported packet type */
            printf("Unknown type: %d\n", packet_get_type(packet));
            char msg[] = "Unknown packet";
            recv_buffer_write(msg, sizeof(msg));

        }
    } else {                                            /* data packet */
        recv_buffer_write(packet.data, sizeof(packet.data));
    }
    return;
}
