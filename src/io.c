#include <string.h>

#include "udt.h"
#include "packet.h"
#include "buffer.h"

int udt_recv(socket_t sock, char *buffer, int len, int flags)
{
    int num_read;
    do {
        num_read = recv_buffer_read(buffer, len);
    } while (num_read == 0);

    return num_read;
}

int udt_send(socket_t sock, char *buffer, int len, int flags)
{
    return send_buffer_write(buffer, len);
}
