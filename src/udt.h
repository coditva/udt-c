#ifndef UDT_H_JDNRQTZQ
#define UDT_H_JDNRQTZQ

#include <sys/types.h>

typedef int socket_t;

typedef struct sockaddr sockaddr_t;

socket_t    accept  (socket_t, sockaddr_t *, int *);
int         bind    (socket_t, sockaddr_t *, int *);
int         close   (socket_t);
int         connect (socket_t, const sockaddr_t *, int *);
int         startup ();
socket_t    socket  (int, int, int);
int         recv    (socket_t, char *, int, int);
//int64_t     sendfile(socker_t, fstream&, const int64_t, const int64_t,
                     //const int);
//int64_t     recvfile(socker_t, fstream&, const int64_t, const int64_t,
                     //const int);

#endif /* end of include guard: UDT_H_JDNRQTZQ */
