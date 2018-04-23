#ifndef STATE_H_FCRM38WG
#define STATE_H_FCRM38WG

#include "packet.h"

typedef struct {
    packet_t packet;
} state_t;

void state_enter(state_t);

#endif /* end of include guard: STATE_H_FCRM38WG */
