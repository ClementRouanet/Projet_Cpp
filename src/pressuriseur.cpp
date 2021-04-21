#include "pressuriseur.hpp"

using namespace std;


Pressuriseur::Pressuriseur() : m_etat(1.), m_etatResistance(1.), m_tempDemandee(25), m_temp_actuel(25)
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
  return m_temp_actuel;
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
  if(valeur>=0 && valeur<=1)
    m_etatResistance = valeur;
  else if(valeur<0)
    m_etatResistance = 0;
  else
    m_etatResistance = 1;
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
  if(m_temp_actuel < m_tempDemandee)
    m_temp_actuel += 1;

  if(m_temp_actuel > m_tempDemandee)
    m_temp_actuel -= 1;
}

Pressuriseur::~Pressuriseur()
{
}
