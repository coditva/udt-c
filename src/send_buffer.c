#include "buffer.h"
#include "packet.h"

static buffer_t buffer;

int send_buffer_init()
{
    return buffer_init(&buffer);
}

int send_packet_buffer_write(packet_t *packet)
{
    return buffer_write_packet(&buffer, packet);
}

int send_packet_buffer_read(packet_t *packet)
{
    return buffer_read_packet(&buffer, packet);
}

int send_buffer_write(char *data, int len)
{
    packet_t new_packet;
    packet_t packet;

    packet_clear_header (packet);
    packet_set_data     (packet);
    packet_set_seqnum   (packet, 2142894844); /* TODO: generate random number */
    packet_set_boundary (packet, PACKET_BOUNDARY_SOLO);
    packet_set_order    (packet, 0);
    packet_set_msgnum   (packet, 1);
    packet_set_timestamp(packet, 0x0000051c); /* TODO: calculate time */
    packet_set_id       (packet, 0x08c42c74); /* TODO: generate an id */

    packet_new(&new_packet, &packet.header, data, len);
    return send_packet_buffer_write(&new_packet);
}
