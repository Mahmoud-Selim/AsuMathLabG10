all: Team10.o MatLibrary.o assistingfunctions.o linked.o Mystring.o AdvMatrices.o AdvNumbers.o
	g++ Team10.o MatLibrary.o assistingfunctions.o linked.o Mystring.o AdvMatrices.o AdvNumbers.o -o matrix

Team10.o: Team10.cpp
	g++ -c Team10.cpp

MatLibrary.o: MatLibrary.h MatLibrary.cpp
	g++ -c MatLibrary.cpp

assistingfunctions.o: assistingfunctions.h assistingfunctions.cpp
	g++ -c assistingfunctions.cpp

linked.o: linked.h linked.cpp
	g++ -c linked.cpp

Mystring.o: Mystring.h Mystring.cpp
	g++ -c Mystring.cpp

AdvMatrices.o: AdvMatrices.h AdvMatrices.cpp
	g++ -c AdvMatrices.cpp

AdvNumbers.o: AdvNumbers.h AdvNumbers.cpp
	g++ -c AdvNumbers.cpp

clean:
	rm *.o matrix
