#include "buffer.h"

static buffer_t buffer;

int recv_buffer_write(char *data, int len)
{
    return buffer_write(&buffer, data, len);
}

int recv_buffer_read(char *data, int len)
{
    return buffer_read(&buffer, data, len);
}
