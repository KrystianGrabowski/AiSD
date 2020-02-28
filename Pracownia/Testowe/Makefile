CPPFLAGS=-std=gnu++17 -Wall -Wextra -Wshadow -O2 -static -DSPRAWDZACZKA

default: program

program.o: program.cpp
	g++ $(CPPFLAGS) -c program.cpp

program: program.o
	g++ $(CPPFLAGS) program.o -o program

run: program
	./program

clean:
	-rm -f program.o
	-rm -f program