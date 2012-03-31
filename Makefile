main : longint/lib/liblongint.a main.cpp
	g++ main.cpp -I longint/include -Llongint/lib -llongint -o main

longint/lib/liblongint.a :
	cd longint/ ; make

clean :
	rm -f main *~ ; cd longint/ ; make clean

