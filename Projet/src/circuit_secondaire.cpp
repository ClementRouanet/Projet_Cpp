#include <iostream>
#include <random>
#include <algorithm>

#include "circuit_secondaire.hpp"


using namespace std;


/* Destructeur */
CircuitSec::CircuitSec() : m_etatGenerateurVapeur(1.), m_temperatureVapeur(25.), m_pressionVapeur(1.)
{
}

/* Renvoie l'état du générateur de vapeur du circuit secondaire*/
double CircuitSec::etatGenerateurVapeur() const
{
  return m_etatGenerateurVapeur;
}

/* Renvoie l'état du condenseur du circuit secondaire*/
double CircuitSec::etatCondenseur() const
{
  return m_condenseur.etat();
}

/* Renvoie le rendement du condenseur du circuit secondaire*/
double CircuitSec::rendementPompeCondenseur() const
{
  return m_condenseur.rendementPompe();
}

/* Renvoie la température de la vapeur du circuit secondaire*/
double CircuitSec::temperatureVapeur() const
{
  return m_temperatureVapeur;
}

/* Renvoie la pression de la vapeur du circuit secondaire*/
double CircuitSec::pressionVapeur() const
{
  return m_pressionVapeur;
}

/* Renvoie le débit du condenseur du circuit secondaire*/
double CircuitSec::debitCondenseur() const
{
  return m_condenseur.debit();
}

/* Renvoie la différence de chaleur du condenseur du circuit secondaire*/
double CircuitSec::diffChaleurCondenseur() const
{
  return m_condenseur.differenceChaleur();
}

/* Met a jour l'état du générateur de vapeur du circuit secondaire*/
void CircuitSec::majEtatGenerateurVapeur(double valeur)
{
  if(valeur>=0 && valeur<=1)
    m_etatGenerateurVapeur = valeur;
  else if(valeur<0)
    m_etatGenerateurVapeur = 0;
  else
    m_etatGenerateurVapeur = 1;
}

/* Met a jour l'état du condenseur du circuit secondaire*/
void CircuitSec::majEtatCondenseur(double valeur)
{
  m_condenseur.majEtat(valeur);
}

/* Met a jour le rendement du condenseur du circuit secondaire*/
void CircuitSec::majRendementPompeCondenseur(double valeur)
{
  m_condenseur.majRendementPompe(valeur);
}

/* Met a jour la température de la vapeur du circuit secondaire*/
void CircuitSec::majTemperatureVapeur(double etatEchangChaleur, double temperature1)
{
  m_temperatureVapeur = max(etatEchangChaleur*(temperature1/1.51)+26+(m_inertieTemp*(m_inertieTemp>3)), 99.);
}

/* Met a jour la pression de la vapeur dans le circuit secondaire*/
void CircuitSec::majPressionVapeur()
{
  double regimePompe = m_pompe.rendement();
  if (m_temperatureVapeur < 120)
    m_pressionVapeur = 1;
  else
    m_pressionVapeur = max(1., (m_etatCircuit+0.1)*m_etatGenerateurVapeur*(regimePompe/50+(m_temperatureVapeur-135)/10));
}

/* Met a jour le débit de l'eau du circuit secondaire*/
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

/* Met a jour le débit du condenseur du circuit secondaire*/
void CircuitSec::majDebitCondenseur()
{
  double etatCondenseur = m_condenseur.etat();
  double regimePompeCondenseur = m_condenseur.rendementPompe();

  double valeur = etatCondenseur*regimePompeCondenseur*150;
  m_condenseur.majDebit(valeur);
}

/* Met a jour la différence de chaleur du condenseur du circuit secondaire*/
void CircuitSec::majDiffChaleurCondenseur()
{
  double debitCondenseur = m_condenseur.debit();

  double valeur = debitCondenseur/7.5;
  m_condenseur.majDifferenceChaleur(valeur);
}

/* Met a jour l'inertie de température du circuit secondaire*/
void CircuitSec::majInertieTemperature(double temperatureEau) // temperatureEau = circuitPrim.temperatureEau()
{
  auto RND1 = ((float)(rand()))/((float)(RAND_MAX))*0.15; // Nombre réel aléatoire entre 0 et 0.15
  auto RND2 = ((float)(rand()))/((float)(RAND_MAX))*(temperatureEau/100); // Nombre réel aléatoire entre 0 et temperatureEau/100
  auto RND3 = ((float)(rand()))/((float)(RAND_MAX))*3; // Nombre réel aléatoire entre 0 et 3

  double regimePompe = m_pompe.rendement();

  if(regimePompe<(0.55+RND1) && temperatureEau>200)
    m_inertieTemp = RND2;
  else
    m_inertieTemp = max(m_inertieTemp-RND3, 0.);
}

/* Met a jour la radioactivité du circuit secondaire*/
void CircuitSec::majRadioactivite(double etatEchangChaleur, double radioactivite1) // etatEchangChaleur = circuitPrim.etatEchangeurChaleur() & radioactivite1 = circuitPrim.radioactivite()
{
  m_radioactivite = max(m_radioactivite, (1.-etatEchangChaleur)*radioactivite1);
}

/* Répare le générateur de vapeur lorsque les ouvriers sont sur place */
void CircuitSec::reparationGenerateurVapeur()
{
  if(m_etatGenerateurVapeur >= 0.89)
    m_etatGenerateurVapeur = 1;
  else
  {
    auto RND = ((float)(rand()))/((float)(RAND_MAX))*0.05; // Nombre réel aléatoire entre 0 et 0.05
    m_etatGenerateurVapeur += RND;
  }
}

/* Répare l'état du circuit secondaire lorsque les ouvriers sont sur place */
void CircuitSec::reparationEtat()
{
  if(m_etatCircuit >= 0.78)
    m_etatCircuit = 1;
  else
  {
    auto RND = ((float)(rand()))/((float)(RAND_MAX))*0.02; // Nombre réel aléatoire entre 0 et 0.02
    m_etatCircuit += RND;
  }
}

/* Répare le condenseur lorsque les ouvriers sont sur place */
void CircuitSec::reparationCondenseur()
{
  m_condenseur.reparation();
}

/* Destructeur */
CircuitSec::~CircuitSec()
{
}
