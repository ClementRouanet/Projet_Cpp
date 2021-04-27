#ifndef POPULATION_HPP_
#define POPULATION_HPP_


class Population
{
  public :
  Population(); //constructeur

  double evacuation() const;
  double radioactiviteEau() const;
  int contamination() const;
  double radioactiviteAir() const;
  void majEvacuation(double valeur);
  void majRadioactiviteEau(double valeur);
  void majRadioactiviteAir(double valeur);
  void majContamination(int valeur);

  ~Population(); //destructeur

  private:
  double m_evacuation;
  double m_radioactiviteEau;
  double m_radioactiviteAir;
  int m_contamination;
};

#endif
