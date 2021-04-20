#include <iostream>
#include <algorithm>
#include <chrono>
#include <random>
#include <functional>

#include "centrale.hpp"
#include "circuit_primaire.hpp"
#include "circuit_secondaire.hpp"

using namespace std;


Centrale::Centrale(): m_etat(1.), m_production(0.)
{
}


double Centrale::EtatEnceinte() const
{
  return enceinte.etat();
}

double Centrale::PressionEnceinte() const
{
  return enceinte.pression();
}

double Centrale::RadioactiviteEnceinte() const
{
  return enceinte.radioactivite();
}


double Centrale::EtatCentrale() const
{
  return m_etat;
}


double Centrale::ProductionCentrale() const
{
  return m_production;
}

/*
//Pression subit par l’enceinte de confinement

void Centrale::majPressionEnceinte(CircuitPrim& primaire,CircuitSec& secondaire)
{
  if (((primaire.pression()>8)&&(Centrale.reacteur.Ecuve<1)&&(Centrale.reacteur.Episc<1))||((Centrale.reacteur.Ecuve<0.3)&&(Centrale.reacteur.Episc<0.4)))
  {
    enceinte.majPression((2.-Centrale.reacteur.Ecuve-Centrale.reacteur.pisc)/23+enceinte.pression());
  }
  if (((primaire.etatCircuit()<0.6)&&(primaire.pression()>12))||(primaire.etatCircuit()<0.2))
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
   m_production = max(5.787*(secondaire.temperatureVapeur()-120)+28.118*(secondaire.pressionVapeur()-1)+primaire.pression(),0.);
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

Centrale::~Centrale()
{
}
