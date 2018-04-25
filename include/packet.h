#ifndef PACKET_H_R7ONXCYA
#define PACKET_H_R7ONXCYA

#include <inttypes.h>


#define PACKET_HEADER_SIZE 4
#define PACKET_DATA_SIZE 200


#define PACKET_MASK_CTRL 0x80000000
#define PACKET_MASK_SEQ  0x7FFFFFFF
#define PACKET_MASK_TYPE 0x7FFF0000

#define PACKET_TYPE_HANDSHAKE 0xFFFFFFFF
#define PACKET_TYPE_KEEPALIVE 0xFFF1FFFF
#define PACKET_TYPE_ACK       0xFFF2FFFF
#define PACKET_TYPE_NAK       0xFFF3FFFF
#define PACKET_TYPE_CONGDELAY 0xFFF4FFFF
#define PACKET_TYPE_SHUTDOWN  0xFFF5FFFF
#define PACKET_TYPE_ACK2      0xFFF6FFFF
#define PACKET_TYPE_DROPREQ   0xFFF7FFFF
#define PACKET_TYPE_ERRSIG    0xFFF8FFFF


#define packet_is_control(PACKET) \
    ((PACKET).header._head0 & PACKET_MASK_CTRL)

#define packet_set_data(PACKET) \
    ((PACKET).header._head0 &= 0x7FFFFFFF)

#define packet_clear_header(PACKET) \
    ((PACKET).header._head0 = 0x00000000); \
    ((PACKET).header._head1 = 0x00000000); \
    ((PACKET).header._head2 = 0x00000000); \
    ((PACKET).header._head3 = 0x00000000)

#define packet_set_ctrl(PACKET) \
    ((PACKET).header._head0 |= PACKET_MASK_CTRL)

#define packet_set_seqnum(PACKET, SEQNUM) \
    ((PACKET).header._head0 &= 0x80000000); \
    ((PACKET).header._head0 |= (SEQNUM))

#define packet_set_boundary(PACKET, BOUNDARY) \
    ((PACKET).header._head1 &= 0x30000000); \
    ((PACKET).header._head1 |= (BOUNDARY << 30))

#define packet_set_order(PACKET, ORDER) \
    ((PACKET).header._head1 &= (ORDER) ? 0x00000000 : 0x00000000 )

#define packet_set_msgnum(PACKET, MSGNUM) \
    ((PACKET).header._head1 &= 0xE0000000); \
    ((PACKET).header._head1 |= (MSGNUM))

#define packet_get_type(PACKET) \
    ((PACKET).header._head0 & PACKET_MASK_TYPE)

#define packet_set_type(PACKET, PACKET_TYPE) \
    ((PACKET).header._head0 &= (PACKET_TYPE))


/**
 * The udt packet header structure
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
} packet_header_t;


/**
 * The udt packet consists of a header and the data. The header is of size
 * 4 * 32 bits and the data can be of maximum size according to the
 * implementation.
 */
typedef struct {
    packet_header_t header;
    char            data[PACKET_DATA_SIZE];
} packet_t;

/**
 * Parse the given packet. Take appropriate action if control packet is
 * received. Fills up receiver buffer if data packet is received.
 *
 * @param   packet_t    The packet to be parsed
 */
void        packet_parse    (packet_t);

int         packet_new      (packet_t *, packet_header_t *, char *, int);

#endif /* end of include guard: PACKET_H_R7ONXCYA */
