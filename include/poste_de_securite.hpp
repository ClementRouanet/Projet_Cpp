#ifndef POSTE_DE_SECURITE_HPP_
#define POSTE_DE_SECURITE_HPP_

#include "sdl2.hpp"
#include "centrale.hpp"
#include "circuit_primaire.hpp"
#include "circuit_secondaire.hpp"
#include "ouvriers.hpp"

class PosteDeSecurite
{
public:
  PosteDeSecurite();  // Constructeur

  // Affichage fenêtre graphique
  void majAffichage(sdl2::window& fenetre, Centrale& centrale,Ouvriers& ouvriers); //met à jour lz fenetre
  void cadre(sdl2::window& fenetre) const; // Affiche un cadre
  void affichageSchemaCentrale(sdl2::window& fenetre, Centrale& centrale); //Affichage du schéma de la centrale
  void affichageReacteur(sdl2::window& fenetre,Centrale& centrale) const; // Affichage du réacteur (état canaux, barres de graphite, piscine et cuve)
  void affichageCircuitPrim(sdl2::window& fenetre,Centrale& centrale) const;  // Affiche le circuit primaire (état, pompe, pressuriseur, résistances électriques et l'injecteur)
  void affichageCircuitSec(sdl2::window& fenetre,Centrale& centrale) const; //Affiche le circuit secondaire (état, pompe, générateur de vapeur, échangeur de chaleur)
  void affichageEnceinteConfinement(sdl2::window& fenetre,Centrale& centrale) const;  // Affiche l'état de l'enceinte de confinement
  void affichageCondenseur(sdl2::window& fenetre,Centrale& centrale) const; // Affiche l'état du condenseur
  void affichageOuvriers(sdl2::window& fenetre,Ouvriers& ouvriers) const; // Affiche les effectifs humains à notre disposition
  void affichageActivite(sdl2::window& fenetre,Centrale& centrale) const; // Affiche le signalement de divers niveaux de contaminations
  void affichageOrdinateur(sdl2::window& fenetre,Centrale& centrale) const; // Affiche l'état courant de la centrale et des alentours
  void affichageCommandes(sdl2::window& fenetre,Centrale& centrale) const;  // Affiche les commandes disponibles pour effectuer des actions
  bool majCommandes(sdl2::window& fenetre, int touche, Centrale& centrale,Ouvriers& ouvriers);
  void evacuationPopulation(sdl2::window& fenetre, Centrale& centrale,Ouvriers& ouvriers);
  void bilanOuvriers(sdl2::window& fenetre, Centrale& centrale,Ouvriers& ouvriers);
  void interventionOuvriers(sdl2::window& fenetre, Centrale& centrale,Ouvriers& ouvriers);






  ~PosteDeSecurite(); // Destructeur

private:
 bool m_schemaCentrale;
};

#endif
