all: a.out clean

a.out: main.o ENN.o TSP.o
	g++ main.o ENN.o TSP.o

main.o: ENN.h TSP.h points.h
	g++ -c main.cpp

ENN.o: ENN.h
	g++ -c ENN.cpp

TSP.o: TSP.h
	g++ -c TSP.cpp

.PHONY : clean
clean:
	rm *.o
