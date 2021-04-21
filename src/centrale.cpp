#include <algorithm> //min,max
#include <stdlib.h> //rand
#include <iostream>
#include <chrono>
#include <random>
#include <functional>

#include "centrale.hpp"
#include "circuit_primaire.hpp"
#include "circuit_secondaire.hpp"
//#include "reacteur.hpp"

using namespace std;


Centrale::Centrale():m_etat(1.), m_production(0.)
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

//Pression subit par l’enceinte de confinement
/*
void Centrale::majPressionEnceinte()
{
  if (((primaire.pression()>8)&&(Centrale.reacteur.Ecuve<1)&&(Centrale.reacteur.Episc<1))||((Centrale.reacteur.Ecuve<0.3)&&(Centrale.reacteur.Episc<0.4)))
  {
    enceinte.majPression((2.-Centrale.reacteur.Ecuve-Centrale.reacteur.pisc)/23+enceinte.pression());
  }
  if (((primaire.etatCircuit()<0.6)&&(pressionPrim()>12))||(primaire.etatCircuit()<0.2))
  {
    enceinte.majPression((1-primaire.etatCircuit())/30+enceinte.pression());
  }
  if((secondaire.etatGenerateurVapeur()<0.9)&&(secondaire.pressionvapeur()>2))
  {
    enceinte.majPression((1-secondaire.etatGenerateurVapeur())/20+enceinte.pression());
    enceinte.majPression(min(enceinte.pression(),5.));
  }
  if((enceinte.etat() > 0.5) && (enceinte.etat() < 0.6))
  {
    enceinte.majPression((1-enceinte.etat())/2*enceinte.pression()-enceinte.pression());
  }
  random_device hgenerateur;
  default_random_engine generateur(hgenerateur());
   uniform_real_distribution<double> genrand(0,1./55);
   auto rnd = bind(genrand, generateur);
   double RND = rnd();
   //À chaque tour, 30% de chance que  la pression de l'enceinte baisse de 0.13 bar
  if(RND<0.3)
  {
   enceinte.majPression(enceinte.pression()-0.13);
  }
}
//Radioactivité de l’enceinte de confinement à l’intérieur.
void Centrale::majRadioactiviteEnceinte(CircuitPrim& primaire,CircuitSec& secondaire)
{
  random_device hgenerateur;
  default_random_engine generateur(hgenerateur());
   uniform_real_distribution<double> genrand(0,1./55);
   auto rnd = bind(genrand, generateur);
   double RND = rnd();
  enceinte.majRadioactivite(RND+0.00002+(1-primaire.etatCircuit())*primaire.radioactivite()/98.98+(1-primaire.etatPressuriseur())*10);
if((reacteur.Episc < 0.55) && (reacteur.Rpisc > 3000))
{
  enceinte.majRadioactivite(enceinte.radioactivite()*1.25);
}
if (enceinte.etat() < 0.9)
{
 enceinte.majRadioactivite(enceinte.radioactivite()/1.3);
}
if (enceinte.etat() < 0.1)
{
   enceinte.majRadioactivite(enceinte.radioactivite()/1.5);
}
}
*/


//-------------------------------CENTRALE------------------------------------//
double Centrale::etatCentrale() const
{
  return m_etat;
}

double Centrale::productionCentrale() const
{
  return m_production;
}







/*
void Centrale::majEtatCentrale(CircuitPrim& primaire,CircuitSec& secondaire)
{
  m_etat = (reacteur.Ecanaux+2*reacteur.Ebarre+8*reacteur.Ecuve+3*reacteur.Episc+primaire.etatPompe()+secondaire.etatPompe()+5*primaire.etatEchangeurChaleur()+4*secondaire.etatGenerateurVapeur()+primaire.etatPressuriseur()+primaire.etatResistancePressuriseur()+4*m_etat+8*primaire.etatCircuit()+3*secondaire.etatCircuit()+reacteur.Ebore+reacteur.Ecd)/44;
}
void Centrale::majProductionCentrale(CircuitPrim& primaire,CircuitSec& secondaire)
{
  if((secondaire.temperatureVapeur()<120)||(secondaire.etatCircuit()<0.22))
  {
    m_production = 0;
  }
  if(secondaire.temperatureVapeur() < 3000)
  {
   m_production = max(5.787*(secondaire.temperatureVapeur()-120)+28.118*(secondaire.pressionvapeur()-1)+primaire.pression(),0.);
  }
  else
  {
    m_production = 30000;
  }
  if (secondaire.etatCircuit() < 0.6)
  {
  m_production  *= secondaire.etatCircuit();
}
  if ((m_production > 1400) && (m_production < 1412))
  {
   m_production = 1400;
  }
}
*/



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

void Centrale::majDebitEauPrim(double Ecuve)
{
  primaire.majDebitEau(Ecuve);
}

void Centrale::majInertietemperaturePrim(double Tvap, double TBeff, double TGreff)
{
  primaire.majInertietemperature(Tvap, TBeff, TGreff);
}

void Centrale::majTemperatureEau(double TBeff, double TGreff)
{
  primaire.majTemperatureEau(TBeff, TGreff);
}

void Centrale::majRadioactivitePrim(double TBeff, double MW)
{
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
Centrale::~Centrale()
{
}
