#ifndef CENTRALE_HPP_
#define CENTRALE_HPP_

#include "enceinte.hpp"
#include "circuit_primaire.hpp"
#include "circuit_secondaire.hpp"


class Centrale
{
public:
  Centrale(); //Constructeur
  double etatEnceinte() const;
  double pressionEnceinte() const;
  double radioactiviteEnceinte() const;
  double etatCentrale() const;
  double productionCentrale() const;

  void majPressionEnceinte(CircuitPrim& primaire,CircuitSec& secondaire); // met à jour la Pression subit par l'enceinte de Confinement
  void majRadioactiviteEnceinte(CircuitPrim& primaire,CircuitSec& secondaire); // met à jour la radioactivité de l'enceinte de confinement
  void majEtatCentrale(CircuitPrim& primaire,CircuitSec& secondaire); // met à jour l'état général de la centrale
  void majProductionCentrale(CircuitPrim& primaire,CircuitSec& secondaire); // met à jour la production générale de la centrale

  ~Centrale(); //Destructeur

private:
  Enceinte enceinte;
  double m_etat;
  double m_production;
};

#endif
