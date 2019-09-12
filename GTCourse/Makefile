INC := -IGraphAPI/include/

objects: $(wildcard GraphAPI/src/*.c) $(wildcard GraphAPI/include/*.h)
	gcc -c GraphAPI/src/graph.c $(INC)

api: objects
	ld -shared -o lib/libgraph.so $(wildcard *.o) -ldl

test: $(wildcard Test/include/*.h) $(wildcard Test/src/*.c) lib/libgraph.so
	gcc -L/home/alanhdiniz/Documentos/c/GraphTheory/GTCourse/lib/libgraph.so $(INC) -o bin/test $(wildcard Test/include/*.h) $(wildcard Test/src/*.c) -lgraph
