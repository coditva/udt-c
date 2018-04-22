TARGET			= libudt.so
CC 				= gcc
CC_FLAGS 		= -Wall -pedantic -shared
OBJS			= accept.o

$(TARGET): 		$(OBJS)
				$(CC) $(CC_FLAGS) $< -o $@

clean:
				rm -f *.o $(OBJS) $(TARGET)

$(OBJS):%.o:	%.c Makefile
				$(CC) $(CC_FLAGS) -I. -c $<
