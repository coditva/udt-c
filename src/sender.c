#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <stdio.h>

#include "core.h"
#include "sender.h"
#include "buffer.h"
#include "packet.h"

void sender_start (void *arg)
{
    conn_t *conn = (conn_t *) arg;
    packet_t packet;

    while (1) {
        if (conn -> is_open == 1 && send_packet_buffer_read(&packet)) {
            if (sendto(conn -> sock, &packet, sizeof(packet_t), 0,
                       &(conn -> addr), sizeof(sockaddr_t)) <= 0)
                exit(errno);

            /* shutdown message */
            if (packet.header._head0 == 1408)
                conn -> is_open = 0;

            memset(&packet, 0, sizeof(packet_t));
        }
    }
}
