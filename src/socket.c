#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <errno.h>

#include "udt.h"

socket_t udt_socket(af_type af, sock_type type, int protocol)
{
    if (type != SOCK_STREAM && type != SOCK_DGRAM) {
        errno = 5003;  /* bad params */
        return -1;
    }

    return socket(af, type, 0);
}
