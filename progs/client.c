#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <netdb.h>
#include "../src/udt.h"

#define HOST "127.0.0.1"
#define PORT 9000

int main(int argc, char *argv[])
{
    socket_t        sock;
    int             err;
    struct addrinfo hints,
                    *result;

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

    /* connect to server */
    if (connect(sock, result -> ai_addr, result -> ai_addrlen) == -1) {
        fprintf(stderr, "Could not connect to socket\n");
        exit(errno);
    } else {
        fprintf(stderr, "Connected\n");
    }

    /* send, recv */
    char buffer[1025];
    while (send(sock, buffer, 1024, 0)) {
        memset(buffer, 0, sizeof(buffer));
        sprintf(buffer, "this is the future man");
    }

    /* close the connection */
    udt_close(sock);
    return 0;
}
