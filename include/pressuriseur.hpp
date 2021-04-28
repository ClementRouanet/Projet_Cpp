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

  void majEtat(double valeur);  // Modifie l'état du pressuriseur
  void majEtatResistance(double valeur);  // Modifie l'état de la résistance du pressuriseur
  void majTemperatureDemandee(double valeur); // Modifie la température du pressuriseur demandée
  void majTemperatureActuel(); // Modifie la température du pressuriseur actuel

  void reparation();  // Réparation de l'état du pressuriseur par les ouvriers

  ~Pressuriseur();  // Destructeur

private:
  double m_etat;  //Epress
  double m_etatResistance;  //Eres
  double m_tempDemandee; //Tpress
  double m_tempActuel;  //TPeff
};

#endif
