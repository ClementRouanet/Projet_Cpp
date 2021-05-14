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

  std::vector<std::string> messages(Centrale& centrale); // Renvoie le tableau des alertes qui seront affichés
  void affichageSecurite(sdl2::window& fenetre, Centrale& centrale);  // Affiche les alertes sécurité
  void affichagePoints(sdl2::window& fenetre); // Fonction contenue dans affichageSecurite permettant de se repérer dans les fenetres de Sécurité

  /* Les deux fonction suivantes mettent à jour le numéro de la fenêtre sur laquelle nous sommes sur l'écran Sécurité (m_fenetreActuelle) */

  void majSecuriteDroite();
  void majSecuriteGauche();

  ~Securite(); // Destructeur

private:
  int m_nbMessages; // Nombre d'alertes
  int m_fenetreActuelle; // Indice de la fenêtre actuelle
 int m_nbFenetres; // Nombre de fenêtre pour l'écran Sécurité
};

#endif
