CC = gcc
CFLAGS = `pkg-config --cflags gtk+-3.0` -O3 -Wall -Wextra -g
LDFLAGS =
LDLIBS = `pkg-config --libs gtk+-3.0` `sdl2-config --libs` -lSDL2_mixer -lm

SRC = pathfinding/graph.c pathfinding/priority_queue.c pathfinding/stack.c pathfinding/astar.c GUImove/src/bato.c GUImove/src/bot.c GUImove/src.bot.c
OBJ = ${SRC:.c=.o}

all: GUImove/src/bato

GUImove/src/bato: pathfinding/graph.o pathfinding/priority_queue.o pathfinding/stack.o pathfinding/astar.o GUImove/src/bato.o GUImove/src/bot.o

astar: pathfinding/graph.o pathfinding/priority_queue.o pathfinding/stack.o pathfinding/astar.o

graph: pathfinding/graph.o

priority_queue: pathfinding/graph.o pathfinding/priority_queue.o

stack: pathfinding/graph.o pathfinding/stack.o

.PHONY: clean

clean:
	${RM} pathfinding/graph pathfinding/priority_queue pathfinding/stack pathfinding/astar GUImove/src/bato
	${RM} ${OBJ}
