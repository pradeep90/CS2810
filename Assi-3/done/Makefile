BigInt.exe: BigInt.o llist.o
	g++ BigInt.o llist.o -o BigInt.exe

BigInt.o: BigInt.cpp llist.h
	g++ -c BigInt.cpp

llist.o: llist.cpp llist.h
	g++ -c llist.cpp

Points-Complex.exe: Points-Complex.cpp
	g++ Points-Complex.cpp -o Points-Complex.exe

calendar1.exe: calendar1.cpp
	g++ calendar1.cpp -o calendar.exe

roman-arithmetic.exe: roman-arithmetic.cpp
	g++ roman-arithmetic.cpp -o roman-arithmetic.exe

# doubly-linked-list.exe:
# 	g++ llist.o -o doubly-linked-list.exe

# debug-BigInt.exe: BigInt.cpp llist.cpp llist.h
# 	g++ -g BigInt.cpp llist.cpp -o debug-BigInt.exe
