all: a.out clean

a.out: main.o ENN.o TSP.o
	g++ -g main.o ENN.o TSP.o

main.o: ENN.h TSP.h tspvector.h TStopwatch.h
	g++ -g -c main.cpp

ENN.o: ENN.h
	g++ -g -c ENN.cpp

TSP.o: TSP.h
	g++ -g -c TSP.cpp

.PHONY : clean
clean:
	rm *.o
