#ifndef _NUCLEARALERTE_CIRCUIT_SECONDAIRE_HPP_
#define _NUCLEARALERTE_CIRCUIT_SECONDAIRE_HPP_
#include "condensateur.hpp"
#include "centrale_base.hpp"

class Circuit_secondaire: public Circuit
{
public:
  Circuit_secondaire();

  virtual double radioactivité( const centrale_base& c ) const = 0;
  Condensateur Getcondensateur() const;
  double GetEvap() const;
  double GetTvap() const;
  double GetPvap() const;
  double GetI_T2() const;

  ~Circuit_secondaire();
private:
  /* condensateur inclus dans le circuit secondaire */
  Condensateur condensateur;
  /* État du générateur de vapeur */
  double Evap;
  /* Température vapeur */
  double Tvap;
  /* Pression exercée par la vapeur */
  double Pvap;
  /* Inertie chaleur de l’eau du circuit */
  double I_T2;
};

#endif
