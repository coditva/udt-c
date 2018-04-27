#include <pthread.h>
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
    /* TODO: implement this */
    return 0;
}
