#include "buffer.h"

static buffer_t buffer;

int send_buffer_write(char *data, int len)
{
    return buffer_write(&buffer, data, len);
}

int send_buffer_read(char *data, int len)
{
    return buffer_read(&buffer, data, len);
}
