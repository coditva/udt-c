#ifndef STATE_H_FCRM38WG
#define STATE_H_FCRM38WG

#include "packet.h"

typedef struct _state state_t;
typedef void (*state_execute_t) (state_t *);

struct _state{
    packet_t packet;
    state_execute_t execute;
    int retval;
};

void state_enter(state_t);

#endif /* end of include guard: STATE_H_FCRM38WG */
