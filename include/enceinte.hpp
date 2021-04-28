#ifndef ENCEINTE_HPP_
#define ENCEINTE_HPP_


class Enceinte
{
public :
  Enceinte(); //constructeur

  double etat() const;
  double pression() const;
  double radioactivite() const;
  void majEtat(double valeur);
  void majPression(double valeur);
  void majRadioactivite(double valeur);

  ~Enceinte(); //destructeur

private:
  double m_etat;
  double m_pression;
  double m_radioactivite;
};

#endif
