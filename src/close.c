#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <errno.h>

#include <unistd.h>
#include "udt.h"

int udt_close(socket_t sock)
{
    return close(sock);
}
