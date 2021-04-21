#include <iostream>
#include <chrono>
#include <random>
#include <functional>
#include <algorithm>

#include "circuit_primaire.hpp"

using namespace std;


CircuitPrim::CircuitPrim() : Circuit(), m_echangChal(1.), m_pression(1.), m_temperatureEau(25.)
{
}

double CircuitPrim::etatPressuriseur() const
{
  return m_pressuriseur.etat();
}

double CircuitPrim::etatResistancePressuriseur() const
{
  return m_pressuriseur.etatResistance();
}

double CircuitPrim::etatEchangeurChaleur() const
{
  return m_echangChal;
}

double CircuitPrim::tempPressuriseurDemande() const
{
  return m_pressuriseur.temperatureDemandee();
}

double CircuitPrim::tempPressuriseurActuel() const
{
  return m_pressuriseur.temperatureActuel();
}

double CircuitPrim::pression() const
{
  return m_pression;
}

double CircuitPrim::temperatureEau() const
{
  return m_temperatureEau;
}

void CircuitPrim::majEtatPressuriseur(double valeur)
{

}

void CircuitPrim::majEtatResistancePressuriseur(double valeur)
{

}

void CircuitPrim::majEtatEchangeurChaleur(double valeur)
{

}

void CircuitPrim::majTempPressuriseurDemande(double valeur)
{

}

void CircuitPrim::majTempPressuriseurActuel(double valeur)
{

}

void CircuitPrim::majPression()
{
  double tempPressuriseurActuel = m_pressuriseur.temperatureActuel();
  m_pression = max((tempPressuriseurActuel-25)/3.24 + (m_temperatureEau-100)/83.3*(m_etatCircuit+0.1)*(m_echangChal+0.1), 1.);
}
/*
void CircuitPrim::majDebitEau()
{
  double rendementPompe = m_pompe.rendement();
  m_debit = m_etatCircuit*ETATCUVE*rendementPompe*90; //////////////////
}

void CircuitPrim::majInertietemperature(double Tvap)  // Tvap = circuitSec.temperatureVapeur()
{
  random_device hgenerateur;
  default_random_engine generateur1(hgenerateur());
  default_random_engine generateur2(hgenerateur());

  uniform_real_distribution<double> genrand1(0,26);
  uniform_real_distribution<double> genrand2(0,16);

  auto rnd1 = bind(genrand1, generateur1);
  auto rnd2 = bind(genrand2, generateur2);

  double RND1 = rnd1();
  double RND2 = rnd2();

  if(m_echangChal<50 && TBEFF<25 && TGREFF<50) ///////////////////////
    m_inertieTemp += RND1;

  if(Tvap<m_temperatureEau)
    m_inertieTemp += (Tvap-m_temperatureEau)/3;
  else
    m_inertieTemp = max(0., m_inertieTemp-RND2);
}

void CircuitPrim::majTemperatureEau()
{
  m_temperatureEau = max(25, (0.5-TBEFF)/0.5*(645*TGREFF-140*m_debit/90+2*m_pression)+26+m_inertieTemp) /////////////////////
}

void CircuitPrim::majRadioactivite()
{
  random_device hgenerateur;
  default_random_engine generateur(hgenerateur());
  uniform_real_distribution<double> genrand(0,90);

  auto rnd = bind(genrand, generateur);
  double RND = rnd();

  m_radioactivite = 98*(m_debit+1) + RND + (0.5-TBEFF)*(MW+0.1)*6.54; ////////////////
}
*/

CircuitPrim::~CircuitPrim()
{
}
