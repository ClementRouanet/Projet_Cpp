#include <iostream>
#include <random>
#include <algorithm>

#include "circuit_secondaire.hpp"


using namespace std;


CircuitSec::CircuitSec() : m_etatGenerateurVapeur(1.), m_temperatureVapeur(25.), m_pressionVapeur(1.)
{
}

double CircuitSec::etatGenerateurVapeur() const
{
  return m_etatGenerateurVapeur;
}

double CircuitSec::etatCondenseur() const
{
  return m_condenseur.etat();
}

double CircuitSec::rendementPompeCondenseur() const
{
  return m_condenseur.rendementPompe();
}

double CircuitSec::temperatureVapeur() const
{
  return m_temperatureVapeur;
}

double CircuitSec::pressionVapeur() const
{
  return m_pressionVapeur;
}

double CircuitSec::debitCondenseur() const
{
  return m_condenseur.debit();
}

double CircuitSec::diffChaleurCondenseur() const
{
  return m_condenseur.differenceChaleur();
}

void CircuitSec::majEtatGenerateurVapeur(double valeur)
{
  if(valeur>=0 && valeur<=1)
    m_etatGenerateurVapeur = valeur;
  else if(valeur<0)
    m_etatGenerateurVapeur = 0;
  else
    m_etatGenerateurVapeur = 1;
}

void CircuitSec::majEtatCondenseur(double valeur)
{
  m_condenseur.majEtat(valeur);
}

void CircuitSec::majRendementPompeCondenseur(double valeur)
{
  m_condenseur.majRendementPompe(valeur);
}

void CircuitSec::majTemperatureVapeur(double etatEchangChaleur, double temperature1) // etatEchangChaleur = circuitPrim.etatEchangeurChaleur() & temperature1 = circuitPrim.temperatureEau()
{
  m_temperatureVapeur = max(etatEchangChaleur*(temperature1/1.51)+26+(m_inertieTemp*(m_inertieTemp>3)), 99.);
}

void CircuitSec::majPressionVapeur()
{
  double regimePompe = m_pompe.rendement();
  if (m_temperatureVapeur < 120)
    m_pressionVapeur = 1;
  else
    m_pressionVapeur = max(1., (m_etatCircuit+0.1)*m_etatGenerateurVapeur*(regimePompe/50+(m_temperatureVapeur-135)/10));
}

void CircuitSec::majDebitEau()
{
  double etatCondenseur = m_condenseur.etat();
  double regimePompe = m_pompe.rendement();

  double Z = m_etatCircuit*(etatCondenseur+0.1)*m_etatGenerateurVapeur*regimePompe*0.85;

  if(m_temperatureVapeur>3 && Z<3)
    m_debit = m_etatCircuit*(etatCondenseur+0.1)*m_etatGenerateurVapeur*1.3;
  else
    m_debit = Z;
}

void CircuitSec::majDebitCondenseur()
{
  double etatCondenseur = m_condenseur.etat();
  double regimePompeCondenseur = m_condenseur.rendementPompe();

  double valeur = etatCondenseur*regimePompeCondenseur*150;
  m_condenseur.majDebit(valeur);
}

void CircuitSec::majDiffChaleurCondenseur()
{
  double debitCondenseur = m_condenseur.debit();

  double valeur = debitCondenseur/7.5;
  m_condenseur.majDifferenceChaleur(valeur);
}

void CircuitSec::majInertieTemperature(double temperatureEau) // temperatureEau = circuitPrim.temperatureEau()
{
  auto RND1 = ((float)(rand()))/((float)(RAND_MAX))*0.15;
  auto RND2 = ((float)(rand()))/((float)(RAND_MAX))*(temperatureEau/100);
  auto RND3 = ((float)(rand()))/((float)(RAND_MAX))*3;

  double regimePompe = m_pompe.rendement();

  if(regimePompe<(0.55+RND1) && temperatureEau>200)
    m_inertieTemp = RND2;
  else
    m_inertieTemp = max(m_inertieTemp-RND3, 0.);
}

void CircuitSec::majRadioactivite(double etatEchangChaleur, double radioactivite1) // etatEchangChaleur = circuitPrim.etatEchangeurChaleur() & radioactivite1 = circuitPrim.radioactivite()
{
  m_radioactivite = max(m_radioactivite, (1.-etatEchangChaleur)*radioactivite1);
}

CircuitSec::~CircuitSec()
{
}
