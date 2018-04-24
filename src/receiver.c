#include <stdio.h>
#include <sys/socket.h>

#include "core.h"
#include "udt.h"
#include "receiver.h"

void receiver_start (conn_t *receiver)
{
    char buffer[1025];
    while (recv(receiver -> sock, buffer, 1024, 0)) {
        printf("Got a packet\n");
    }
}
