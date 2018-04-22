#include <unistd.h>
#include "udt.h"

int udt_close(socket_t sock)
{
    return close(sock);
}
