INC := -Iinclude/

all: $(wildcard include/*.h) $(wildcard src/*.c)
	gcc -c $^ -o graph.o && ar rcs bin/libgraph.a graph.o $(INC)
