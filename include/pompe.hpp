#ifndef POMPE_HPP_
#define POMPE_HPP_


class Pompe
{
public:
  Pompe();  // Constructeur

  double rendement() const; // Renvoie le rendement de la pompe
  double etat() const;  // Renvoie l'état de la pompe

  void majRendement(double valeur, double etat); // Modifie le rendement de la pompe
  void majEtat(double valeur);  // Modifie l'état de la pompe

  void reparation();  // Réparation de l'état de la pompe par les ouvriers

  ~Pompe(); // Destructeur

private:
  double m_etat;  //Ep
  double m_rendement; //Fp
};

#endif
