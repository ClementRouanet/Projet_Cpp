#ifndef PRESSURISUER_HPP_
#define PRESSURISUER_HPP_


class Pressuriseur
{
public:
  Pressuriseur(); // Constructeur

  double etat() const;  // Renvoie l'état du pressuriseur
  double etatResistance() const;  // Renvoie l'état de la résistance du pressuriseur
  void temperatureDemandee(int valeur); // Modifie la température du pressuriseur demandée
  int temperatureActuel() const;  // Renvoie la température du pressuriseur actuel

  ~Pressuriseur();  // Destructeur

private:
  double m_etat;  //Epress
  double m_etatResistance;  //Eres
  int m_tempDemandee; //Tpress
  int m_temp_actuel;  //TPeff
};

#endif
