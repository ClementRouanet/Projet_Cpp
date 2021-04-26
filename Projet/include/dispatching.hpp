#ifndef DISPATCHING_HPP_
#define DISPATCHING_HPP_

#include "centrale.hpp"
#include "sdl2.hpp"


class Dispatching
{
public:
  Dispatching(); // Constructeur

  int scoreDispatching(); // Renvoie le score du dispatching

  void ordreInitial(sdl2::window& fenetre) const; // Affiche l'ordre initial (divergence)
  void ordre(); // Simule les ordres qui arrivent après la divergence
  void affichageDispatching(sdl2::window& fenetre, Centrale& centrale) const;  // Affiche les ordres provenant du dispatching national

  void majdispatching(sdl2::window& fenetre, Centrale& centrale, int tour); // Met à jour le dispatching

  ~Dispatching(); // Destructeur

private:
  int m_tourDebut;  // Tour du début de l'ordre
  int m_tourActuel; // Nombre de tours depuis le début de l'ordre
  int m_score;  // Score du joueur
  int m_nbOrdre;  // Nombre d'ordre reçu depuis le début de la partie
  int m_produire; // Nombre de MW à produire lors d'un ordre
  bool m_ordre; // true = on a un ordre, false = pas d'ordre en cours
  bool m_contreOrdre;  // true = on a un contre-ordre, false = sinon
  bool m_objectif;  // true = on est dans la fourchette demandée à 10MW près
  int m_tourObjectif; // Nombre de tour consécutif après première fois dans la fourchette
};

#endif
