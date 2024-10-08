CXX = g++
CXXFLAGS = -O3 -march=native -Wall -O -std=c++17 `sdl2-config --cflags`
EXEC = nuclearalert  # Suppression de l'extension .exe

LIBSSDL2 = `sdl2-config --cflags` -lSDL2_ttf -lSDL2_image `sdl2-config --libs` -I SDL2
LIBS = $(LIBSSDL2) -I include

all : $(EXEC)

OBJS = obj/niveaux.o obj/centrale.o obj/reacteur.o obj/circuit.o obj/circuit_primaire.o obj/circuit_secondaire.o obj/pompe.o obj/pressuriseur.o obj/condenseur.o obj/enceinte.o obj/dispatching.o obj/securite.o obj/population.o obj/catastrophe.o obj/ouvriers.o obj/poste_de_securite.o obj/salle_de_controle.o
SDL2 = SDL2/sdl2.o SDL2/geometry.o SDL2/window.o SDL2/font.o SDL2/event.o SDL2/texte.o SDL2/image.o SDL2/formated_text.o

SDL2/sdl2.o:	SDL2/sdl2.hpp SDL2/sdl2.cpp
	$(CXX) $(CXXFLAGS) -c SDL2/sdl2.cpp -o SDL2/sdl2.o

SDL2/geometry.o:	SDL2/geometry.hpp SDL2/window.hpp SDL2/geometry.cpp
	$(CXX) $(CXXFLAGS) -c SDL2/geometry.cpp -o SDL2/geometry.o

SDL2/window.o:	SDL2/window.hpp SDL2/window.cpp
	$(CXX) $(CXXFLAGS) -c SDL2/window.cpp -o SDL2/window.o

SDL2/font.o:	SDL2/window.hpp SDL2/font.hpp SDL2/font.cpp
	$(CXX) $(CXXFLAGS) -c SDL2/font.cpp -o SDL2/font.o

SDL2/event.o : SDL2/window.hpp SDL2/event.hpp SDL2/event.cpp
	$(CXX) $(CXXFLAGS) -c SDL2/event.cpp -o SDL2/event.o

SDL2/texte.o : SDL2/window.hpp SDL2/font.hpp SDL2/texte.hpp SDL2/texte.cpp
	$(CXX) $(CXXFLAGS) -c SDL2/texte.cpp -o SDL2/texte.o

SDL2/formated_texte.o : SDL2/window.hpp SDL2/font.hpp SDL2/formated_text.hpp SDL2/formated_text.cpp
	$(CXX) $(CXXFLAGS) -c SDL2/formated_text.cpp -o SDL2/formated_text.o

SDL2/image.o : SDL2/window.hpp SDL2/image.hpp SDL2/image.cpp
	$(CXX) $(CXXFLAGS) -c SDL2/image.cpp -o SDL2/image.o


obj/pompe.o : include/pompe.hpp src/pompe.cpp
	$(CXX) $(CXXFLAGS) -c src/pompe.cpp -o obj/pompe.o $(LIBS)

obj/pressuriseur.o : include/pressuriseur.hpp src/pressuriseur.cpp
	$(CXX) $(CXXFLAGS) -c src/pressuriseur.cpp -o obj/pressuriseur.o $(LIBS)

obj/condenseur.o : include/condenseur.hpp src/condenseur.cpp
	$(CXX) $(CXXFLAGS) -c src/condenseur.cpp -o obj/condenseur.o $(LIBS)

obj/enceinte.o : include/enceinte.hpp src/enceinte.cpp
	$(CXX) $(CXXFLAGS) -c src/enceinte.cpp -o obj/enceinte.o $(LIBS)

obj/circuit.o : include/circuit.hpp include/pompe.hpp src/circuit.cpp
	$(CXX) $(CXXFLAGS) -c src/circuit.cpp -o obj/circuit.o $(LIBS)

obj/circuit_primaire.o : include/circuit_primaire.hpp include/circuit.hpp include/pressuriseur.hpp src/circuit_primaire.cpp
	$(CXX) $(CXXFLAGS) -c src/circuit_primaire.cpp -o obj/circuit_primaire.o $(LIBS)

obj/circuit_secondaire.o : include/circuit_secondaire.hpp include/circuit.hpp include/condenseur.hpp src/circuit_secondaire.cpp
	$(CXX) $(CXXFLAGS) -c src/circuit_secondaire.cpp -o obj/circuit_secondaire.o $(LIBS)

obj/reacteur.o : include/reacteur.hpp src/reacteur.cpp
	$(CXX) $(CXXFLAGS) -c src/reacteur.cpp -o obj/reacteur.o $(LIBS)

obj/centrale.o : include/centrale.hpp src/centrale.cpp
	$(CXX) $(CXXFLAGS) -c src/centrale.cpp -o obj/centrale.o $(LIBS)

obj/dispatching.o : include/dispatching.hpp src/dispatching.cpp
	$(CXX) $(CXXFLAGS) -c src/dispatching.cpp -o obj/dispatching.o $(LIBS)

obj/securite.o : include/securite.hpp src/securite.cpp
	$(CXX) $(CXXFLAGS) -c src/securite.cpp -o obj/securite.o $(LIBS)

obj/population.o : include/population.hpp src/population.cpp
	$(CXX) $(CXXFLAGS) -c src/population.cpp -o obj/population.o $(LIBS)

obj/catastrophe.o : include/catastrophe.hpp src/catastrophe.cpp
	$(CXX) $(CXXFLAGS) -c src/catastrophe.cpp -o obj/catastrophe.o $(LIBS)

obj/ouvriers.o : include/ouvriers.hpp src/ouvriers.cpp
	$(CXX) $(CXXFLAGS) -c src/ouvriers.cpp -o obj/ouvriers.o $(LIBS)

obj/poste_de_securite.o : include/poste_de_securite.hpp src/poste_de_securite.cpp
	$(CXX) $(CXXFLAGS) -c src/poste_de_securite.cpp -o obj/poste_de_securite.o $(LIBS)

obj/salle_de_controle.o : include/salle_de_controle.hpp src/salle_de_controle.cpp
	$(CXX) $(CXXFLAGS) -c src/salle_de_controle.cpp -o obj/salle_de_controle.o $(LIBS)

obj/niveaux.o : include/niveaux.hpp src/niveaux.cpp
	$(CXX) $(CXXFLAGS) -c src/niveaux.cpp -o obj/niveaux.o $(LIBS)

nuclearalert : $(OBJS) $(SDL2) src/main.cpp
	$(CXX) $(CXXFLAGS) $(OBJS) $(SDL2) src/main.cpp -o nuclearalert $(LIBS)

clean :
	@rm -f obj/*.o SDL2/*.o nuclearalert src/*~ SDL2/*~
