CC 				= g++
CC_FLAGS 		= -Wall -pedantic

.PHONY			: all

all				:
				$(MAKE) --directory src
				$(MAKE) --directory progs

clean			:
				$(MAKE) --directory src clean
				$(MAKE) --directory progs clean
				rm -f *.o $(OBJS)
