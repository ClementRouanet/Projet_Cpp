#include <random>

#include "pressuriseur.hpp"

using namespace std;


Pressuriseur::Pressuriseur() : m_etat(1.), m_etatResistance(1.), m_tempDemandee(25), m_tempActuel(25)
{
}

double Pressuriseur::etat() const
{
  return m_etat;
}

double Pressuriseur::etatResistance() const
{
  return m_etatResistance;
}

double Pressuriseur::temperatureDemandee() const
{
  return m_tempDemandee;
}

double Pressuriseur::temperatureActuel() const
{
  return m_tempActuel;
}

void Pressuriseur::majEtat(double valeur)
{
  if(valeur>=0 && valeur<=1)
    m_etat = valeur;
  else if(valeur<0)
    m_etat = 0;
  else
    m_etat = 1;
}

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

void Pressuriseur::majTemperatureDemandee(double valeur)
{
  if(valeur>=25 && valeur<=100*(m_etat+m_etatResistance))
    m_tempDemandee = valeur;
  else if(valeur<25)
    m_tempDemandee = 25;
  else
    m_tempDemandee = 100*(m_etat+m_etatResistance);
}

void Pressuriseur::majTemperatureActuel()
{
  if(m_tempActuel < m_tempDemandee)
    m_tempActuel += 1;

  if(m_tempActuel > m_tempDemandee)
    m_tempActuel -= 1;
}

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

Pressuriseur::~Pressuriseur()
{
}
