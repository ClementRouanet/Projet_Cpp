#ifndef PRESSURISUER_HPP_
#define PRESSURISUER_HPP_


class Pressuriseur
{
public:
  Pressuriseur(); // Constructeur

  double etat() const;  // Renvoie l'état du pressuriseur
  double etatResistance() const;  // Renvoie l'état de la résistance du pressuriseur
  double temperatureDemandee() const; // Renvoie la température du pressuriseur demandée
  double temperatureActuel() const;  // Renvoie la température du pressuriseur actuel

  ~Pressuriseur();  // Destructeur

private:
  double m_etat;  //Epress
  double m_etatResistance;  //Eres
  double m_tempDemandee; //Tpress
  double m_temp_actuel;  //TPeff
};

#endif
