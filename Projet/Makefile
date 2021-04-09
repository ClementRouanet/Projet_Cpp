CXX = g++
CXXFLAGS = -O3 -march=native -Wall -O
EXEC = bin/main.exe

LIBS = -I include

all : $(EXEC)

OBJS = obj/circuit.o obj/circuit_primaire.o obj/circuit_secondaire.o obj/pompe.o obj/pressuriseur.o obj/condenseur.o

obj/pompe.o : include/pompe.hpp src/pompe.cpp
	$(CXX) $(CXXFLAGS) -c src/pompe.cpp -o obj/pompe.o $(LIBS)

obj/pressuriseur.o : include/pressuriseur.hpp src/pressuriseur.cpp
	$(CXX) $(CXXFLAGS) -c src/pressuriseur.cpp -o obj/pressuriseur.o $(LIBS)

obj/condenseur.o : include/condenseur.hpp src/condenseur.cpp
	$(CXX) $(CXXFLAGS) -c src/condenseur.cpp -o obj/condenseur.o $(LIBS)

obj/circuit.o : include/circuit.hpp include/pompe.hpp src/circuit.cpp
	$(CXX) $(CXXFLAGS) -c src/circuit.cpp -o obj/circuit.o $(LIBS)

obj/circuit_primaire.o : include/circuit_primaire.hpp include/circuit.hpp include/pressuriseur.hpp src/circuit_primaire.cpp
	$(CXX) $(CXXFLAGS) -c src/circuit_primaire.cpp -o obj/circuit_primaire.o $(LIBS)

obj/circuit_secondaire.o : include/circuit_secondaire.hpp include/circuit.hpp include/condenseur.hpp src/circuit_secondaire.cpp
	$(CXX) $(CXXFLAGS) -c src/circuit_secondaire.cpp -o obj/circuit_secondaire.o $(LIBS)

bin/main.exe : $(OBJS) src/main.cpp
	$(CXX) $(CXXFLAGS) $(OBJS) src/main.cpp -o bin/main.exe $(LIBS)

clean :
	@rm -f obj/*.o bin/*.exe src/*~ core
