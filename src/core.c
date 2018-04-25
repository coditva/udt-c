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
