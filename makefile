
all: proj3.x

proj3.x: in2post.o
	g++ -o proj3.x in2post.o

in2post.o: in2post.cpp stack.h stack.hpp
	g++ -c in2post.cpp -std=c++11

clean:
	rm -f *.o proj3.x
