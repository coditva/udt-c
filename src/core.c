#include "core.h"
#include "packet.h"
#include "buffer.h"

extern conn_t connection;

void handshake_init()
{
    packet_t packet;

    packet_new_handshake(&packet);
    send_packet_buffer_write(&packet);
}

void handshake_terminate()
{
    connection.is_connected = 1;
}

void connection_close()
{
    packet_t packet;

    packet_clear_header (packet);
    packet_set_ctrl     (packet);
    packet_set_type     (packet, PACKET_TYPE_SHUTDOWN);

    packet_new(&packet, NULL, 0);
    send_packet_buffer_write(&packet);
}
