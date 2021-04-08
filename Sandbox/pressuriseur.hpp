#ifndef _PROJET_PRESSURISUER_HPP_
#define _PROJET_PRESSURISUER_HPP_
/**
* @brief      Cette classe décrit le pressurisuer du circuit primaire *
*
*/
class Pressuriseur
{
public:
  /**
  * @brief      Constructeur par défaut
  *
  * L'état initial du pressurisuer et de la résistance du pressuriseur valent 1.
  */
  Pressuriseur();

  double GetEpress() const;
  double GetEres() const;
  double GetTpress() const;
  double GetTPeff() const;
  
  ~Pressuriseur();

protected:
  /* etat du pressuriseur */
  double Epress;
  /* État de la résistance du pressuriseur */
  double Eres;
  /* Température du pressuriseur demandé */
  double Tpress;
  /* Température du pressuriseur actuel */
  double TPeff;
};

#endif
