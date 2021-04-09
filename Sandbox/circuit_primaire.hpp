#ifndef _NUCLEARALERTE_CIRCUIT_PRIMAIRE_HPP_
#define _NUCLEARALERTE_CIRCUIT_PRIMAIRE_HPP_
#include "pressuriseurr.hpp"
#include "centrale_base.hpp"

class Circuit_primaire: public Circuit
{
public:
  Circuit_primaire();

  virtual double radioactivité( const centrale_base& c ) const = 0;
  double GetE_EC() const;
  Pressuriseur Getpressuriseur() const;
  double GetP1() const;
  double GetI_T1() const;
  double GetT1() const;

  ~Circuit_primaire();
private:
  /* État de l’échangeur de chaleur */
  double E_EC;
  /* Pressuriseur du circuit primaire */
  Pressuriseur pressuriseur;
  /* Pression */
  double P1;
  /* Inertie température eau circuit */
  double I_T1;
  /* Température eau dans circuit */
  double T1;
};

#endif
