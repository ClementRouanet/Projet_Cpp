CC = g++
CFLAGS = -Wall -O
EXEC = nuclearalert.exe

all : $(EXEC)

nuclearalert.exe : main.o circuit.o circuit_primaire.o circuit_secondaire.o pompe.o pressuriseur.o condenseur.o
	$(CC) -o nuclearalert.exe main.o circuit.o circuit_primaire.o circuit_secondaire.o pompe.o pressuriseur.o condenseur.o

main.o : main.cpp circuit_primaire.hpp circuit_secondaire.hpp
	$(CC) -o main.o -c main.cpp

circuit.o : circuit.cpp circuit.hpp pompe.hpp
	$(CC) -o circuit.o -c circuit.cpp

circuit_primaire.o : circuit_primaire.cpp circuit_primaire.hpp circuit.hpp pressuriseur.hpp
	$(CC) -o circuit_primaire.o -c circuit_primaire.cpp

circuit_secondaire.o : circuit_secondaire.cpp circuit_secondaire.hpp circuit.hpp condenseur.hpp
	$(CC) -o circuit_secondaire.o -c circuit_secondaire.cpp

pompe.o : pompe.cpp pompe.hpp
	$(CC) -o pompe.o -c pompe.cpp

pressuriseur.o : pressuriseur.cpp pressuriseur.hpp
	$(CC) -o pressuriseur.o -c pressuriseur.cpp

condenseur.o : condenseur.cpp condenseur.hpp
	$(CC) -o condenseur.o -c condenseur.cpp

clean :
	rm -f *.o core

mrpropre : clean
	rm -f $(EXEC)
