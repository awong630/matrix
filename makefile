all: matrix.a

matrix.o: src/matrix.cpp src/matrix.hpp
	g++ -std=c++11 -c src/matrix.cpp -o obj/matrix.o

matrix.a: matrix.o
	ar rcs lib/matrix.a obj/matrix.o

clean:
	clean rm -f obj/*.o lib/*.a
