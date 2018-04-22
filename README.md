# Complementary UDT Implementation
A complementary implementation of the UDT protocol that can communicate with any existing UDT implementation to provide a custom API.

### How to
```bash
make        # compile
make clean  # cleanup

export LD_LIBRARY_PATH=./src/:$LD_LIBRARY_PATH  # export the library path

./progs/server  # start the server
./progs/client  # start the client
```

### License
MIT
