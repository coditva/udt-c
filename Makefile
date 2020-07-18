CC				= gcc
CC_FLAGS 		?= -Wall -pedantic

BUILD_TYPE      ?= 'debug'

ifeq ($(BUILD_TYPE), 'debug')
	CC_FLAGS := $(CC_FLAGS) -g
endif

.PHONY			: all

all				:
				$(MAKE) --directory src CC_FLAGS="${CC_FLAGS}" CC="${CC}"
				$(MAKE) --directory progs CC_FLAGS="${CC_FLAGS}" CC="${CC}"

clean			:
				$(MAKE) --directory src clean
				$(MAKE) --directory progs clean
				rm -f *.o $(OBJS)
