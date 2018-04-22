CC 				= gcc
CC_FLAGS 		= -Wall -pedantic
OBJS			= server.o client.o
TARGETS			= server client

all				: $(TARGETS)

$(TARGETS):%	: %.o
				$(CC) $(CC_FLAGS) -I. $< -o $@

clean			:
				rm -f *.o $(OBJS) $(TARGETS)

$(OBJS):%.o		: %.c Makefile
				$(CC) $(CC_FLAGS) -I../src $< -c
