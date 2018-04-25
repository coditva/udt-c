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
    packet_header_t header;
    packet_t packet;

    packet_clear_header (packet);
    packet_set_data     (packet);
    packet_set_seqnum   (packet, 123412); /* TODO: generate random number */
    packet_set_boundary (packet, 0);
    packet_set_order    (packet, 0);
    packet_set_msgnum   (packet, 0);

    packet_new(&packet, &header, data, len);
    return send_packet_buffer_write(&packet);
}
