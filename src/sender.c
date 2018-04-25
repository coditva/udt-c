#include <string.h>
#include <sys/socket.h>

#include "core.h"
#include "sender.h"
#include "buffer.h"

void sender_start (void *arg)
{
    conn_t *conn = (conn_t *) arg;
    packet_t packet;

    memset(&packet, 0, sizeof(packet_t));
    while (1) {
        if (send_packet_buffer_read(&packet)) {
            sendto(conn -> sock, &packet, sizeof(packet_t), 0,
                   &(conn -> addr), conn -> addrlen);
            memset(&packet, 0, sizeof(packet_t));
        }
    }
}
