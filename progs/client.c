#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "udt.h"

#define HOST "127.0.0.1"
#define PORT 9000

int main(int argc, char *argv[])
{
    sockaddr_t  addr;
    socket_t    sock;

    /* create a socket */
    sock = udt_socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        fprintf(stderr, "Could not create socket\n");
        exit(errno);
    }

    /* connect to server */
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port   = PORT;
    inet_pton(addr.sin_family, HOST, &(addr.sin_addr));
    if (connect(sock, (struct sockaddr *)&addr, sizeof(addr)) == -1) {
        fprintf(stderr, "Could not connect to socket\n");
        exit(errno);
    }

    /* send, recv */

    /* close the connection */
    udt_close(sock);
    return 0;
}
