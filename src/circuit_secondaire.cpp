#include <iostream>
#include <chrono>
#include <random>
#include <functional>
#include <algorithm>

#include "circuit_secondaire.hpp"


using namespace std;


CircuitSec::CircuitSec() : m_etatGenerateurVapeur(1.), m_temperatureVapeur(25), m_pressionVapeur(1.)
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

void CircuitSec::modifTemperatureVapeur(double etatEchangChaleur, double temperature1) // etatEchangChaleur = circuitPrim.etatEchangeurChaleur() & temperature1 = circuitPrim.temperatureEau()
{
  m_temperatureVapeur = max(etatEchangChaleur*(temperature1/1.51)+26+(m_inertieTemp*(m_inertieTemp>3)), 99.);
}

void CircuitSec::modifPressionVapeur()
{
  double regimePompe = m_pompe.rendement();
  if (m_temperatureVapeur < 120)
    m_pressionVapeur = 1;
  else
    m_pressionVapeur = max(1., (m_etatCircuit+0.1)*m_etatGenerateurVapeur*(regimePompe/50+(m_temperatureVapeur-135)/10));
}

void CircuitSec::modifDebitEau()
{
  double etatCondenseur = m_condenseur.etat();
  double regimePompe = m_pompe.rendement();

  double Z = m_etatCircuit*(etatCondenseur+0.1)*m_etatGenerateurVapeur*regimePompe*0.85;

  if(m_temperatureVapeur>3 && Z<3)
    m_debit = m_etatCircuit*(etatCondenseur+0.1)*m_etatGenerateurVapeur*1.3;
  else
    m_debit = Z;
}

void CircuitSec::modifDebitCondenseur()
{
  double etatCondenseur = m_condenseur.etat();
  double regimePompeCondenseur = m_condenseur.rendementPompe();

  double valeur = etatCondenseur*regimePompeCondenseur*150;
  m_condenseur.modifDebit(valeur);
}

void CircuitSec::modifDiffChaleurCondenseur()
{
  double debitCondenseur = m_condenseur.debit();

  double valeur = debitCondenseur/7.5;
  m_condenseur.modifDifferenceChaleur(valeur);
}

void CircuitSec::modifInertieTemperature(double temperatureEau) // temperatureEau = circuitPrim.temperatureEau()
{
  random_device hgenerateur;
  default_random_engine generateur1(hgenerateur());
  default_random_engine generateur2(hgenerateur());
  default_random_engine generateur3(hgenerateur());

  uniform_real_distribution<double> genrand1(0,0.15);
  uniform_real_distribution<double> genrand2(0,temperatureEau/100);
  uniform_real_distribution<double> genrand3(0,3);

  auto rnd1 = bind(genrand1, generateur1);
  auto rnd2 = bind(genrand2, generateur2);
  auto rnd3 = bind(genrand3, generateur3);

  double RND1 = rnd1();
  double RND2 = rnd2();
  double RND3 = rnd3();

  double regimePompe = m_pompe.rendement();

  if(regimePompe<(0.55+RND1) && temperatureEau>200)
    m_inertieTemp = RND2;
  else
    m_inertieTemp = max(m_inertieTemp-RND3, 0.);
}

void CircuitSec::modifRadioactivite(double etatEchangChaleur, double radioactivite1) // etatEchangChaleur = circuitPrim.etatEchangeurChaleur() & radioactivite1 = circuitPrim.radioactivite()
{
  m_radioactivite = max(m_radioactivite, (1.-etatEchangChaleur)*radioactivite1);
}

CircuitSec::~CircuitSec()
{
}
