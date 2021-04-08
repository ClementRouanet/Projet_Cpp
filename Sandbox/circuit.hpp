#ifndef _NUCLEARALERTE_CIRCUIT_HPP_
#define _NUCLEARALERTE_CIRCUIT_HPP_
#include "pompe.hpp"
#include "centrale_base.hpp"

class Circuit
{
public:

  virtual double radioactivité( const centrale_base& c ) const = 0;
protected:
  /* etat du circuit */
  double etat;
  /* debit de l'eau */
  double debit;
  // Calcul de l'inertie
  Pompe pompe;
  /* radiocativité du circuit */
  double R;
};

#endif
