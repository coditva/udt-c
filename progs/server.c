#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <netdb.h>

#include "../src/udt.h"
#include "../src/packet.h"
#include "../src/state.h"

#define BACKLOG 5
#define HOST "127.0.0.1"
#define PORT 9000

int main(int argc, char *argv[])
{
    socket_t        sock;
    int             err;
    struct addrinfo hints, *result;

    /* get address info */
    memset(&hints, 0, sizeof(hints));
    hints.ai_flags = AI_PASSIVE;
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_DGRAM;

    if ((err = getaddrinfo(NULL, "9000", &hints, &result)) != 0) {
        fprintf(stderr, "Error: %s\n", gai_strerror(err));
        exit(err);
    }

    /* create a socket */
    sock = udt_socket(result -> ai_family,
                      result -> ai_socktype,
                      result -> ai_protocol);
    if (sock == -1) {
        fprintf(stderr, "Could not create socket\n");
        exit(errno);
    }

    /* bind to address */
    if (udt_bind(sock, result -> ai_addr, result -> ai_addrlen) == -1) {
        fprintf(stderr, "Could not bind socket\n");
        exit(errno);
    } else {
        fprintf(stdout, "Active on %d\n", PORT);
    }

    freeaddrinfo(result);

    /* send, recv packets */
    packet_t packet;
    state_t  state;
    while (recv(sock, &packet, sizeof(packet_t), 0)) {
        packet_deserialize(&packet);
        state.packet = packet;
        state_enter(state);

        memset(&packet, 0, sizeof(packet));
        memset(&state, 0, sizeof(state_t));
    }

    /* send, recv */

    /* close connection */
    if (udt_close(sock) == -1) {
        fprintf(stderr, "Could not close socket\n");
        exit(errno);
    }

    return 0;
}
