#ifndef PACKET_H_R7ONXCYA
#define PACKET_H_R7ONXCYA

#include <inttypes.h>

#define MAX_DATA_SIZE 20

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


/* Extract packet data */
int         packet_is_control       (packet_t);
int         packet_is_data          (packet_t);
int32_t     packet_get_seq          (packet_t);
int16_t     packet_get_type         (packet_t);
int16_t     packet_get_ext_type     (packet_t);
int32_t     packet_get_msg_num      (packet_t);
int32_t     packet_get_ack_seq      (packet_t);
int32_t     packet_get_timestamp    (packet_t);

/* Convert packet to/from network layer */
void        packet_serialize        (packet_t *, int);
void        packet_deserialize      (packet_t *, int);

/* Packet creation/deletion */
packet_t*   packet_new              (char *, int); 
void        packet_delete           (packet_t); 

/* Parse packet */
void        packet_parse            (packet_t);


#define PACKET_TYPE_MASK 0x80000000     /* 32nd bit */
#define PACKET_SEQ_MASK  0x7FFFFFFF     /* 32nd bit */

#endif /* end of include guard: PACKET_H_R7ONXCYA */
