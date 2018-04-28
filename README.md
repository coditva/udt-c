# UDT Implementation in C
An implementation of the **UDP-based Data Transfer (UDT)** protocol in C.
UDT is a much faster data transfer protocol than TCP and provides a socket
interface to send/receive data just like any other protocol.

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


### References

- Yunhong Gu and Robert L. Grossman, UDT: UDP-based Data Transfer for High-Speed Wide Area Networks, Computer Networks (Elsevier). Volume 51, Issue 7. May 2007.
- UDT Implementation in C++ : [http://udt.sourceforge.net/software.html](http://udt.sourceforge.net/software.html).
- UDT Manual : [http://udt.sourceforge.net/udt4/](http://udt.sourceforge.net/udt4/).

### License
MIT
