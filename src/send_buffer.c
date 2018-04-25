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

    header._head0 = 0x00000000;
    header._head1 = 0x00000000;
    header._head2 = 0x00000000;
    header._head3 = 0x00000000;

    packet_new(&packet, &header, data, len);
    return send_packet_buffer_write(&packet);
}
