test:reacteur.o main.cpp
	g++ reacteur.o main.cpp -o test
reacteur.o:reacteur.cpp reacteur.hpp
	g++ -c reacteur.cpp -o reacteur.o
