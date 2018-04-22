CC 				= gcc
CC_FLAGS 		= -Wall -pedantic
SRC_DIR 	 	= src

INCLUDE_DIR 	= include
SRCS			= main.c
OBJS 			= $(SRCS:c=o)


.PHONY: 		all

all: 			$(OBJS)

clean:
				rm -f *.o $(OBJS)

$(OBJS):%.o:	$(SRC_DIR)/%.c $(INCLUDE_DIR)/%.h Makefile
				$(CC) $(CC_FLAGS) -I$(INCLUDE_DIR) -c $<
