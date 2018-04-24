#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <netdb.h>
#include "../include/udt.h"

#define HOST "127.0.0.1"
#define PORT "9000"

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
    /*hints.ai_socktype = SOCK_STREAM;*/

    if ((err = getaddrinfo(NULL, PORT, &hints, &result)) != 0) {
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

    freeaddrinfo(result);

    /* send, recv */
    char buffer[1025];
    char msg[] = "this is the future man";
    while (1) {
        sprintf(buffer, msg);
        if (udt_send(sock, buffer, sizeof(msg), 0) == -1)
            exit(1);
        printf("sent\n");
        memset(buffer, 0, sizeof(buffer));
        if (udt_recv(sock, buffer, sizeof(buffer), 0) == 0)
            exit(1);
        printf("recvd\n");
    }

    /* close the connection */
    udt_close(sock);
    return 0;
}
