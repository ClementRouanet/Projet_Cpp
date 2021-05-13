#include <iostream>
#include <random>
#include <algorithm>

#include "circuit_primaire.hpp"

using namespace std;


/* Constructeur */
CircuitPrim::CircuitPrim() : Circuit(), m_echangChal(1.), m_pression(1.), m_temperatureEau(25.)
{
}

/* Renvoie l'état du pressuriseur du circuit primaire */
double CircuitPrim::etatPressuriseur() const
{
  return m_pressuriseur.etat();
}

/* Renvoie l'état de la résistance du pressuriseur du circuit primaire */
double CircuitPrim::etatResistancePressuriseur() const
{
  return m_pressuriseur.etatResistance();
}

/* Renvoie l'état de l'échangeur de chaleur du circuit primaire */
double CircuitPrim::etatEchangeurChaleur() const
{
  return m_echangChal;
}

/* Renvoie la température demandée pour le pressuriseur du circuit primaire */
double CircuitPrim::tempPressuriseurDemande() const
{
  return m_pressuriseur.temperatureDemandee();
}

/* Renvoie la température actuelle du circuit primaire */
double CircuitPrim::tempPressuriseurActuel() const
{
  return m_pressuriseur.temperatureActuel();
}

/* Renvoie la pression du circuit primaire */
double CircuitPrim::pression() const
{
  return m_pression;
}

/* Renvoie la température de l'eau dans le circuit primaire */
double CircuitPrim::temperatureEau() const
{
  return m_temperatureEau;
}

/* Met a jour l'état du pressuriseur du circuit primaire */
void CircuitPrim::majEtatPressuriseur(double valeur)
{
  m_pressuriseur.majEtat(valeur);
}

/* Met a jour l'état de la résistance du pressuriseur du circuit primaire */
void CircuitPrim::majEtatResistancePressuriseur(double valeur)
{
  m_pressuriseur.majEtatResistance(valeur);
}

/* Met a jour l'état de l'échangeur de chaleur du circuit primaire */
void CircuitPrim::majEtatEchangeurChaleur(double valeur)
{
  if(valeur>=0 && valeur<=1)
    m_echangChal = valeur;
  else if(valeur<0)
    m_echangChal = 0;
  else
    m_echangChal = 1;
}

/* Met a jour la température demandée dans le circuit primaire */
void CircuitPrim::majTempPressuriseurDemande(double valeur)
{
  m_pressuriseur.majTemperatureDemandee(valeur);
}

/* Met a jour la température actuele du circuit primaire */
void CircuitPrim::majTempPressuriseurActuel()
{
  m_pressuriseur.majTemperatureActuel();
}

/* Met a jour la pression dans le circuit primaire */
void CircuitPrim::majPression()
{
  double tempPressuriseurActuel = m_pressuriseur.temperatureActuel();
  m_pression = max((tempPressuriseurActuel-25)/3.24 + (m_temperatureEau-100)/83.3*(m_etatCircuit+0.1)*(m_echangChal+0.1), 1.);
}

/* Met a jour la débit de l'eau dans le circuit primaire */
void CircuitPrim::majDebitEau(double Ecuve)
{
  double rendementPompe = m_pompe.rendement();
  m_debit = m_etatCircuit*Ecuve*rendementPompe*90;
}

/* Met a jour l'inertie de température dans le circuit primaire */
void CircuitPrim::majInertietemperature(double Tvap, double TBeff, double TGreff)  // Tvap = circuitSec.temperatureVapeur()
{
  auto RND1 = ((float)(rand()))/((float)(RAND_MAX))*26; // nombre réel aléatoire entre 0 et 26
  auto RND2 = ((float)(rand()))/((float)(RAND_MAX))*16; // nombre réel aléatoire entre 0 et 16

  if(m_echangChal<0.5 && TBeff<0.25 && TGreff<0.5)
    m_inertieTemp += RND1;

  if(Tvap<m_temperatureEau)
    m_inertieTemp += (Tvap-m_temperatureEau)/3;
  else
    m_inertieTemp = max(0., m_inertieTemp-RND2);
}

/* Met a jour la température de l'eau dans le circuit primaire */
void CircuitPrim::majTemperatureEau(double TBeff, double TGreff)
{
  m_temperatureEau = max(25., ((0.5-TBeff)/0.5)*(645*TGreff-140*(m_debit/90)+2*m_pression)+26+m_inertieTemp);
}

/* Met a jour la radioactivité dans le circuit primaire */
void CircuitPrim::majRadioactivite(double TBeff, double MW)
{
  auto RND = ((float)(rand()))/((float)(RAND_MAX))*90; // nombre réel aléatoire entre 0 et 90

  m_radioactivite = 98*(m_debit+1) + RND + (0.5-TBeff)*(MW+0.1)*6.54;
}

/* Réparation de l'état du circuit primare par les ouvriers */
void CircuitPrim::reparationEtat()
{
  if(m_etatCircuit >= 0.8)
    m_etatCircuit = 1;
  else
  {
    auto RND = ((float)(rand()))/((float)(RAND_MAX))*0.02; // nombre réel aléatoire entre 0 et 0.02
    m_etatCircuit += RND;
  }
}

/* Réparation de l'état du pressuriseur du circuit primare par les ouvriers */
void CircuitPrim::reparationPressuriseur()
{
  m_pressuriseur.reparation();
}

/* Destructeur */
CircuitPrim::~CircuitPrim()
{
}
