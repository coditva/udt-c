#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <netdb.h>
#include <fcntl.h>
#include <unistd.h>
#include "../include/udt.h"

#define HOST "127.0.0.1"
#define PORT "8000"
#define BUFFER_SIZE 10240

int main(int argc, char *argv[])
{
    socket_t        sock;
    int             err;
    struct addrinfo hints,
                    *result;

    udt_startup();

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
    if (udt_connect(sock, result -> ai_addr, result -> ai_addrlen) == -1) {
        fprintf(stderr, "Could not connect to socket\n");
        exit(errno);
    } else {
        fprintf(stderr, "Connected\n");
    }

    freeaddrinfo(result);

    /* send, recv */
    char reqfile[BUFFER_SIZE];
    char filename[BUFFER_SIZE];
    printf("\n\tGet file: ");
    scanf("%s", reqfile);
    printf("\tSave as: ");
    scanf("%s", filename);
    udt_send(sock, reqfile, strlen(reqfile), 0);

    /* send file */
    int filefd = open(filename, O_WRONLY | O_TRUNC | O_CREAT);
    int64_t offset = 0;
    if (filefd < -1) return 2;
    if (udt_recvfile(sock, filefd, &offset, 10, 0) < 0) return 1;
    close(filefd);

    printf("Disconnected\n");

    /* close the connection */
    udt_close(sock);
    return 0;
}
