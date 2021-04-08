#ifndef _PROJET_CONDENSATEUR_HPP_
#define _PROJET_CONDENSATEUR_HPP_
#include "pompe.hpp"
/**
* @brief      Cette classe décrit le condensateur du circuit secondaire *
*
* Le condensateur est caractérisée par le rendement de la pompe et son état. Le rendement peut être
* limité par l'état du condensateur
*/
class Condensateur
{
public:
  /**
  * @brief      Constructeur par défaut
  *
  * L'état initial du condensateur vaut 1. et son rendement est à zéro.
  */
  Condensateur();

  double Getetat() const;
  double Getdebit() const;
  Pompe Getpompe() const;
  double Getdelta_ES() const;

  ~Condensateur();

protected:
  /* etat du condensateur */
  double etat;
  /* debit au niveau du condensateur */
  double debit;
  /* pompe du condensateur */
  Pompe pompe;
  /* Différence de chaleur entre l’entrée et la sortie du condensateur */
  double delta_ES;
};

#endif
