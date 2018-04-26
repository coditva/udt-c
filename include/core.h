#ifndef CORE_H_7KCLGLUV
#define CORE_H_7KCLGLUV

#include "udt.h"

typedef struct {
    socket_t sock;
    struct {
        sockaddr_t addr;
        unsigned int addrlen;
    };
    int is_open;
    int is_connected;
    int is_client;
    int type;
} conn_t;

conn_t connection;

void    handshake_init      ();
void    handshake_terminate ();

void    connection_close    ();

#endif /* end of include guard: CORE_H_7KCLGLUV */
