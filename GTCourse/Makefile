INC := -IGraphAPI/include/

api: $(wildcard GraphAPI/include/*.h) $(wildcard GraphAPI/src/*.c)
	gcc -c $^ -o graph.o && ar rcs bin/libgraph.a graph.o $(INC)
