CC=clang++
LDLIBS=-lsfml-graphics -lsfml-window -lsfml-system

all: bin/pong

bin/pong: main.o classes.o
	$(CC) $(LDLIBS) main.o classes.o -o bin/pong

main.o: main.cpp classes.hpp
	$(CC) -c main.cpp

classes.o: classes.cpp classes.hpp
	$(CC) -c classes.cpp

clean:
	rm -f *.o
