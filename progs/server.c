#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "udt.h"

#define BACKLOG 5
#define HOST "127.0.0.1"
#define PORT 9000

int main(int argc, char *argv[])
{
    sockaddr_t  addr;
    sockaddr_t  conn_addr;
    int         conn_addr_len;
    socket_t    sock;
    socket_t    conn;

    /* create a socket */
    sock = udt_socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        fprintf(stderr, "Could not create socket\n");
        exit(errno);
    }

    /* bind to address */
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port   = PORT;
    inet_pton(addr.sin_family, HOST, &(addr.sin_addr));
    if (udt_bind(sock, &addr, sizeof(addr)) == -1) {
        fprintf(stderr, "Could not bind socket\n");
        exit(errno);
    }

    /* start listening */
    if (listen(sock, BACKLOG) == -1) {
        fprintf(stderr, "Could not listen on socket\n");
        exit(errno);
    } else {
        fprintf(stderr, "Listening on %d\n", PORT);
    }

    /* accept a new connection */
    conn = udt_accept(sock, &conn_addr, &conn_addr_len);
    if (conn == -1) {
        fprintf(stderr, "Could not accept connection\n");
        exit(errno);
    } else {
        fprintf(stderr, "New connection: :%d\n", conn_addr.sin_port);
    }

    /* send, recv */

    /* close connection */
    if (udt_close(sock) == -1) {
        fprintf(stderr, "Could not close socket\n");
        exit(errno);
    }

    return 0;
}
