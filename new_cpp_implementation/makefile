# world.o:	world.cpp
	# g++ world.cpp -c -o world.o

scanner.out: scanner.cpp world.cpp
	g++ scanner.cpp world.cpp ../cubiomes/libcubiomes.a -lpthread -o scanner.out

# all: world.o scanner.out