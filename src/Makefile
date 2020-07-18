TARGET			= libudt-c.so
CC 				?= gcc
CC_FLAGS		?= -Wall -pedantic
C_FLAGS         = $(CC_FLAGS) -fPIC
LD_FLAGS		= -shared
INC_DIR			= ../include
INC				= ../include/config.h \
				  ../include/udt.h \
				  ../include/packet.h \
				  ../include/buffer.h \
				  ../include/util.h \
				  ../include/receiver.h \
				  ../include/core.h
OBJS			= api.o \
				  core.o \
				  packet.o \
				  buffer.o \
				  send_buffer.o \
				  recv_buffer.o \
				  receiver.o \
				  sender.o \
				  util.o

$(TARGET): 		$(OBJS)
				$(CC) $(C_FLAGS) $(LD_FLAGS) $(OBJS) -o $@

clean:
				rm -f *.o $(OBJS) $(TARGET)

$(OBJS):%.o:	%.c $(INC) Makefile
				$(CC) $(C_FLAGS) -I$(INC_DIR) -c $<
