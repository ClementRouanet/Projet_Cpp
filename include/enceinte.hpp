#ifndef ENCEINTE_HPP_
#define ENCEINTE_HPP_


class Enceinte
{
public :
  Enceinte(); //constructeur

  double etat() const; //retourne l'état de l'enceinte
  double pression() const; //retourne la pression de l'enceinte
  double radioactivite() const; //retourne la radioactivité de l'enceinte
  void majEtat(double valeur); //affecte une nouvelle valeur à l'état de l'enceinte
  void majPression(double valeur); //affecte une nouvelle valeur à la pression
  void majRadioactivite(double valeur); //affecte une nouvelle valeur à la  radioactivité

  ~Enceinte(); //destructeur

private:
  double m_etat; //état de l'enceinte
  double m_pression; //pression subit par l'enceinte
  double m_radioactivite; //radioactivité dans l'enceinte
};

#endif
