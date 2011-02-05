BigInt.exe: BigInt.o llist.o
	g++ BigInt.o llist.o -o BigInt.exe

BigInt.o: BigInt.cpp llist.h
	g++ -c BigInt.cpp

llist.o: llist.cpp llist.h
	g++ -c llist.cpp
