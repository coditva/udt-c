#include <stdlib.h>
#include <stdio.h>
#include "udt.h"

int main(int argc, char *argv[])
{
    socket_t sock = udt_socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        fprintf(stderr, "Could not create socket\n");
        exit(errno);
    }

    return 0;
}
