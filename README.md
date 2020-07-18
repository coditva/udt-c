# UDT Implementation in C

[![Codacy Badge](https://api.codacy.com/project/badge/Grade/212e3f610f6149dca8e66b0e75e97abe)](https://app.codacy.com/app/UtkarshMe/udt-c?utm_source=github.com&utm_medium=referral&utm_content=UtkarshMe/udt-c&utm_campaign=badger)

An implementation of the **UDP-based Data Transfer (UDT)** protocol in C.
UDT is a much faster data transfer protocol than TCP and provides a socket
interface to send/receive data just like any other protocol.

The documentation can be found in the header files (see `include/udt.h`).

### How to
```bash
make        # compile
make clean  # cleanup
make BUILD_TYPE='debug'  # to create dev build with symbols for gdb

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
