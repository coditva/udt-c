#include <string.h>
#include <arpa/inet.h>
#include "packet.h"

int packet_is_data(packet_t packet)
{
    return (packet.sequence_number & PACKET_TYPE_MASK) ? 0 : 1;
}

int packet_is_control(packet_t packet)
{
    return (packet.sequence_number & PACKET_TYPE_MASK) ? 1 : 0;
}


int32_t packet_get_seq (packet_t packet)
{
    return (packet.sequence_number & PACKET_SEQ_MASK);
}

void packet_deserialize(packet_t *packet)
{
    packet -> _head0 = ntohl(packet -> _head0);
    packet -> _head1 = ntohl(packet -> _head1);
    packet -> _head2 = ntohl(packet -> _head2);
}
