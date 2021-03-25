CC = gcc -fsanitize=address
CFLAGS = -Wall -Wextra -g
LDFLAGS =
LDLIBS =

SRC = graph.c priority_queue.c
OBJ = ${SRC:.c=.o}

all:

graph: graph.o

priority_queue: graph.o priority_queue.o

.PHONY: clean

clean:
	${RM} graph priority_queue
	${RM} ${OBJ}
