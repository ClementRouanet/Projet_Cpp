#ifndef CUIRCUIT_PRIMAIRE_HPP_
#define CUIRCUIT_PRIMAIRE_HPP_

#include "circuit.hpp"
#include "pressuriseur.hpp"


class CircuitPrim: public Circuit     // Circuit primaire hérite de circuit
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

  void majEtatPressuriseur(double valeur);  // Modifie l'état du pressuriseur
  void majEtatResistancePressuriseur(double valeur);  // Modifie l'état de la résistance du pressuriseur
  void majEtatEchangeurChaleur(double valeur);  // Modifie l'état de l'échangeur de chaleur
  void majTempPressuriseurDemande(double valeur); // Modifie la température du pressuriseur demandée
  void majTempPressuriseurActuel();  // Modifie la température du pressuriseur actuel
  void majPression(); // Modifie la pression
  void majDebitEau(double Ecuve); // Modifie le débit de l'eau
  void majInertietemperature(double Tvap, double TBeff, double TGreff); // Modifie l'inertie température eau circuit
  void majTemperatureEau(double TBeff, double TGreff); // Modifie la température de l'eau dans le circuit
  void majRadioactivite(double TBeff, double MW);  // Modifie la radioactivité du circuit

  void reparationEtat();  // Réparation de l'état du circuit primaire par les ouvriers
  void reparationPressuriseur();  // Réparation de l'état du pressuriseur par les ouvriers

  ~CircuitPrim(); // Destructeur

private:
  Pressuriseur m_pressuriseur;  //Epress & Eres & Tpress & TPeff
  double m_echangChal;  //Eec
  double m_pression;  //P
  double m_temperatureEau; //T
};

#endif
