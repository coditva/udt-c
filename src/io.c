#include <string.h>

#include "udt.h"
#include "packet.h"
#include "state.h"
#include "buffer.h"

int udt_recv(socket_t sock, char *buffer, int len, int flags)
{
    return recv_buffer_read(buffer, len);
}

int udt_send(socket_t sock, char *buffer, int len, int flags)
{
    return send_buffer_write(buffer, len);
}
