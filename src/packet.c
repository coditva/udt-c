#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>

#include "config.h"
#include "packet.h"
#include "buffer.h"
#include "core.h"

extern conn_t connection;

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

int packet_new(packet_t *packet, char *buffer, int len)
{
    if (len > sizeof(packet -> data)) return -1;

    memset(packet -> data, 0, sizeof(PACKET_DATA_SIZE));
    strncpy(packet -> data, buffer, len);
    packet_serialize(packet);

    return len;
}

int packet_new_handshake(packet_t *packet)
{
    char buffer[8 * sizeof(uint32_t)];
    uint32_t *p = NULL;
    uint32_t type = 0,
             isn = 0,
             mss = 0,
             flight_flag_size = 0,
             id = 0,
             req_type = 0,
             cookie = 0;

    packet_clear_header (*packet);
    packet_set_ctrl     (*packet);
    packet_set_type     (*packet, PACKET_TYPE_HANDSHAKE);
    packet_set_timestamp(*packet, 0);
    packet_set_id       (*packet, 0);

    p = (uint32_t *) buffer;
    *p++ = UDT_VERSION;
    *p++ = type;
    *p++ = isn;
    *p++ = mss;
    *p++ = flight_flag_size;
    *p++ = req_type;
    *p++ = id;
    *p++ = cookie;

    return packet_new(packet, buffer, sizeof(buffer));
}

void packet_parse(packet_t packet)
{
    packet_deserialize(&packet);
    if (packet_is_control(packet)) {                    /* control packet */
        switch (packet_get_type(packet)) {

        case PACKET_TYPE_HANDSHAKE:             /* handshake */
            if (connection.is_client) {
                handshake_terminate();
                break;
            }
            packet_new_handshake(&packet);
            send_packet_buffer_write(&packet);
            connection.is_connected = 1;
            break;

        case PACKET_TYPE_KEEPALIVE:             /* keep-alive */
            break;

        case PACKET_TYPE_ACK:                   /* ack */
            break;

        case PACKET_TYPE_NAK:                   /* nak */
            break;

        case PACKET_TYPE_CONGDELAY:             /* congestion-delay warn */
            break;

        case PACKET_TYPE_SHUTDOWN:              /* shutdown */
            connection.is_open = 0;
            connection.is_connected = 0;
            break;

        case PACKET_TYPE_ACK2:                  /* ack of ack */
            break;

        case PACKET_TYPE_DROPREQ:               /* message drop request */
            break;

        case PACKET_TYPE_ERRSIG:                /* error signal */
            break;

        default:                                /* unsupported packet type */
            recv_buffer_write("Unknown message", 16);

        }
    } else {                                            /* data packet */

        if (packet.header._head1 & 0x80000000 &&
            packet.header._head1 & 0x40000000)      /* solo packet */
            recv_buffer_write(packet.data, PACKET_DATA_SIZE);

        else if (packet.header._head1 & 0x40000000) /* last packet */
            recv_buffer_write(packet.data, PACKET_DATA_SIZE);

        else if (packet.header._head1 & 0x80000000) /* first packet */
            recv_buffer_write(packet.data, -1);

        else                                        /* middle packet */
            recv_buffer_write(packet.data, -1);
    }
    return;
}
