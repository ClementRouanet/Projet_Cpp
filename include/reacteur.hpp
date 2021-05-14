#ifndef _PROJET_REACTEUR_HPP_
#define _PROJET_REACTEUR_HPP_

class Reacteur
{
public:

  Reacteur();

  double getPropGrAct() const; // Renvoie la proportion actuelle des barres de graphite hors de l’eau demandé
  double getPropGrDemandee() const; // Renvoie la proportion des barres de graphite hors de l’eau demandé
  double getTauxBoreDemande() const; // Renvoie le taux de bore demandé dans l’eau du circuit
  double getTauxBoreAct() const; // Renvoie le taux de bore actuel dans l’eau du circuit
  double getEtatCuve() const; // Renvoie l'état de la cuve
  double getRadPiscine() const; // Renvoie la radiation de la piscine en becquerel
  double getEtatPiscine() const; // Renvoie l'etat de la piscine
  double getEtatBarresGr() const; // Renvoie l'état des barres de graphite
  double getEtatCanaux() const; // Renvoie l'état des canaux guidant les barres
  double getEtatInjBore() const; // Renvoie l'état des injecteurs d’acide borique

  void majPropGrAct(); // Modifie la proportion actuelle des barres de graphite hors de l’eau demandé
  void majPropGrDemandee(double valeur_demandee); // Modifie la proportion des barres de graphite hors de l’eau demandé
  void majTauxBoreDemande(double valeur_demandee); // Modifie le taux de bore demandé dans l’eau du circuit
  void majTauxBoreAct(); // Modifie le taux de bore actuel dans l’eau du circuit
  void majEtatCuve(double valeur_demandee); // Modifie l'état de la cuve
  void majRadPiscine(double R1); // Modifie la radiation de la piscine en becquerel
  void majEtatPiscine(double valeur_demandee); // Modifie l'etat de la piscine
  void majEtatBarresGr(double valeur_demandee); // Modifie l'état des barres de graphite
  void majEtatCanaux(double valeur_demandee); // Modifie l'état des canaux guidant les barres
  void majEtatInjBore(double valeur_demandee); // Modifie l'état des injecteurs d’acide borique

  void reparationInjecteurBore();  // Réparation par les ouvriers des injecteurs d'acide borique

  ~Reacteur();

private:
  double m_propGrAct; // Proportion actuelle des barres de graphite hors de l’eau demandé
  double m_propGrDemandee; // La proportion des barres de graphite hors de l’eau demandé
  double m_tauxBoreDemande; // Taux de bore demandé dans l’eau du circuit
  double m_tauxBoreAct; // Taux de bore actuel dans l’eau du circuit
  double m_etatCuve; // Etat de la cuve
  double m_radPiscine; // La radiation de la piscine en becquerel
  double m_etatPiscine; // Etat de la piscine
  double m_etatBarresGr; // Etat des barres de graphite
  double m_etatCanaux; // Etat des canaux guidant les barres
  double m_etatInjBore; // Etat des injecteurs d’acide borique
};

#endif
