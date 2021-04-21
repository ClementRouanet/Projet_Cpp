#ifndef CONDENSEUR_HPP_
#define CONDENSEUR_HPP_

#include "pompe.hpp"


class Condenseur
{
public:
  Condenseur(); // Constructeur

  double etat() const;  // Renvoie l'état du condenseur
  double rendementPompe() const; // Renvoie le rendement de la pompe du condenseur
  double debit() const; // Renvoie le débit au niveau du condenseur
  double differenceChaleur() const; // Renvoie la différence de chaleur entre l'entrée et la sortie du condenseur

  void majRendementPompe(double valeur);  // Modifie le rendement de la pompe du condenseur
  void majDebit(double valeur); // Modifie le débit au niveau du condenseur
  void majDifferenceChaleur(double valeur); // Modifie la différence de chaleur entre l'entrée et la sortie du condenseur

  ~Condenseur();  // Destructeur

private:
  double m_etat;  //Ecd
  Pompe m_pompe;  //Fcd
  double m_debit; //Dcd
  double m_diffChaleur; //delta-ES
};

#endif
