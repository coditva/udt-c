TARGET			= libudt.so
CC 				= gcc
CC_FLAGS 		= -Wall -pedantic
OBJS			= main.o

$(TARGET): 		$(OBJS)
				$(CC) $(CC_FLAGS) $< -o $@

clean:
				rm -f *.o $(OBJS) $(TARGET)

$(OBJS):%.o:	%.c Makefile
				$(CC) $(CC_FLAGS) -I. -c $<
