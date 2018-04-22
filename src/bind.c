#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <errno.h>

#include "udt.h"

int udt_bind (socket_t sock, sockaddr_t *addr, int len)
{
    return bind(sock, (struct sockaddr *)addr, len);
}
