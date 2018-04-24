#include <stdio.h>
#include <sys/socket.h>
#include <string.h>

#include "core.h"
#include "udt.h"
#include "packet.h"
#include "receiver.h"

void receiver_start (void *arg)
{
    conn_t *receiver = (conn_t *) arg;
    char buffer[1025];
    packet_t packet;

    memset(&packet, 0, sizeof(packet_t));
    while (recv(receiver -> sock, buffer, 1024, 0)) {
        packet_parse(packet);
        memset(&packet, 0, sizeof(packet_t));
    }
}
