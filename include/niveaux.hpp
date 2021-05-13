#ifndef NIVEAUX_HPP_
#define NIVEAUX_HPP_

#include "centrale.hpp"
#include "salle_de_controle.hpp"
#include "poste_de_securite.hpp"
#include "sdl2.hpp"


void miseAJour(Centrale& centrale, PosteDeSecurite& posteDeSecurite); // Met a jour toutes les vriables de la centrale

// Niveaux du jeu
int niveau1(sdl2::window& fenetre, Centrale& centrale, SalleDeControle& salleDeControle, PosteDeSecurite& posteDeSecurite);
int niveau2(sdl2::window& fenetre, Centrale& centrale, SalleDeControle& salleDeControle, PosteDeSecurite& posteDeSecurite);
int niveau3(sdl2::window& fenetre, Centrale& centrale, SalleDeControle& salleDeControle, PosteDeSecurite& posteDeSecurite);

int menu(sdl2::window& fenetreMenu);  // Menu du jeu : choix niveau

// Affichage du bilan du jeu
void affichageEtats(sdl2::window& fenetre, Centrale& centrale);
void affichageProduction(sdl2::window& fenetre, Centrale& centrale, int nbTour);
void affichageRadioactivite(sdl2::window& fenetre, Centrale& centrale);
void affichageScore(sdl2::window& fenetre, SalleDeControle& salleDeControle);
void bilan(sdl2::window& fenetre, Centrale& centrale, SalleDeControle& salleDeControle, int niveau, int nbTour);


void jeu(); // Fonction principale du jeu entier


#endif
