# Complementary UDT Implementation
A complementary implementation of the UDT protocol that can communicate with any existing UDT implementation to provide a custom API.

### How to
```bash
make        # compile
make clean  # cleanup

export LD_LIBRARY_PATH=./src/:$LD_LIBRARY_PATH  # export the library path

progs/server  # start the server
progs/client  # start the client

progs/sendfile  # start the sendfile server
progs/recvfile "file/to/get" "file/to/saveas"  # receive the file
```

### Progress
 - [x] Implement architecture.
 - [x] Implement basic API.
 - [x] Implement handshake.
 - [x] Use threads for sender/receiver.
 - [x] Implement data packet handling.
 - [x] Implement `sendfile`, `recvfile`.
 - [ ] Implement timer and use it to send various packets.
 - [ ] Make this work with an existing UDT implementation.
 - [ ] Implement a congestion control algorithm.


### Bugs, suggestions
Please report bugs, suggestions [here](https://github.com/utkarshme/udt-c/issues).

### License
MIT
