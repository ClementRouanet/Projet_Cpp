#ifndef CUIRCUIT_PRIMAIRE_HPP_
#define CUIRCUIT_PRIMAIRE_HPP_

#include "circuit.hpp"
#include "pressuriseur.hpp"


class CircuitPrim: public Circuit
{
public:
  CircuitPrim();  // onstructeur

  double etatPressuriseur() const;  // Renvoie l'état du pressuriseur
  double etatResistancePressuriseur() const;  // Renvoie l'état de la résistance du pressuriseur
  double etatEchangeurChaleur() const;  // Renvoie l'état de l'échangeur de chaleur
  int tempPressuriseurDemande() const; // Renvoie la température du pressuriseur demandée
  int tempPressuriseurActuel() const;  // Renvoie la température du pressuriseur actuel
  double pression() const;  // Renvoie la pression
  double temperatureEau() const;  // renvoie la température de l'eau dans le circuit

  void majEtatPressuriseur(double valeur);  // Modifie l'état du pressuriseur
  void majEtatResistancePressuriseur(double valeur);  // Modifie l'état de la résistance du pressuriseur
  void majEtatEchangeurChaleur(double valeur);  // Modifie l'état de l'échangeur de chaleur
  void majTempPressuriseurDemande(double valeur); // Modifie la température du pressuriseur demandée
  void majTempPressuriseurActuel();  // Modifie la température du pressuriseur actuel
  void majPression(); // Modifie la pression
  void majDebitEau(); // Modifie le débit de l'eau
  void majInertietemperature(double Tvap); // Modifie l'inertie température eau circuit
  void majTemperatureEau(); // Modifie la température de l'eau dans le circuit
  void majRadioactivite();  // Modifie la radioactivité du circuit
  
  ~CircuitPrim(); // Destructeur

private:
  Pressuriseur m_pressuriseur;  //Epress & Eres & Tpress & TPeff
  double m_echangChal;  //Eec
  double m_pression;  //P
  int m_temperatureEau; //T
};

#endif
