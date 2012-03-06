main : main.cpp long.o long.h misc.o misc.h
	g++ -g -o main main.cpp long.o misc.o

long.o : long.cpp long.h
	g++ -g -c long.cpp -o long.o

misc.o : misc.cpp misc.h
	g++ -g -c misc.cpp -o misc.o

clean : 
	rm *.o
