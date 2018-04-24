#ifndef CORE_H_7KCLGLUV
#define CORE_H_7KCLGLUV

#include "udt.h"

typedef struct {
    socket_t sock;
    sockaddr_t addr;
    int addrlen;
    int is_open;
} conn_t;

#endif /* end of include guard: CORE_H_7KCLGLUV */
