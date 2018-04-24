#include <stdio.h>
#include <sys/socket.h>
#include <string.h>

#include "core.h"
#include "udt.h"
#include "packet.h"
#include "receiver.h"

void receiver_start (void *arg)
{
    conn_t *connection = (conn_t *) arg;
    packet_t packet;

    memset(&packet, 0, sizeof(packet_t));
    while (recvfrom(connection -> sock, &packet, sizeof(packet_t), 0,
           &(connection -> peer.addr), &(connection -> peer.addrlen))) {
        packet_parse(packet);
        memset(&packet, 0, sizeof(packet_t));
    }
}
