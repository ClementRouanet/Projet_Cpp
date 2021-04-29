#ifndef REACTEUR_HPP_
#define REACTEUR_HPP_

class Reacteur
{
public:

  Reacteur();
  ~Reacteur();

  double getPropGrAct() const;
  double getPropGrDemandee() const;
  double getTauxBoreDemande() const;
  double getTauxBoreAct() const;
  double getEtatCuve() const;
  double getRadPiscine() const;
  double getEtatPiscine() const;
  double getEtatBarresGr() const;
  double getEtatCanaux() const;
  double getEtatInjBore() const;

  void majPropGrDemandee(double valeur_demandee);
  void majPropGrAct();
  void majTauxBoreDemande(double valeur_demandee);
  void majTauxBoreAct();
  void majEtatCuve(double valeur_demandee);
  void majRadPiscine(double R1);
  void majEtatPiscine(double valeur_demandee);
  void majEtatBarresGr(double valeur_demandee);
  void majEtatCanaux(double valeur_demandee);
  void majEtatInjBore(double valeur_demandee);

  void reparationInjecteurBore();  // Réparation de l'état de l'injecteur de bore par les ouvriers

private:
  double m_propGrAct;
  double m_propGrDemandee;
  double m_tauxBoreDemande;
  double m_tauxBoreAct;
  double m_etatCuve;
  double m_radPiscine;
  double m_etatPiscine;
  double m_etatBarresGr;
  double m_etatCanaux;
  double m_etatInjBore;
};

#endif
