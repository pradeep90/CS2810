BigInt.exe: BigInt.o llist.o
	g++ -g BigInt.o llist.o -o BigInt.exe

BigInt.o: BigInt.cpp llist.h
	g++ -c BigInt.cpp

llist.o: llist.cpp llist.h
	g++ -c llist.cpp

doubly-linked-list.exe:
	g++ llist.o -o doubly-linked-list.exe

debug-BigInt.exe: BigInt.cpp llist.cpp llist.h
	g++ -g BigInt.cpp llist.cpp -o debug-BigInt.exe

clean:
	rm llist.o
