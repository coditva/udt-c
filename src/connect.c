#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <errno.h>

#include "udt.h"

int udt_connect(socket_t sock, const sockaddr_t *addr, int len)
{
    return connect(sock, addr, len);
}
