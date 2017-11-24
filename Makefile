all: Team10.o MatLibrary.o assistingfunctions.o linked.o Mystring.o
	g++ Team10.o MatLibrary.o assistingfunctions.o linked.o Mystring.o -o matrix

Team10.o: Team10.cpp
	g++ -c Team10.cpp

MatLibrary.o: MatLibrary.h MatLibrary.cpp
	g++ -c MatLibrary.cpp

assistingfunctions.o: assistingfunctions.h assistingfunctions.cpp
	g++ -c assistingfunctions.cpp

linked.o: linked.h linked.cpp
	g++ -c linked.cpp

Mystring.o: Mystring.h Mystring.cpp
	c++ -c Mystring.cpp

clean:
	rm *.o matrix
