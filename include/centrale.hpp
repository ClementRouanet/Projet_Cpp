#ifndef CENTRALE_HPP_
#define CENTRALE_HPP_

#include "enceinte.hpp"
#include "circuit_primaire.hpp"
#include "circuit_secondaire.hpp"
//#include "reacteur.hpp"


class Centrale
{
public:
  Centrale(); //Constrcteur


  //FONCTIONS DE L'ENCEINTE
  double etatEnceinte() const;
  double pressionEnceinte() const;
  double radioactiviteEnceinte() const;

  //void majPressionEnceinte(); // met à jour la Pression subit par l'enceinte de Confinement
  //void majRadioactiviteEnceinte(); // met à jour la radioactivité de l'enceinte de confinement

  //FONCTION DE LA CENTRALE
  double etatCentrale() const;
  double productionCentrale() const;

  //void majEtatCentrale(); // met à jour l'état général de la centrale
  //void majProductionCentrale(); // met à jour la production générale de la centrale


  //FONCTION DU CIRCUIT PRIMAIRE
  double etatCircuitPrim() const; // Renvoie l'état du circuit
  double etatPompePrim() const; // Renvoie l'état de la pompe
  double rendementPompePrim() const; // Renvoie le rendement de la pompe
  double debitEauPrim() const;  // Renvoie le débit de l'eau
  double inertieTemperaturePrim() const;  // Renvoie l'inertie température eau circuit
  double radioactivitePrim() const; // Renvoie la radioactivité du circuit
  double etatPressuriseur() const;  // Renvoie l'état du pressuriseur
  double etatResistancePressuriseur() const;  // Renvoie l'état de la résistance du pressuriseur
  double etatEchangeurChaleur() const;  // Renvoie l'état de l'échangeur de chaleur
  double tempPressuriseurDemande() const; // Renvoie la température du pressuriseur demandée
  double tempPressuriseurActuel() const;  // Renvoie la température du pressuriseur actuel
  double pressionPrim() const;  // Renvoie la pression
  double temperatureEau() const;  // renvoie la température de l'eau dans le circuit

  void majEtatCircuitPrim(double valeur); // Modifie l'état du circuit
  void majEtatPompePrim(double valeur); // Modifie l'état de la pompe
  void majRendementPompePrim(double valeur); // Modifie le rendement de la pompe
  void majEtatPressuriseur(double valeur);  // Modifie l'état du pressuriseur
  void majEtatResistancePressuriseur(double valeur);  // Modifie l'état de la résistance du pressuriseur
  void majEtatEchangeurChaleur(double valeur);  // Modifie l'état de l'échangeur de chaleur
  void majTempPressuriseurDemande(double valeur); // Modifie la température du pressuriseur demandée
  void majTempPressuriseurActuel();  // Modifie la température du pressuriseur actuel
  void majPressionEau(); // Modifie la pression de l'eau
  void majDebitEauPrim(double Ecuve); // Modifie le débit de l'eau
  void majInertietemperaturePrim(double Tvap, double TBeff, double TGreff); // Modifie l'inertie température eau circuit
  void majTemperatureEau(double TBeff, double TGreff); // Modifie la température de l'eau dans le circuit
  void majRadioactivitePrim(double TBeff, double MW);  // Modifie la radioactivité du circuit


  //FONCTION DU CIRCUIT SECONDAIRE
  double etatCircuitSec() const; // Renvoie l'état du circuit
  double etatPompeSec() const; // Renvoie l'état de la pompe
  double rendementPompeSec() const; // Renvoie le rendement de la pompe
  double debitEauSec() const;  // Renvoie le débit de l'eau
  double inertieTemperatureSec() const;  // Renvoie l'inertie température eau circuit
  double radioactiviteSec() const; // Renvoie la radioactivité du circuit
  double etatGenerateurVapeur() const;  // Renvoie l'état du générateur de vapeur
  double etatCondenseur() const;  // Renvoie l'état du condenseur
  double rendementPompeCondenseur() const; // Renvoie le rendement de la pompe du condenseur
  double temperatureVapeur() const; // Renvoie la température de la vapeur
  double pressionVapeur() const;  // Renvoie la pression exercée par la vapeur
  double debitCondenseur() const; // Renvoie le débit au niveau du condenseur
  double diffChaleurCondenseur() const; // Renvoie la différence de chaleur entre l'entrée et la sortie du condenseur

  void majEtatCircuitSec(double valeur); // Modifie l'état du circuit
  void majEtatPompeSec(double valeur); // Modifie l'état de la pompe
  void majRendementPompeSec(double valeur); // Modifie le rendement de la pompe
  void majEtatGenerateurVapeur(double valeur);  // Modifie l'état du générateur de vapeur
  void majEtatCondenseur(double valeur);  // Modifie l'état du condenseur
  void majRendementPompeCondenseur(double valeur);  // Modifie le rendement de la pompe du condenseur
  void majTemperatureVapeur();  // Modifie la température de la vapeur
  void majPressionVapeur(); // Modifie la pression exercée par la vapeur
  void majDebitEauSec(); // Modifie le débit de l'eau
  void majDebitCondenseur();  // Modifie le débit au niveau du condenseur
  void majDiffChaleurCondenseur();  // modifie la différence de chaleur entre l'entrée et la sortie du condenseur
  void majInertieTemperatureSec(); // Modifie l'inertie température eau circuit
  void majRadioactivite();  // Modifie la radioactivité du circuit


  //FONCTION DU REACTEUR



  //fini
  ~Centrale(); //Destructeur

private:
  CircuitPrim primaire;
  CircuitSec secondaire;
  //Reacteur reacteur;
  Enceinte enceinte;
  double m_etat;
  double m_production;
};

#endif
