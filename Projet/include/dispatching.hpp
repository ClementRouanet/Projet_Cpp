#ifndef DISPATCHING_HPP_
#define DISPATCHING_HPP_

#include "centrale.hpp"


class Dispatching
{
public:
  Dispatching(); // Constructeur

  void premierOrdre(sdl2::window& fenetre);
  void ordre(sdl2::window& fenetre, Centrale& centrale);

  // Affichage fenêtre graphique
  void affichageDispatching(sdl2::window& fenetre, Centrale& centrale);

  ~Dispatching(); // Destructeur

private:
  int m_tourDebut;
  int m_tourActuel;
  int m_score;

};

#endif
