CC 				?= gcc
CC_FLAGS 		?= -Wall -pedantic
CL_FLAGS		= -L../src -ludt-c -lpthread
INC				= ../include/udt.h
TARGETS			= server client sendfile recvfile

all				: $(TARGETS)

$(TARGETS):%	: %.o
				$(CC) $(CC_FLAGS) -I. $< -o $@ $(CL_FLAGS)

clean			:
				rm -f *.o $(OBJS) $(TARGETS)

$(OBJS):%.o:	%.c $(INC) Makefile
				$(CC) $(CC_FLAGS) -I../src $< -c
