#ifndef SALLE_DE_CONTROLE_HPP_
#define SALLE_DE_CONTROLE_HPP_

#include <iostream>

#include "sdl2.hpp"
#include "centrale.hpp"
#include "securite.hpp"
#include "dispatching.hpp"


class SalleDeControle
{
public:
  SalleDeControle();  // Constructeur

  void niveau(int niveau);  // Permet de connaitre le niveau du jeu pour le dispatching (niveau1 : pas de dispatching)

  // Affichage fenêtre graphique
  void majAffichage(sdl2::window& fenetre, Centrale& centrale); // Met à jour l'affichage de la fenêtre graphique
  void cadre(sdl2::window& fenetre) const; // Affiche l'image de font
  void affichageProdElec(sdl2::window& fenetre, Centrale& centrale) const; // Affiche la production d'électricité (en MW)
  void afficheTauxBorePiscine(sdl2::window& fenetre, Centrale& centrale) const;  // Affiche le taux de bore dans la piscine
  void afficheCircuitPrim(sdl2::window& fenetre, Centrale& centrale) const;  // Affiche le circuit primaire (rendement, température, débit, pression, radioactivité)
  void afficheCircuitSec(sdl2::window& fenetre, Centrale& centrale) const; // Affiche le circuit secondaire (rendement, température, débit, pression, radioactivité)
  void affichePressionEnceinte(sdl2::window& fenetre, Centrale& centrale) const; // Affiche la pression subit par l'enceinte de confinement
  void afficheSystRefroidissement(sdl2::window& fenetre, Centrale& centrale) const;  // Affiche la pression subit par l'enceinte de confinement
  void afficheEtatBarreGraphite(sdl2::window& fenetre, Centrale& centrale) const;  // Affiche l'état des barres de graphite (pas d'unité)

  // Modification valeurs avec les commandes
  std::vector<int> majCommandes(sdl2::window& fenetre, int touche, Centrale& centrale); // Appelle les fonction dessous en fonction de la touche associée
  void majRendementPompeCircuitPrim(sdl2::window& fenetre, Centrale& centrale); // Modifie le rendement de la pompe du circuit primaire
  void majRendementPompeCircuitSec(sdl2::window& fenetre, Centrale& centrale);  // Modifie le rendement de la pompe du circuit secondaire
  void majBarreControle(sdl2::window& fenetre, Centrale& centrale); // Modifie l'action sur les barres de contrôle
  void majTauxAcideBorique(sdl2::window& fenetre, Centrale& centrale);  // Modifie le taux d'acide borique
  void majRendementPressuriseur(sdl2::window& fenetre, Centrale& centrale); // Modifie le rendement du pressuriseur
  void majRendementPompeCondenseur(sdl2::window& fenetre, Centrale& centrale);  // Modifie le rendement pompe condenseur
  void arretUrgence(sdl2::window& fenetre, Centrale& centrale); // Simule l'arrêt d'urgence avec l'enfoncement rapide des barres dans le réacteur
  int finSession(); // Arrête la partie en cours
  void affichageSchemaCentrale(sdl2::window& fenetre, Centrale& centrale);  // Affiche le schéma de la centrale
  void schemaCentrale(sdl2::window& fenetre, Centrale& centrale); // Charge le schéma de la centrale et la fait clignoter

  // Met à jour le dspatchinng
  bool majdispatching( Centrale& centrale); // Met à jour le dispatching
  int scoreDispatching(); // Renvoie le score du dispatching

  ~SalleDeControle(); // Destructeur

private:
  bool m_schemaCentrale;  // Vaut true si on a appuyé sur 'Entrée', false sinon
  int m_niveau; // Score du dispatching
  Securite securite;
  Dispatching dispatching;
};

#endif
