#include <algorithm> //min,max
#include <stdlib.h> //rand
#include <iostream>
#include <chrono>
#include <random>
#include <functional>

#include "centrale.hpp"

using namespace std;


Centrale::Centrale():m_etat(1.), m_production(0.), m_productionTot(0.)
{
}

//------------------------ENCEINTE-----------------------------------//
double Centrale::etatEnceinte() const
{
  return enceinte.etat();
}

double Centrale::pressionEnceinte() const
{
  return enceinte.pression();
}

double Centrale::radioactiviteEnceinte() const
{
  return enceinte.radioactivite();
}

void Centrale::majEtatEnceinte(double valeur)
{
  if (valeur>=0 && valeur<=1)
  m_etat = valeur;
  else if (valeur<0)
  m_etat = 0;
  else
  m_etat = 1;
}

//Pression subit par l’enceinte de confinement

void Centrale::majPressionEnceinte()
{
  if (((pressionPrim()>8)&&(etatCuve()<1)&&(etatPiscine()<1))||((etatCuve()<0.3)&&(etatPiscine()<0.4)))
  {
    enceinte.majPression((2.-etatCuve()-etatPiscine())/23+pressionEnceinte());
  }
  if (((etatCircuitPrim()<0.6)&&(pressionPrim()>12))||(etatCircuitPrim()<0.2))
  {
    enceinte.majPression((1-etatCircuitPrim())/30+pressionEnceinte());
  }
  if((etatGenerateurVapeur()<0.9)&&(pressionVapeur()>2))
  {
    enceinte.majPression((1-etatGenerateurVapeur())/20+pressionEnceinte());
    enceinte.majPression(min(pressionEnceinte(),5.));
  }
  if((etatEnceinte() > 0.5) && (etatEnceinte() < 0.6))
  {
    enceinte.majPression((1-etatEnceinte())/2*pressionEnceinte()-pressionEnceinte());
  }
  random_device hgenerateur;
  default_random_engine generateur(hgenerateur());
  uniform_real_distribution<double> genrand(0,1./55);
  auto rnd = bind(genrand, generateur);
  double RND = rnd();
  //À chaque tour, 30% de chance que  la pression de l'enceinte baisse de 0.13 bar
  if(RND<0.3)
  {
    //enceinte.majPression(pressionEnceinte()-0.13);
  }
}



//Radioactivité de l’enceinte de confinement à l’intérieur.
void Centrale::majRadioactiviteEnceinte()
{
  random_device hgenerateur;
  default_random_engine generateur(hgenerateur());
  uniform_real_distribution<double> genrand(0,1./55);
  auto rnd = bind(genrand, generateur);
  double RND = rnd();
  enceinte.majRadioactivite(RND+0.00002+(1-etatCircuitPrim())*radioactivitePrim()/98.98+(1-etatPressuriseur())*10);
  if((etatPiscine() < 0.55) && (radPiscine() > 3000))
  {
    enceinte.majRadioactivite(radioactiviteEnceinte()*1.25);
  }
  if (etatEnceinte() < 0.9)
  {
    enceinte.majRadioactivite(radioactiviteEnceinte()/1.3);
  }
  if (etatEnceinte() < 0.1)
  {
    enceinte.majRadioactivite(radioactiviteEnceinte()/1.5);
  }
}


//-------------------------------CENTRALE------------------------------------//
double Centrale::etatCentrale() const
{
  return m_etat;
}

double Centrale::productionCentrale() const
{
  return m_production;
}

double Centrale::productionTotale() const
{
  return m_productionTot;
}

void Centrale::majEtatCentrale()
{
  m_etat = (etatCanaux()+2*etatBarresGr()+8*etatCuve()+3*etatPiscine()+etatPompePrim()+etatPompeSec()+5*etatEchangeurChaleur()+4*etatGenerateurVapeur()+etatPressuriseur()+etatResistancePressuriseur()+4*m_etat+8*etatCircuitPrim()+3*etatCircuitSec()+etatInjBore()+etatCondenseur())/44;
}

void Centrale::majProductionCentrale()
{
  if((temperatureVapeur()<120)||(etatCircuitSec()<0.22))
  {
    m_production = 0;
  }
  if(temperatureVapeur() < 3000)
  {
    m_production = max(5.787*(temperatureVapeur()-120)+28.118*(pressionVapeur()-1)+pressionPrim(),0.);
  }
  else
  {
    m_production = 30000;
  }
  if(etatCircuitSec() < 0.6)
  {
    m_production  *= etatCircuitSec();
  }
  if ((m_production > 1400) && (m_production < 1412))
  {
    m_production = 1400;
  }
}

void Centrale::madProductionTotale()
{
  m_productionTot += m_production;
}



//-----------------------------CIRCUIT PRIMAIRE -----------------------/
double Centrale::etatCircuitPrim() const // Renvoie l'état du circuit
{
  return primaire.etatCircuit();
}

double Centrale::etatPompePrim() const
{
  return primaire.etatPompe();
}

double Centrale::rendementPompePrim() const
{
  return primaire.rendementPompe();
}

double Centrale::debitEauPrim() const
{
  return primaire.debitEau();
}

double Centrale::inertieTemperaturePrim() const
{
  return primaire.inertieTemperature();
}

double Centrale::radioactivitePrim() const
{
  return primaire.radioactivite();
}

double Centrale::etatPressuriseur() const
{
  return primaire.etatPressuriseur();
}

double Centrale::etatResistancePressuriseur() const
{
  return primaire.etatResistancePressuriseur();
}

double Centrale::etatEchangeurChaleur() const
{
  return primaire.etatEchangeurChaleur();
}

double Centrale::tempPressuriseurDemande() const
{
  return primaire.tempPressuriseurDemande();
}

double Centrale::tempPressuriseurActuel() const
{
  return primaire.tempPressuriseurActuel();
}

double Centrale::pressionPrim() const
{
  return primaire.pression();
}

double Centrale::temperatureEau() const
{
  return primaire.temperatureEau();
}

void Centrale::majEtatCircuitPrim(double valeur)
{
  primaire.majEtatCircuit(valeur);
}

void Centrale::majEtatPompePrim(double valeur)
{
  primaire.majEtatPompe(valeur);
}

void Centrale::majRendementPompePrim(double valeur)
{
  primaire.majRendementPompe(valeur);
}

void Centrale::majEtatPressuriseur(double valeur)
{
  primaire.majEtatPressuriseur(valeur);
}

void Centrale::majEtatResistancePressuriseur(double valeur)
{
  primaire.majEtatResistancePressuriseur(valeur);
}

void Centrale::majEtatEchangeurChaleur(double valeur)
{
  primaire.majEtatEchangeurChaleur(valeur);
}

void Centrale::majTempPressuriseurDemande(double valeur)
{
  primaire.majTempPressuriseurDemande(valeur);
}

void Centrale::majTempPressuriseurActuel()
{
  primaire.majTempPressuriseurActuel();
}

void Centrale::majPressionEau()
{
  primaire.majPression();
}

void Centrale::majDebitEauPrim()
{
  double Ecuve = etatCuve();
  primaire.majDebitEau(Ecuve);
}

void Centrale::majInertietemperaturePrim()
{
  double Tvap = temperatureVapeur();
  double TBeff = tauxBoreActuel();
  double TGreff = propGrActuel();

  primaire.majInertietemperature(Tvap, TBeff, TGreff);
}

void Centrale::majTemperatureEau()
{
  double TBeff = tauxBoreActuel();
  double TGreff = propGrActuel();

  primaire.majTemperatureEau(TBeff, TGreff);
}

void Centrale::majRadioactivitePrim()
{
  double TBeff = tauxBoreActuel();
  double MW = productionCentrale();

  primaire.majRadioactivite(TBeff, MW);
}



//---------------------------CIRCUIT SECONDAIRE --------------------------------//
double Centrale::etatCircuitSec() const
{
  return secondaire.etatCircuit();
}

double Centrale::etatPompeSec() const
{
  return secondaire.etatPompe();
}

double Centrale::rendementPompeSec() const
{
  return secondaire.rendementPompe();
}

double Centrale::debitEauSec() const
{
  return secondaire.debitEau();
}

double Centrale::inertieTemperatureSec() const
{
  return secondaire.inertieTemperature();
}

double Centrale::radioactiviteSec() const
{
  return secondaire.radioactivite();
}

double Centrale::etatGenerateurVapeur() const
{
  return secondaire.etatGenerateurVapeur();
}

double Centrale::etatCondenseur() const
{
  return secondaire.etatCondenseur();
}

double Centrale::rendementPompeCondenseur() const
{
  return secondaire.rendementPompeCondenseur();
}

double Centrale::temperatureVapeur() const
{
  return secondaire.temperatureVapeur();
}

double Centrale::pressionVapeur() const
{
  return secondaire.pressionVapeur();
}

double Centrale::debitCondenseur() const
{
  return secondaire.debitCondenseur();
}

double Centrale::diffChaleurCondenseur() const
{
  return secondaire.diffChaleurCondenseur();
}

void Centrale::majEtatCircuitSec(double valeur)
{
  secondaire.majEtatCircuit(valeur);
}

void Centrale::majEtatPompeSec(double valeur)
{
  secondaire.majEtatPompe(valeur);
}

void Centrale::majRendementPompeSec(double valeur)
{
  secondaire.majRendementPompe(valeur);
}

void Centrale::majEtatGenerateurVapeur(double valeur)
{
  return secondaire.majEtatGenerateurVapeur(valeur);
}

void Centrale::majEtatCondenseur(double valeur)
{
  secondaire.majEtatCondenseur(valeur);
}

void Centrale::majRendementPompeCondenseur(double valeur)
{
  secondaire.majRendementPompeCondenseur(valeur);
}

void Centrale::majTemperatureVapeur()
{
  double etatEchangChaleur = primaire.etatEchangeurChaleur();
  double temperature1 = primaire.temperatureEau();
  secondaire.majTemperatureVapeur(etatEchangChaleur,temperature1);
}

void Centrale::majPressionVapeur()
{
  secondaire.majPressionVapeur();
}

void Centrale::majDebitEauSec()
{
  secondaire.majDebitEau();
}

void Centrale::majDebitCondenseur()
{
  secondaire.majDebitCondenseur();
}

void Centrale::majDiffChaleurCondenseur()
{
  secondaire.majDiffChaleurCondenseur();
}

void Centrale::majInertieTemperatureSec()
{
  double temperatureEau = primaire.temperatureEau();
  secondaire.majInertieTemperature(temperatureEau);
}

void Centrale::majRadioactivite()
{
  double etatEchangChaleur = primaire.etatEchangeurChaleur();
  double radioactivite1 = primaire.radioactivite();
  secondaire.majRadioactivite(etatEchangChaleur,radioactivite1);
}


//--------------------------------------REACTEUR------------------------------------///

double Centrale::propGrActuel() const
{
  return reacteur.getPropGrAct();
}

double Centrale::propGrDemande() const
{
  return reacteur.getPropGrDemandee();
}

double Centrale::tauxBoreDemande() const
{
  return reacteur.getTauxBoreDemande();
}

double Centrale::tauxBoreActuel() const
{
  return reacteur.getTauxBoreAct();
}

double Centrale::etatCuve() const
{
  return reacteur.getEtatCuve();
}

double Centrale::radPiscine() const
{
  return reacteur.getRadPiscine();
}

double Centrale::etatPiscine() const
{
  return reacteur.getEtatPiscine();
}

double Centrale::etatBarresGr() const
{
  return reacteur.getEtatBarresGr();
}

double Centrale::etatCanaux() const
{
  return reacteur.getEtatCanaux();
}

double Centrale::etatInjBore() const
{
  return reacteur.getEtatInjBore();
}

void Centrale::majPropGrDemandee(double valeur_demandee)
{
  reacteur.majPropGrDemandee(valeur_demandee);
}

void Centrale::majPropGrAct()
{
  reacteur.majPropGrAct();
}

void Centrale::majTauxBoreDemande(double valeur_demandee)
{
  reacteur.majTauxBoreDemande(valeur_demandee);
}

void Centrale::majTauxBoreAct()
{
  reacteur.majTauxBoreAct();
}

void Centrale::majEtatCuve(double valeur_demandee)
{
  reacteur.majEtatCuve(valeur_demandee);
}

void Centrale::majRadPiscine()
{
  double R1 = radioactivitePrim();
  reacteur.majRadPiscine(R1);
}

void Centrale::majEtatPiscine(double valeur_demandee)
{
  reacteur.majEtatPiscine(valeur_demandee);
}

void Centrale::majEtatBarresGr(double valeur_demandee)
{
  reacteur.majEtatBarresGr(valeur_demandee);
}

void Centrale::majEtatCanaux(double valeur_demandee)
{
  reacteur.majEtatCanaux(valeur_demandee);
}

void Centrale::majEtatInjBore(double valeur_demandee)
{
  reacteur.majEtatInjBore(valeur_demandee);
}


//--------------------------------------REPARATION------------------------------------///

void Centrale::reparationPompePrim()
{
  primaire.reparationPompe();
}

void Centrale::reparationPompeSec()
{
  secondaire.reparationPompe();
}

void Centrale::reparationCondenseur()
{
  secondaire.reparationCondenseur();
}

void Centrale::reparationGenerateurVapeur()
{
  secondaire.reparationGenerateurVapeur();
}

void Centrale::reparationInjecteurBore()
{
  reacteur.reparationInjecteurBore();
}

void Centrale::reparationCircuitPrim()
{
  primaire.reparationEtat();
}

void Centrale::reparationCircuitSec()
{
  secondaire.reparationEtat();
}

void Centrale::reparationPressuriseur()
{
  primaire.reparationPressuriseur();
}


//------------------------------------------POPULATION---------------------------------------//
double Centrale::evacuation() const
{
  return population.evacuation();
}

int Centrale::contamination() const
{
 return population.contamination();
}

double Centrale::radioactiviteEau() const
{
 return population.radioactiviteEau();
}

double Centrale::radioactiviteAir() const
{
 return population.radioactiviteAir();
}


void Centrale::majEvacuation()
{
 auto RND = ((float)(rand()))/((float)(RAND_MAX));
 if(RND<0.4 && evacuation() <= 0.9)
 {
 population.majEvacuation(evacuation()+0.1);
 }
}

void Centrale::majContamination()
{
 if(radioactiviteEnceinte()<0.1)
 {
   population.majContamination(contamination()-(5*(radioactiviteAir()>6))-5*(radioactiviteEau()>1)-8*(radioactiviteEau()>12)-10*(radioactiviteAir()>12));
 }
 if(radioactiviteAir()>12)
 {
   auto RND = (rand())/(RAND_MAX)*15;
   population.majContamination(contamination()+4+RND);
 }
 if(radioactiviteEau()>12)
 {
   auto RND = (rand())/(RAND_MAX)*20;
   population.majContamination(contamination()+5+RND);
 }
 if(radioactiviteAir()>20)
 {
   auto RND = (rand())/(RAND_MAX)*20;
   population.majContamination(contamination()+12+RND);
 }
}

void Centrale::majRadioactiviteEau()
{
 if((radioactiviteSec()<2)||(etatCondenseur()>0.9))
 {
   population.majRadioactiviteEau(0.);
 }
 else
 {
   population.majRadioactiviteEau((1-etatCondenseur())*radioactiviteSec()/100);
 }
}

void Centrale::majRadioactiviteAir()
{
 if(etatEnceinte()>0.97)
 {
   population.majRadioactiviteAir(0.);
 }
 else
 {
   population.majRadioactiviteAir((1.-etatEnceinte()*radioactiviteEnceinte()+(1-etatCircuitSec()*10)));
 }
}


Centrale::~Centrale()
{
}
