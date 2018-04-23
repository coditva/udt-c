#include "udt.h"
#include "packet.h"
#include "state.h"

int udt_recv(socket_t sock, char *buffer, int len, int flags)
{
    packet_t packet;
    state_t  state;

    while (1) {
        recv(sock, &packet, sizeof(packet_t), flags);

        packet_deserialize(&packet);

        state.packet = packet;
        state.retval = 0;
        state_enter(state);

        if (state.retval == 0) {
            return 0;
        }
    }

    return 0;
}

int udt_send(socket_t sock, char *buffer, int len, int flags)
{
    return send(sock, buffer, len, flags);
}
