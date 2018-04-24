#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <errno.h>

#include "udt.h"
#include "core.h"
#include "receiver.h"
#include "sender.h"
#include "util.h"

static conn_t connection;

int udt_bind (socket_t sock, sockaddr_t *addr, int len)
{
    int result = 0;

    result = bind(sock, (struct sockaddr *)addr, len);
    if (result == -1) return result;

    connection.sock = sock;
    connection.addr = *addr;
    connection.addrlen = len;

    /* TODO: execute these functions with threads */
    thread_start((thread_worker_t) receiver_start, (&connection));
    thread_start((thread_worker_t) sender_start, (&connection));

    return 0;
}
