TARGET			= libudt.so
CC 				= gcc
CC_FLAGS 		= -Wall -pedantic -shared -fPIC
OBJS			= socket.o \
				  bind.o \
				  close.o \
				  connect.o \
				  listen.o \
				  accept.o \
				  io.o \
				  packet.o \
				  state.o

$(TARGET): 		$(OBJS)
				$(CC) $(CC_FLAGS) $(OBJS) -o $@

clean:
				rm -f *.o $(OBJS) $(TARGET)

$(OBJS):%.o:	%.c Makefile
				$(CC) $(CC_FLAGS) -I. -c $<
