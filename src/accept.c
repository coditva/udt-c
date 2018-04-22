#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <errno.h>

#include <stdlib.h>
#include "udt.h"

socket_t udt_accept(socket_t sock, sockaddr_t *addr, int *addrlen)
{
    return accept(sock, (struct sockaddr *)addr, (socklen_t *)addrlen);
}
