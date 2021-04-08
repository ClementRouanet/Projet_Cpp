#ifndef _PROJET_POMPE_HPP_
#define _PROJET_POMPE_HPP_
/**
* @brief      Cette classe décrit une pompe du circuit primaire ou secondaire *
*
* La pompe est caractérisée par son rendement et son état. Le rendement peut être
* limité par l'état de la pompe
*/
class Pompe
{
public:
  /**
  * @brief      Constructeur par défaut
  *
  * L'état initial de la pompe vaut 1. et son rendement est à zéro.
  */
  Pompe();

  /**
  * @brief      Permet d'ajuster le rendement de la pompe
  *
  *  Ma formule mathématique : \f$x_{i} = \frac{i+1}{2}\f$
  *
  *  Et voici un lien sur un attribut :
  *
  *  voir #rendement
  *
  * @param[in]  valeur_demandee  La valeur demandée
  *
  * @return     La valeur effective obtenue (qui dépend de l'état de la pompe)
  */
  double ajuster_rendement(double valeur_demandee);
  double Getrendement() const;
  double Getetat() const;

  ~Pompe();

protected:
  /** Rendement de la pompe */
  double rendement;
  /** Etat de la pompe */
  double etat;
};

#endif
