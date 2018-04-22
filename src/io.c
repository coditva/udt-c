#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <errno.h>

#include "udt.h"

int udt_recv(socket_t sock, char *buffer, int len, int flags)
{
    return recv(sock, buffer, len, flags);
}

int udt_send(socket_t sock, char *buffer, int len, int flags)
{
    return send(sock, buffer, len, flags);
}
