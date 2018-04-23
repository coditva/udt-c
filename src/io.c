#include <string.h>

#include "udt.h"
#include "packet.h"
#include "state.h"

int udt_recv(socket_t sock, char *buffer, int len, int flags)
{
    packet_t packet;
    state_t  state;

    while (1) {
        recv(sock, &packet, sizeof(packet_t), flags);
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
    return send(sock, buffer, len, flags);
}
