#ifndef CUIRCUIT_SECONDAIRE_HPP_
#define CUIRCUIT_SECONDAIRE_HPP_

#include "circuit.hpp"
#include "condenseur.hpp"


class CircuitSec: public Circuit     // Circuit secondaire hérite de circuit
{
public:
  CircuitSec(); // Constructeur

  double etatGenerateurVapeur() const;  // Renvoie l'état du générateur de vapeur
  double etatCondenseur() const;  // Renvoie l'état du condenseur
  double rendementPompeCondenseur() const; // Renvoie le rendement de la pompe du condenseur
  double temperatureVapeur() const; // Renvoie la température de la vapeur
  double pressionVapeur() const;  // Renvoie la pression exercée par la vapeur
  double debitCondenseur() const; // Renvoie le débit au niveau du condenseur
  double diffChaleurCondenseur() const; // Renvoie la différence de chaleur entre l'entrée et la sortie du condenseur

  void majEtatGenerateurVapeur(double valeur);  // Modifie l'état du générateur de vapeur
  void majEtatCondenseur(double valeur);  // Modifie l'état du condenseur
  void majRendementPompeCondenseur(double valeur);  // Modifie le rendement de la pompe du condenseur
  void majTemperatureVapeur(double etatEchangChaleur, double temperature1);  // Modifie la température de la vapeur
  void majPressionVapeur(); // Modifie la pression exercée par la vapeur
  void majDebitEau(); // Modifie le débit de l'eau
  void majDebitCondenseur();  // Modifie le débit au niveau du condenseur
  void majDiffChaleurCondenseur();  // modifie la différence de chaleur entre l'entrée et la sortie du condenseur
  void majInertieTemperature(double temperatureEau); // Modifie l'inertie température eau circuit
  void majRadioactivite(double etatEchangChaleur, double radioactivite1);  // Modifie la radioactivité du circuit

  void reparationGenerateurVapeur();  // Réparation de l'état du générateur de vapeur par les ouvriers
  void reparationEtat();  // Réparation de l'état du circuit secondaire par les ouvriers
  void reparationCondenseur();  // Réparation de l'état du condenseur par les ouvriers

  ~CircuitSec();  // Destructeur

private:
  double m_etatGenerateurVapeur;  //Evap
  Condenseur m_condenseur;  //Ecd & Fcd & Dcd & delta_ES
  double m_temperatureVapeur;  //Tvap
  double m_pressionVapeur;  //Pvap
};

#endif
