#include <unistd.h>

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

int64_t recv_file_buffer_read(int fd, int64_t *offset, int64_t size, int64_t blocksize)
{
    char data[PACKET_DATA_SIZE];
    int retval = 0;
    int len = 0;

    if (fd < 0) return -1;

    while (size > 0) {
        buffer_read(&buffer, data, PACKET_DATA_SIZE);
        len = pwrite(fd, &data, PACKET_DATA_SIZE, *offset);
        if (len < 0) return -1;

        retval += len;
        size -= len;
    }

    return retval;
}
