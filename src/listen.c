#include "udt.h"

int udt_listen(socket_t sock, int backlog)
{
    return listen(sock, backlog);
}
