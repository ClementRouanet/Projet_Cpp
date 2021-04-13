#ifndef CUIRCUIT_SECONDAIRE_HPP_
#define CUIRCUIT_SECONDAIRE_HPP_

#include "circuit.hpp"
#include "condenseur.hpp"


class CircuitSec: public Circuit
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

  void modifTemperatureVapeur(double etatEchangChaleur, double temperature1);  // Modifie la température de la vapeur
  void modifPressionVapeur(); // Modifie la pression exercée par la vapeur
  void modifDebitEau(); // Modifie le débit de l'eau
  void modifDebitCondenseur();  // Modifie le débit au niveau du condenseur
  void modifDiffChaleurCondenseur();  // modifie la différence de chaleur entre l'entrée et la sortie du condenseur
  void modifInertieTemperature(double temperatureEau); // Modifie l'inertie température eau circuit
  void modifRadioactivite(double etatEchangChaleur, double radioactivite1);  // Modifie la radioactivité du circuit

  ~CircuitSec();  // Destructeur

private:
  double m_etatGenerateurVapeur;  //Evap
  Condenseur m_condenseur;  //Ecd & Fcd & Dcd & delta_ES
  double m_temperatureVapeur;  //Tvap
  double m_pressionVapeur;  //Pvap
};

#endif
