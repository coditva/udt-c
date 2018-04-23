#ifndef STATE_H_FCRM38WG
#define STATE_H_FCRM38WG

#include "udt.h"
#include "packet.h"

typedef struct _state state_t;
typedef void (*state_execute_t) (state_t *);

struct _state{
    int retval;

    socket_t sock;

    packet_t req_packet;
    packet_t res_packet;

    sockaddr_t sock_addr;
    sockaddr_t peer_addr;

    state_execute_t execute;
};

static state_t state;

void state_enter(state_t);

#endif /* end of include guard: STATE_H_FCRM38WG */
