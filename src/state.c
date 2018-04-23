#include <stdio.h>

#include "state.h"
#include "packet.h"

void state_handshake(state_t *);

void state_enter(state_t state) {

    if (packet_is_control(state.packet)) {
        switch (packet_get_seq(state.packet)) {

            /* handshake */
            case 0:
                fprintf(stderr, "log: Handshake packet received\n");
                state.execute = state_handshake;
                break;

            /* keep-alive */
            case 1:
                fprintf(stderr, "log: Handshake packet received\n");
                break;

            /* ack */
            case 2:
                fprintf(stderr, "log: Ack packet received\n");
                break;

            /* nak */
            case 3:
                fprintf(stderr, "log: Nak packet received\n");
                break;

            /* congestion-delay warning */
            case 4:
                fprintf(stderr, "log: Congestion-delay packet received\n");
                break;

            /* shutdown */
            case 5:
                fprintf(stderr, "log: Shutdown packet received\n");
                break;

            /* ack of ack */
            case 6:
                fprintf(stderr, "log: Ack-squared packet received\n");
                break;

            /* message drop request */
            case 7:
                fprintf(stderr, "log: Message drop request packet received\n");
                break;

            /* error signal from peer */
            case 8:
                fprintf(stderr, "log: Error signal packet received\n");
                break;

            default:
                fprintf(stderr, "log: Unknown packet receiced\n");
        }
    }

    state.execute(&state);
    if (state.retval == 1) {
        fprintf(stderr, "Error!\n");
    }
}

void state_handshake(state_t *state)
{
    fprintf(stderr, "Hand shaken\n");
    state -> retval = 1;
}
