#include "population.hpp"

Population::Population()
{
  m_contamination = 0;
  m_evacuation = 0.;
  m_radioactiviteEau = 0.;
  m_radioactiviteAir = 0.;
}

double evacuation() const
{
  return m_evacuation;
}

int contamination() const
{
  return m_contamination;
}

double radioactiviteEau() const
{
  return m_radioactiviteEau;
}

double radioactiviteAir() const
{
  return m_radioactiviteAir;
}

void majEvacuation(double valeur)
{
  m_evacuation = valeur;
}

void majRadioactiviteEau(double valeur)
{
 m_radioactiviteEau = valeur;
}

void majRadioactiviteAir(double valeur)
{
 m_radioactiviteAir = valeur;
}

void majContamination(int valeur)
{
 m_contamination = valeur;
}
