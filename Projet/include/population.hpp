#ifndef POPULATION_HPP_
#define POPULATION_HPP_


class Population
{
  public :
  Population(); //constructeur

  double evacuation() const; // Renvoie le nombre d'habitant évacués
  double radioactiviteEau() const; // Renvoie la radioactivité de l'eau avoisinant la centrale
  double radioactiviteAir() const; // Renvoie la radioactivité de l'air avoisinant la centrale
  int contamination() const; // Renvoie le nombre de personnes contaminées

  void majEvacuation(double valeur); // Modifie le nombre d'habitant évacués
  void majRadioactiviteEau(double valeur); // Modifie la radioactivité de l'eau avoisinant la centrale
  void majRadioactiviteAir(double valeur); // Modifie la radioactivité de l'air avoisinant la centrale
  void majContamination(int valeur); // Modifie le nombre de personnes contaminées

  ~Population(); //destructeur

  private:
  double m_evacuation; // Nombre d'habitant évacués
  double m_radioactiviteEau; // Radioactivité de l'eau avoisinant la centrale
  double m_radioactiviteAir; // Radioactivité de l'air avoisinant la centrale
  int m_contamination; // Nombre de personnes contaminées
};

#endif
