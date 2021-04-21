#include <iostream>
#include <random>
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
  m_pressuriseur.majEtat(valeur);
}

void CircuitPrim::majEtatResistancePressuriseur(double valeur)
{
  m_pressuriseur.majEtatResistance(valeur);
}

void CircuitPrim::majEtatEchangeurChaleur(double valeur)
{
  if(valeur>=0 && valeur<=1)
    m_echangChal = valeur;
  else if(valeur<0)
    m_echangChal = 0;
  else
    m_echangChal = 1;
}

void CircuitPrim::majTempPressuriseurDemande(double valeur)
{
  m_pressuriseur.majTemperatureDemandee(valeur);
}

void CircuitPrim::majTempPressuriseurActuel()
{
  m_pressuriseur.majTemperatureActuel();
}

void CircuitPrim::majPression()
{
  double tempPressuriseurActuel = m_pressuriseur.temperatureActuel();
  m_pression = max((tempPressuriseurActuel-25)/3.24 + (m_temperatureEau-100)/83.3*(m_etatCircuit+0.1)*(m_echangChal+0.1), 1.);
}

void CircuitPrim::majDebitEau(double Ecuve)
{
  double rendementPompe = m_pompe.rendement();
  m_debit = m_etatCircuit*Ecuve*rendementPompe*90;
}

void CircuitPrim::majInertietemperature(double Tvap, double TBeff, double TGreff)  // Tvap = circuitSec.temperatureVapeur()
{
  auto RND1 = ((float)(rand()))/((float)(RAND_MAX))*26;
  auto RND2 = ((float)(rand()))/((float)(RAND_MAX))*16;

  if(m_echangChal<50 && TBeff<25 && TGreff<50)
    m_inertieTemp += RND1;

  if(Tvap<m_temperatureEau)
    m_inertieTemp += (Tvap-m_temperatureEau)/3;
  else
    m_inertieTemp = max(0., m_inertieTemp-RND2);
}

void CircuitPrim::majTemperatureEau(double TBeff, double TGreff)
{
  m_temperatureEau = max(25., (0.5-TBeff)/0.5*(645*TGreff-140*m_debit/90+2*m_pression)+26+m_inertieTemp);
}

void CircuitPrim::majRadioactivite(double TBeff, double MW)
{
  auto RND = ((float)(rand()))/((float)(RAND_MAX))*90;

  m_radioactivite = 98*(m_debit+1) + RND + (0.5-TBeff)*(MW+0.1)*6.54;
}


CircuitPrim::~CircuitPrim()
{
}
