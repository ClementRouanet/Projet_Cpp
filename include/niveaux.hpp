#ifndef NIVEAUX_HPP_
#define NIVEAUX_HPP_

#include "centrale.hpp"
#include "salle_de_controle.hpp"
#include "sdl2.hpp"


void miseAJour(Centrale& centrale, SalleDeControle& salleDeControle);

void niveau1(sdl2::window fenetre, Centrale& centrale, SalleDeControle& salleDeControle);
void niveau2(sdl2::window fenetre, Centrale& centrale, SalleDeControle& salleDeControle);
void niveau3(sdl2::window fenetre, Centrale& centrale, SalleDeControle& salleDeControle);

int menu();
void bilan(sdl2::window fenetre, Centrale& centrale, SalleDeControle& salleDeControle);

void jeu();

#endif
