# Makefile

CC = gcc
CFLAGS = `pkg-config --cflags gtk+-3.0` -Wall -O3
LDLIBS = `pkg-config --libs gtk+-3.0` -lm

EXE = bato test ../../pathfinding/graph ../../pathfinding/priority_queue ../../pathfinding/stack ../../pathfinding/astar

all: $(EXE) 

$(foreach f, $(EXE), $(eval $(f):))

.PHONY: clean

clean:
	${RM} $(EXE)

# END