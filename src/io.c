#include <string.h>

#include "udt.h"
#include "packet.h"
#include "state.h"

int udt_recv(socket_t sock, char *buffer, int len, int flags)
{
    packet_t packet;
    state_t  state;
    int      num_read;

    while (1) {
        num_read = recv(sock, &packet, sizeof(packet_t), flags);
        if (num_read <= 0) return num_read;

        packet_deserialize(&packet, sizeof(packet_t));

        state.packet = packet;
        state.retval = 0;
        state_enter(state);

        memset(&packet, 0, sizeof(packet_t));
    }

    return 1;
}

int udt_send(socket_t sock, char *buffer, int len, int flags)
{
    packet_t *packet;
    int      num_sent;

    while (1) {
        packet = packet_new(buffer, len);
        packet_serialize(packet, sizeof(packet_t));

        num_sent = send(sock, packet, sizeof(packet_t), flags);
        if (num_sent <= 0) return num_sent;
    }

    return 1;
}
