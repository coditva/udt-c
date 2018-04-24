#include <stdio.h>
#include <sys/socket.h>

#include "core.h"
#include "sender.h"
#include "buffer.h"

void sender_start (void *arg)
{
    /* TODO: CAN ONLY SEND TO AN ADDRESS IN UDP */

    /*conn_t *connection = (conn_t *) arg;*/
    packet_t packet;

    while (1) {
        if (send_packet_buffer_read(&packet)) {
            printf("Send: %s\n", packet.data);
        }
    }
}
