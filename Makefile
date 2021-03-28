CC = gcc -fsanitize=address
CFLAGS = -Wall -Wextra -g
LDFLAGS =
LDLIBS = -lm

SRC = graph.c priority_queue.c stack.c astar.c
OBJ = ${SRC:.c=.o}

all:

astar: graph.o priority_queue.o stack.o astar.o

graph: graph.o

priority_queue: graph.o priority_queue.o

stack: graph.o stack.o

.PHONY: clean

clean:
	${RM} graph priority_queue stack astar
	${RM} ${OBJ}
