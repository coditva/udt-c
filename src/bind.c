#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <errno.h>

#include "udt.h"
#include "core.h"
#include "receiver.h"
#include "sender.h"

static conn_t connection;

int udt_bind (socket_t sock, sockaddr_t *addr, int len)
{
    int result = 0;

    result = bind(sock, (struct sockaddr *)addr, len);
    if (result == -1) return result;

    connection.sock = sock;

    /* TODO: execute these functions with threads */
    /*receiver_start(&connection);*/
    /*sender_start(&connection);*/

    return 0;
}
