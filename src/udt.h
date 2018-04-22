#ifndef UDT_H_JDNRQTZQ
#define UDT_H_JDNRQTZQ

#include <sys/types.h>
#include <arpa/inet.h>

typedef int socket_t;
typedef int af_type;
typedef int sock_type;

typedef struct sockaddr sockaddr_t;

int errno;

/**
 * Accept a new connection on a listening socket and return its file
 * descriptor.
 *
 * @param   socket_t    A listening socket
 * @param   sockaddr_t* This will be filled with the address of accepted socket
 * @param   int*        This will be set to the length of sockaddr
 * @return  socket_t    Socket file descriptor if success, -1 otherwise.
 */
socket_t    udt_accept  (socket_t, sockaddr_t *, int *);

/**
 * Bind the socket to the given address.
 *
 * @param   socket_t    A socket created with udt_socket()
 * @param   sockaddr_t* The address to bind to
 * @param   int         The length of the address
 */
int         udt_bind    (socket_t, sockaddr_t *, int);

/**
 * Close the socket.
 *
 * @param   socket_t    Socket to close
 * @return  int         0 on success, -1 otherwise
 */
int         udt_close   (socket_t);

/**
 * Connect to the server at the given address
 *
 * @param   socker_t    A socket created with udt_socket()
 * @param   sockaddr_t* The address of the server
 * @param   int         The length of sockaddress
 */
int         udt_connect (socket_t, const sockaddr_t *, int);

int         udt_startup ();

/**
 * Creates a new socket and returns it, if successful. If failed, return -1.
 *
 * @param   af_type     The type of internet family
 * @param   sock_type   The socket type
 * @return  socket_t    Socket file descriptor if success. -1 otherwise.
 */
socket_t    udt_socket  (af_type, sock_type, int);

int         udt_recv    (socket_t, char *, int, int);
/*int64_t     udt_sendfile(socker_t, fstream&, const int64_t, const int64_t,*/
                         /*const int);*/
/*int64_t     udt_recvfile(socker_t, fstream&, const int64_t, const int64_t,*/
                         /*const int);*/

#endif /* end of include guard: UDT_H_JDNRQTZQ */
