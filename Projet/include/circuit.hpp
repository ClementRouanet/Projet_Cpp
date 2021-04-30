#ifndef CUIRCUIT_HPP_
#define CUIRCUIT_HPP_

#include "pompe.hpp"


class Circuit
{
public:
  Circuit();  // Constructeur

  double etatCircuit() const; // Renvoie l'état du circuit
  double etatPompe() const; // Renvoie l'état de la pompe
  double rendementPompe() const; // Renvoie le rendement de la pompe
  double debitEau() const;  // Renvoie le débit de l'eau
  double inertieTemperature() const;  // Renvoie l'inertie température eau circuit
  double radioactivite() const; // Renvoie la radioactivité du circuit

  void majEtatCircuit(double valeur); // Modifie l'état du circuit
  void majEtatPompe(double valeur); // Modifie l'état de la pompe
  void majRendementPompe(double valeur); // Modifie le rendement de la pompe

  void reparationPompe();  // Réparation de l'état de la pompe par les ouvriers

  ~Circuit(); // Destructeur

protected:
  double m_etatCircuit; //Ec
  Pompe m_pompe;  //Ep & Fp
  double m_debit; //D
  double m_inertieTemp; //IT
  double m_radioactivite; //R
};

#endif
