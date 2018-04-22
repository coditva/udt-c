#include "udt.h"

int udt_bind (socket_t sock, sockaddr_t *addr, int len)
{
    return bind(sock, (struct sockaddr *)addr, len);
}
