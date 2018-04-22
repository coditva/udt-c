#ifndef PACKET_H_R7ONXCYA
#define PACKET_H_R7ONXCYA

#include <inttypes.h>


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
    union {
        int32_t sequence_number;
        struct {
            int16_t type;
            int16_t ext_type;
        };
    };
    union {
        int32_t message_number;
        int32_t ack_sequence_number;
    };
    int32_t timestamp;
} packet_t;


/* Functions to extract various packet params */

int     packet_is_control   (packet_t);
int     packet_is_data      (packet_t);
int32_t packet_get_seq      (packet_t);
int16_t packet_get_type     (packet_t);
int16_t packet_get_ext_type (packet_t);
int32_t packet_get_msg_num  (packet_t);
int32_t packet_get_ack_seq  (packet_t);
int32_t packet_get_timestamp(packet_t);

#endif /* end of include guard: PACKET_H_R7ONXCYA */
