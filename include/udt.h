#ifndef UDT_H_JDNRQTZQ
#define UDT_H_JDNRQTZQ

#include <sys/types.h>
#include <arpa/inet.h>
#include <errno.h>

typedef int socket_t;
typedef int af_type;
typedef int sock_type;

typedef struct sockaddr sockaddr_t;


/**
 * Initialize the udt sockets
 *
 * @return  int         0 on success, -1 otherwise
 */
int         udt_startup ();

/**
 * Creates a new socket and returns it, if successful. If failed, return -1.
 *
 * @param   af_type     The type of internet family
 * @param   sock_type   The socket type
 * @return  socket_t    Socket file descriptor if success. -1 otherwise.
 */
socket_t    udt_socket  (af_type, sock_type, int);

/**
 * Bind the socket to the given address.
 *
 * @param   socket_t    A socket created with udt_socket()
 * @param   sockaddr_t* The address to bind to
 * @param   int         The length of the address
 * @return  int         0 on success, -1 otherwise
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
 * @return  int         0 on success, -1 otherwise
 */
int         udt_connect (socket_t, const sockaddr_t *, int);

/**
 * Listen on the given socket for given number of connections
 *
 * @param   socker_t    A socket created with udt_socket()
 * @param   int         The maximum number of connections for the socket
 * @return  int         0 on success, -1 otherwise
 */
int         udt_listen  (socket_t, int);

/**
 * Get a connection on the given socket
 *
 * @param   socker_t    A socket listening for connections
 * @param   sockaddr_t* The address of the connection
 * @param   int*        The length of sockaddress
 * @return  int         0 on success, -1 otherwise
 */
int         udt_accept  (socket_t, sockaddr_t *, int *);

/**
 * Receive data from a socket
 *
 * @param   socket_t    The socket to receive from
 * @param   char*       Pointer to a preallocated memory buffer
 * @param   int         Maximum length of the buffer
 * @param   flags       Flags
 * @return  int         Size of the message
 */
int         udt_recv    (socket_t, char *, int, int);

/**
 * Send data to a socket
 *
 * @param   socket_t    The socket to send to
 * @param   char*       The string to send
 * @param   int         Length of the message
 * @param   flags       Flags
 * @return  int         Size of the message
 */
int         udt_send    (socket_t, char *, int, int);

/**
 * Receive a file from the socket
 *
 * @param   socket_t    The socket to receive from
 * @param   void*       Pointer to the file to store incoming data
 * @param   int64_t     The offset position to store. After transfer, contains
 *                      new offset
 * @param   int64_t     The total size to be received
 * @param   int         The size of data block
 * @return  int64_t     Size of data sent, -1 on error
 */
int64_t     udt_recvfile(socket_t, void *, int64_t *, int64_t, int);

/**
 * Send a file to the socket
 *
 * @param   socket_t    The socket to send to
 * @param   void*       The file buffer to send
 * @param   int64_t     The offset position to read data
 * @param   int64_t     The total size to be sent
 * @param   int         The size of data block
 * @return  int64_t     Size of data sent, -1 on error
 */
int64_t     udt_sendfile(socket_t, void *, int64_t, int64_t, int);

#endif /* end of include guard: UDT_H_JDNRQTZQ */
