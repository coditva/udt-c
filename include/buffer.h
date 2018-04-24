#ifndef BUFFER_H_IBSOFJRY
#define BUFFER_H_IBSOFJRY

typedef struct _block block_t;
struct _block {
    char *data;
    int len;
    block_t *next;
};

typedef struct _buffer buffer_t;
struct _buffer {
    block_t *first;
    block_t *last;
    int size;
};

int buffer_write(buffer_t *, char *, int);
int buffer_read(buffer_t *, char *, int);

int send_buffer_write(char *data, int len);
int send_buffer_read(char *data, int len);

int recv_buffer_write(char *data, int len);
int recv_buffer_read(char *data, int len);

#endif /* end of include guard: BUFFER_H_IBSOFJRY */
