#ifndef NIVEAUX_HPP_
#define NIVEAUX_HPP_

#include "centrale.hpp"
#include "salle_de_controle.hpp"
#include "poste_de_securite.hpp"
#include "sdl2.hpp"


void miseAJour(Centrale& centrale);

int niveau1(sdl2::window fenetre, Centrale& centrale, SalleDeControle& salleDeControle, PosteDeSecurite& posteDeSecurite);
int niveau2(sdl2::window fenetre, Centrale& centrale, SalleDeControle& salleDeControle, PosteDeSecurite& posteDeSecurite);
int niveau3(sdl2::window fenetre, Centrale& centrale, SalleDeControle& salleDeControle, PosteDeSecurite& posteDeSecurite);

int menu(sdl2::window fenetreMenu);
void bilan(sdl2::window fenetre, Centrale& centrale, SalleDeControle& salleDeControle, int niveau, int nbTour);

void jeu();

#endif
