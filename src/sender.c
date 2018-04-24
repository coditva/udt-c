#include <stdio.h>
#include <sys/socket.h>

#include "core.h"
#include "sender.h"
#include "buffer.h"

void sender_start (void *arg)
{
    /* TODO: CAN ONLY SEND TO AN ADDRESS IN UDP */

    /*conn_t *connection = (conn_t *) arg;*/
    char buffer[] = "This is a message";

    while (1) {
        if (send_buffer_read(buffer, sizeof(buffer))) {
            printf("Send: %s\n", buffer);
        }
    }
}
