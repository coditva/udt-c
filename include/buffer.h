#ifndef BUFFER_H_IBSOFJRY
#define BUFFER_H_IBSOFJRY

#include <pthread.h>
#include "packet.h"

typedef struct _block block_t;
struct _block {
    char *data;
    int len;
    block_t *next;
};

typedef struct _packet_block packet_block_t;
struct _packet_block {
    packet_t packet;
    int len;
    packet_block_t *next;
};

typedef struct _buffer buffer_t;
struct _buffer {
    void *first;
    void *last;
    int size;
    pthread_mutex_t mutex;
};

int buffer_init         (buffer_t *);
int send_buffer_init    ();
int recv_buffer_init    ();

int buffer_write        (buffer_t *, char *, int);
int buffer_write_packet (buffer_t *, packet_t *);
int buffer_read         (buffer_t *, char *, int);
int buffer_read_packet  (buffer_t *, packet_t *);

int recv_buffer_write   (char *data, int len);
int recv_buffer_read    (char *data, int len);

int send_buffer_write           (char *data, int len);
int send_packet_buffer_write    (packet_t *);
int send_packet_buffer_read     (packet_t *);

#endif /* end of include guard: BUFFER_H_IBSOFJRY */
