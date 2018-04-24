#include "buffer.h"

static buffer_t buffer;

int recv_packet_buffer_write(packet_t *packet)
{
    return buffer_write_packet(&buffer, packet);
}

int recv_packet_buffer_read(packet_t *packet)
{
    return buffer_read_packet(&buffer, packet);
}
