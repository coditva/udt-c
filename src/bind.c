#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <errno.h>

#include "udt.h"
#include "core.h"
#include "receiver.h"

static conn_t sender, receiver;

int udt_bind (socket_t sock, sockaddr_t *addr, int len)
{
    int result = 0;

    result = bind(sock, (struct sockaddr *)addr, len);
    if (result == -1) return result;

    sender.sock = sock;
    receiver.sock = sock;

    receiver_start(&receiver);
    return -1;
}
