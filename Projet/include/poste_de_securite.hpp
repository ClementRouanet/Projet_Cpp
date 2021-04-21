#ifndef POSTE_DE_SECURITE_HPP_
#define POSTE_DE_SECURITE_HPP_


class PosteDeSecurite
{
public:
  PosteDeSecurite();  // Constructeur

  // Affichage fenêtre graphique
  void cadre(double positionX, double positionY, double tailleX, double tailleY) const; // Affiche un cadre
  void affichageReacteur() const; // Affichage du réacteur (état canaux, barres de graphite, piscine et cuve)
  void affichageCircuitPrim() const;  // Affiche le circuit primaire (état, pompe, pressuriseur, résistances électriques et l'injecteur)
  void affichageCircuitSec() const; //Affiche le circuit secondaire (état, pompe, générateur de vapeur, échangeur de chaleur)
  void affichageEnceinteConfinement() const;  // Affiche l'état de l'enceinte de confinement
  void affichageCondenseur() const; // Affiche l'état du condenseur
  void affichageOuvriers() const; // Affiche les effectifs humains à notre disposition
  void affichageActivite() const; // Affiche le signalement de divers niveaux de contaminations
  void affichageOrdinateur() const; // Affiche l'état courant de la centrale et des alentours
  void affichageCommandes() const;  // Affiche les commandes disponibles pour effectuer des actions

  ~PosteDeSecurite(); // Destructeur

private:

};

#endif
