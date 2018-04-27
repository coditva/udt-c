#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "buffer.h"
#include "packet.h"

static buffer_t buffer;

int send_buffer_init()
{
    return buffer_init(&buffer);
}

int send_packet_buffer_write(packet_t *packet)
{
    return buffer_write_packet(&buffer, packet);
}

int send_packet_buffer_read(packet_t *packet)
{
    return buffer_read_packet(&buffer, packet);
}

int send_buffer_write(char *data, int len)
{
    packet_t packet;
    int size = 0;
    int seqnum;
    int boundary;
    int retval;
    char *buffer;

    size = len;
    retval = len;
    seqnum = 2142894844;  /* TODO: generate random number */
    buffer = data;
    boundary = PACKET_BOUNDARY_START;

    while (len > 0) {
        size = (len > PACKET_DATA_SIZE) ? PACKET_DATA_SIZE : len;
        len -= PACKET_DATA_SIZE;
        boundary |= (len > 0) ? PACKET_BOUNDARY_NONE : PACKET_BOUNDARY_END;

        packet_clear_header (packet);
        packet_set_data     (packet);
        packet_set_seqnum   (packet, seqnum++);
        packet_set_boundary (packet, boundary);
        packet_set_order    (packet, 1);
        packet_set_msgnum   (packet, 1);
        packet_set_timestamp(packet, 0x0000051c); /* TODO: calculate time */
        packet_set_id       (packet, 0x08c42c74); /* TODO: generate an id */

        packet_new(&packet, buffer, size);
        send_packet_buffer_write(&packet);

        buffer += size;
        boundary = PACKET_BOUNDARY_NONE;
    }

    packet_clear_header (packet);
    packet_set_ctrl     (packet);
    packet_set_type     (packet, PACKET_TYPE_ACK);
    packet_set_timestamp(packet, 0x0000051c); /* TODO: calculate time */
    packet_set_id       (packet, 0x08c42c74); /* TODO: generate an id */

    packet_new(&packet, NULL, 0);
    send_packet_buffer_write(&packet);

    return retval;
}

int send_file_buffer_write(int fd, int offset, int size, int blocksize)
{
			
    packet_t packet;

	off_t pos;	
    int retval;
    int seqnum;
	char *buffer;	
    int boundary;
	int readbytescount;
	int packet_dsize;

	pos			= offset;
    retval 		= size;
    seqnum 		= 2142894844;  /* TODO: generate random number */
    buffer 		= (char *) malloc (size);
    boundary 	= PACKET_BOUNDARY_START;	
	
	if (fd < 0 || pos < 0) return -1;

	packet_dsize = (blocksize > PACKET_DATA_SIZE) ? PACKET_DATA_SIZE : blocksize;
		
	while (size > 0)
    {
		
		lseek(fd, pos, SEEK_SET);
		readbytescount 	 = read(fd, buffer, packet_dsize);
		size			-= readbytescount;

        boundary = boundary | (size > 0) ? PACKET_BOUNDARY_NONE : PACKET_BOUNDARY_END;

        packet_clear_header (packet);
        packet_set_data     (packet);
        packet_set_seqnum   (packet, seqnum++);
        packet_set_boundary (packet, boundary);
        packet_set_order    (packet, 1);
        packet_set_msgnum   (packet, 1);
        packet_set_timestamp(packet, 0x0000051c); /* TODO: calculate time */
        packet_set_id       (packet, 0x08c42c74); /* TODO: generate an id */

        packet_new(&packet, buffer, readbytescount);
        send_packet_buffer_write(&packet);

        boundary = PACKET_BOUNDARY_NONE;
	
		pos += blocksize;
    }
		
	packet_clear_header (packet);
    packet_set_ctrl     (packet);
    packet_set_type     (packet, PACKET_TYPE_ACK);
    packet_set_timestamp(packet, 0x0000051c); /* TODO: calculate time */
    packet_set_id       (packet, 0x08c42c74); /* TODO: generate an id */

    packet_new(&packet, NULL, 0);
    send_packet_buffer_write(&packet);
				
    return retval; /* return total bytes sent */		
}
