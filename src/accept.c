#include <stdlib.h>
#include "udt.h"

socket_t udt_accept(socket_t sock, sockaddr_t *addr, int *addrlen)
{
    return accept(sock, (struct sockaddr *)addr, addrlen);
}
