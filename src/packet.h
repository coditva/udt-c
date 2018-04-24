#ifndef PACKET_H_R7ONXCYA
#define PACKET_H_R7ONXCYA

#include <inttypes.h>

#define MAX_DATA_SIZE 20
#define MAX_PACKET_SIZE (MAX_DATA_SIZE + 4)

/**
 * The udt packet structure
 *
 * There are two kinds of packets: data and control which are distinguished
 * based on the value of control.
 * 0 - data packet
 * 1 - control packet
 *
 * Data packet header contains:
 *   sequence_number
 *   boundary order message_number
 *   time_stamp
 *
 * Control packet header contains:
 *   type ext_type
 *   ack_sequence_number
 *   time_stamp
 */
typedef struct {
    struct {

        /* header */
        union {
            uint32_t sequence_number;
            struct {
                uint16_t type;
                uint16_t ext_type;
            };
            uint32_t _head0;
        };
        union {
            uint32_t message_number;
            uint32_t ack_sequence_number;
            uint32_t _head1;
        };
        union {
            uint32_t timestamp;
            uint32_t _head2;
        };
        union {
            uint32_t id;
            uint32_t _head3;
        };

        /* data */
        uint32_t data[MAX_DATA_SIZE];
    };
} packet_t;

/**
 * Parse the given packet. Take appropriate action if control packet is
 * received. Fills up receiver buffer if data packet is received.
 *
 * @param   packet_t    The packet to be parsed
 */
void        packet_parse            (packet_t);

#endif /* end of include guard: PACKET_H_R7ONXCYA */
