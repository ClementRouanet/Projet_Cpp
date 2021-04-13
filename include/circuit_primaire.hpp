#ifndef CUIRCUIT_PRIMAIRE_HPP_
#define CUIRCUIT_PRIMAIRE_HPP_

#include "circuit.hpp"
#include "pressuriseur.hpp"


class CircuitPrim: public Circuit
{
public:
  CircuitPrim();  // Constructeur

  double etatPressuriseur() const;  // Renvoie l'état du pressuriseur
  double etatResistancePressuriseur() const;  // Renvoie l'état de la résistance du pressuriseur
  double etatEchangeurChaleur() const;  // Renvoie l'état de l'échangeur de chaleur
  double tempPressuriseurDemande() const; // Renvoie la température du pressuriseur demandée
  double tempPressuriseurActuel() const;  // Renvoie la température du pressuriseur actuel
  double pression() const;  // Renvoie la pression
  double temperatureEau() const;  // renvoie la température de l'eau dans le circuit

  void modifPression(); // Modifie la pression
  void modifDebitEau(); // Modifie le débit de l'eau
  void modifInertietemperature(double Tvap); // Modifie l'inertie température eau circuit
  void modifTemperatureEau(); // Modifie la température de l'eau dans le circuit
  void modifRadioactivite();  // Modifie la radioactivité du circuit

  void securiteCircuitPrim() const;

  ~CircuitPrim(); // Destructeur

private:
  Pressuriseur m_pressuriseur;  //Epress & Eres & Tpress & TPeff
  double m_echangChal;  //Eec
  double m_pression;  //P
  double m_temperatureEau; //T
};

#endif
