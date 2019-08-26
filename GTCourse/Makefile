INC := -IGraphAPI/include/

%.o: $(wildcard GraphAPI/src/*.c)
	gcc -c $^ -o $@

api: $(wildcard *.o)
	ar rsv $^ -o bin/libgraph.a && rm *.o
