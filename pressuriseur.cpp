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

int Pressuriseur::temperatureDemandee() const
{
  return m_tempDemandee;
}

int Pressuriseur::temperatureActuel() const
{
  return m_temp_actuel;
}

Pressuriseur::~Pressuriseur()
{
}
