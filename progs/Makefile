CC 				= gcc
CC_FLAGS 		= -Wall -pedantic
CL_FLAGS		= -L../src -ludt-c
INC				= ../src/udt.h \
				  ../src/packet.h \
				  ../src/state.h
OBJS			= server.o client.o
TARGETS			= server client

all				: $(TARGETS)

$(TARGETS):%	: %.o
				$(CC) $(CC_FLAGS) -I. $< -o $@ $(CL_FLAGS)

clean			:
				rm -f *.o $(OBJS) $(TARGETS)

$(OBJS):%.o:	%.c $(INC) Makefile
				$(CC) $(CC_FLAGS) -I../src $< -c
