#include <unistd.h>
#include <stdio.h>

#include "packet.h"
#include "buffer.h"

static buffer_t buffer;

int recv_buffer_init()
{
    return buffer_init(&buffer);
}

int recv_buffer_write(char *data, int len)
{
    return buffer_write(&buffer, data, len);
}

int recv_buffer_read(char *data, int len)
{
    return buffer_read(&buffer, data, len);
}

int64_t recv_file_buffer_read(int fd, int64_t *offset, int64_t size,
                              int64_t blocksize)
{
    char data[PACKET_DATA_SIZE];
    int retval = 0;
    int len = 0;
    int read;
    int bytes_to_write;

    if (fd < 0) return -1;

    while (size > 0) {

        read = buffer_read(&buffer, data, PACKET_DATA_SIZE);
        if (read == 0) continue;  /* keep polling until there is data */

        bytes_to_write = (size > PACKET_DATA_SIZE) ? PACKET_DATA_SIZE : size;
        len = pwrite(fd, &data, bytes_to_write, *offset);
        if (len < 1) return len;

        *offset += len;
        retval += len;
        size -= len;
    }

    return retval;
}
