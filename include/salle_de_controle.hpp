#ifndef SALLE_DE_CONTROLE_HPP_
#define SALLE_DE_CONTROLE_HPP_

#include "sdl2.hpp"
#include "centrale.hpp"
#include "circuit_primaire.hpp"
#include "circuit_secondaire.hpp"


class SalleDeControle
{
public:
  SalleDeControle();  // Constructeur

  // Affichage fenêtre graphique
  void cadre(sdl2::window& fenetre) const; // Affiche un cadre
  void affichageDispatching(sdl2::window& fenetre) const;  // Affiche les ordres provenant du dispatching national
  void affichageProdElec(sdl2::window& fenetre, Centrale& centrale) const; // Affiche la production d'électricité (en MW)
  void afficheTauxBorePiscine(sdl2::window& fenetre) const;  // Affiche le taux de bore dans la piscine
  void afficheCircuitPrim(sdl2::window& fenetre, CircuitPrim& circuitPrim) const;  // Affiche le circuit primaire (rendement, température, débit, pression, radioactivité)
  void afficheCircuitSec(sdl2::window& fenetre, CircuitSec& circuitSec) const; // Affiche le circuit secondaire (rendement, température, débit, pression, radioactivité)
  void afficheSystSecurite(sdl2::window& fenetre) const; // Affiche les signalement du système de sécurité
  void affichePressionEnceinte(sdl2::window& fenetre, Centrale& centrale) const; // Affiche la pression subit par l'enceinte de confinement
  void afficheSystRefroidissement(sdl2::window& fenetre, CircuitSec& circuitSec) const;  // Affiche la pression subit par l'enceinte de confinement
  void afficheEtatBarreGraphite(sdl2::window& fenetre) const;  // Affiche l'état des barres de graphite (pas d'unité)
  void afficheCommandes(sdl2::window& fenetre) const;  // Affiche les commandes disponibles pour effectuer des actions

  // Modification valeurs avec les commandes
  void majCommandes(sdl2::window& fenetre, Centrale& centrale, CircuitPrim& circuitPrim, CircuitSec& circuitSec);

  ~SalleDeControle(); // Destructeur

private:

};

#endif
