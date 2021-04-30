#ifndef SECURITE_HPP_
#define SECURITE_HPP_

#include <string>
#include <vector>

#include "centrale.hpp"
#include "sdl2.hpp"


class Securite
{
public:
  Securite(); // Constructeur

  std::vector<std::string> messages(Centrale& centrale); // Renvoie le tableau des messages qui seront affichés
  void affichageSecurite(sdl2::window& fenetre, Centrale& centrale);  // Affiche les alertes sécurité
  void affichagePoints(sdl2::window& fenetre); // Fonction contenue dans affichageSecurite permettant de se repérer dans les fenetres de securite

  void majSecuriteDroite(); // Met à jour l'affichage vers la droite
  void majSecuriteGauche(); // Met à jour l'affichage vers la gauche

  ~Securite(); // Destructeur

private:
  int m_nbMessages;
  int m_fenetreActuelle;
  int m_nbFenetres;
};

#endif
