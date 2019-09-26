CC := gcc
FLAGS := -Wall -Wextra -g
NUMBER := 10

all: src/*.c
	for file in $^ ; do \
		echo $${file} ; \
		$(CC) -o bin/ex$(NUMBER) $${file} $(FLAGS) ; \
		NUMBER := $(NUMBER) + 1 ; \
	done
