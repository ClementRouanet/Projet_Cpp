#include <random>

#include "pressuriseur.hpp"

using namespace std;


/* Constructeur */
Pressuriseur::Pressuriseur() : m_etat(1.), m_etatResistance(1.), m_tempDemandee(25), m_tempActuel(25)
{
}

/* Renvoie l'état du pressuriseur */
double Pressuriseur::etat() const
{
  return m_etat;
}

/* Renvoie l'état de la résistance du pressuriseur */
double Pressuriseur::etatResistance() const
{
  return m_etatResistance;
}

/* Renvoie la température demandée pour le pressuriseur */
double Pressuriseur::temperatureDemandee() const
{
  return m_tempDemandee;
}

/* Renvoie la température actuelle du pressuriseur */
double Pressuriseur::temperatureActuel() const
{
  return m_tempActuel;
}

/* Met a jour l'état du pressuriseur */
void Pressuriseur::majEtat(double valeur)
{
  if(valeur>=0 && valeur<=1)
    m_etat = valeur;
  else if(valeur<0)
    m_etat = 0;
  else
    m_etat = 1;
}

/* Met a jour l'état de la résistance du pressuriseur */
void Pressuriseur::majEtatResistance(double valeur)
{
  if(m_etatResistance+valeur > m_etat)
    m_etatResistance = m_etat;
  else
  {
    if(valeur>=0 && valeur<=1)
      m_etatResistance = valeur;
    else if(valeur<0)
      m_etatResistance = 0;
    else
      m_etatResistance = 1;
  }
}

/* Met a jour la température demandée pour le pressuriseur */
void Pressuriseur::majTemperatureDemandee(double valeur)
{
  if(valeur>=25 && valeur<=100*(m_etat+m_etatResistance))
    m_tempDemandee = valeur;
  else if(valeur<25)
    m_tempDemandee = 25;
  else
    m_tempDemandee = 100*(m_etat+m_etatResistance);
}

/* Met a jour la température actuelle du pressuriseur */
void Pressuriseur::majTemperatureActuel()
{
  if(m_tempActuel < m_tempDemandee)
    m_tempActuel += 1;

  if(m_tempActuel > m_tempDemandee)
    m_tempActuel -= 1;
}

/* Répare le pressuriseur lorsque les ouvriers sont sur place */
void Pressuriseur::reparation()
{
  if(m_etat > 0.97)
  {
    m_etat = 1;
    majEtatResistance(1);
  }
  else
  {
    auto RND1 = ((float)(rand()))/((float)(RAND_MAX))*0.03;
    auto RND2 = ((float)(rand()))/((float)(RAND_MAX))*0.04;

    m_etat += RND1;
    majEtatResistance(m_etatResistance + RND2);
  }
}

/* Destructeur */
Pressuriseur::~Pressuriseur()
{
}
