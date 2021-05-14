#ifndef CENTRALE_HPP_
#define CENTRALE_HPP_

#include "enceinte.hpp"
#include "circuit_primaire.hpp"
#include "circuit_secondaire.hpp"
#include "reacteur.hpp"
#include "population.hpp"
#include "sdl2.hpp"


class Centrale
{
public:
  Centrale(); //Constructeur


  // FONCTIONS DE L'ENCEINTE
  double etatEnceinte() const; // Renvoie l'etat de l'enceinte de confinement
  double pressionEnceinte() const; // Renvoie la Pression subit par l'enceinte de confinement
  double radioactiviteEnceinte() const; // Renvoie la radioactivité de l'enceinte de confinement

  void majEtatEnceinte(double valeur); // Modifie l'etat de l'enceinte de confinement
  void majPressionEnceinte(); // Modifie la Pression subit par l'enceinte de confinement
  void majRadioactiviteEnceinte(); // Modifie la radioactivité de l'enceinte de confinement


  // FONCTION DE LA CENTRALE
  double etatCentrale() const; // Renvoie l'état général de la centrale
  double productionCentrale() const; // Renvoie la production générale de la centrale
  double productionTotale() const; // Renvoie la production totale de la centrale

  void majEtatCentrale(); // Modifie l'état général de la centrale
  void majProductionCentrale(); // Modifie la production générale de la centrale
  void madProductionTotale(); // Modifie la production totale de la centrale

  // FONCTION DU CIRCUIT PRIMAIRE
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
  void majDebitEauPrim(); // Modifie le débit de l'eau
  void majInertietemperaturePrim(); // Modifie l'inertie température eau circuit
  void majTemperatureEau(); // Modifie la température de l'eau dans le circuit
  void majRadioactivitePrim();  // Modifie la radioactivité du circuit


  // FONCTION DU CIRCUIT SECONDAIRE
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


  // FONCTIONS DU REACTEUR
  double propGrActuel() const; // Renvoie la proportion actuelle des barres de graphite hors de l’eau demandé
  double propGrDemande() const; // Renvoie la proportion des barres de graphite hors de l’eau demandé
  double tauxBoreDemande() const; // Renvoie le taux de bore demandé dans l’eau du circuit
  double tauxBoreActuel() const; // Renvoie le taux de bore actuel dans l’eau du circuit
  double etatCuve() const; // Renvoie l'état de la cuve
  double radPiscine() const; // Renvoie la radiation de la piscine en becquerel
  double etatPiscine() const; // Renvoie l'etat de la piscine
  double etatBarresGr() const; // Renvoie létat des barres de graphite
  double etatCanaux() const; // Renvoie l'état des canaux guidant les barres
  double etatInjBore() const; // Renvoie l'état injecteurs d’acide borique


  void majPropGrAct(); // Modifie la proportion actuelle des barres de graphite hors de l’eau demandé
  void majPropGrDemandee(double valeur_demandee); // Modifie la proportion des barres de graphite hors de l’eau demandé
  void majTauxBoreDemande(double valeur_demandee); // Modifie le taux de bore demandé dans l’eau du circuit
  void majTauxBoreAct(); // Modifie le taux de bore actuel dans l’eau du circuit
  void majEtatCuve(double valeur_demandee); // Modifie l'état de la cuve
  void majRadPiscine(); // Modifie la radiation de la piscine en becquerel
  void majEtatPiscine(double valeur_demandee); // Modifie l'etat de la piscine
  void majEtatBarresGr(double valeur_demandee); // Modifie létat des barres de graphite
  void majEtatCanaux(double valeur_demandee); // Modifie l'état des canaux guidant les barres
  void majEtatInjBore(double valeur_demandee); // Modifie l'état injecteurs d’acide borique


  // FONCTIONS DE REPARATION
  void reparationPompePrim(); // Réparation par les ouvriers de la pompe du circuit pimaire
  void reparationPompeSec(); // Réparation par les ouvriers de la pompe du circuit secondaire
  void reparationCondenseur(); // Réparation par les ouvriers du condenseur
  void reparationGenerateurVapeur(); // Réparation par les ouvriers du générateur de vapeur
  void reparationInjecteurBore(); // Réparation par les ouvriers des injecteurs d'acide borique
  void reparationCircuitPrim(); // Réparation par les ouvriers du circuit primaire
  void reparationCircuitSec(); // Réparation par les ouvriers du circuit secondaire
  void reparationPressuriseur(); // Réparation par les ouvriers du pressuriseur


  // FONCTION DE LA POPULATION
    double evacuation() const; // Renvoie le nombre d'habitant évacués
    double radioactiviteEau() const; // Renvoie la radioactivité de l'eau avoisinant la centrale
    double radioactiviteAir() const; // Renvoie la radioactivité de l'air avoisinant la centrale
    int contamination() const; // Renvoie le nombre de personnes contaminées

    void majEvacuation(); // Modifie le nombre d'habitant évacués
    void majRadioactiviteEau(); // Modifie la radioactivité de l'eau avoisinant la centrale
    void majRadioactiviteAir(); // Modifie la radioactivité de l'air avoisinant la centrale
    void majContamination(); // Modifie le nombre de personnes contaminées


  //fini
  ~Centrale(); //Destructeur

private:
  CircuitPrim primaire; // Circuit primaire
  CircuitSec secondaire; // Circuit secondaire
  Reacteur reacteur; // Reacteur
  Enceinte enceinte; // Enceinte
  Population population; // Population
  double m_etat; // Etat de la centrale
  double m_production; // Production électrique
  double m_productionTot; // Production totale de la centrale
};
#endif
