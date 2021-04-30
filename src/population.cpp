#include "population.hpp"

Population::Population():m_evacuation(0.),m_radioactiviteEau(0.),m_radioactiviteAir(0.),m_contamination(0)
{

}

double Population::evacuation() const
{
  return m_evacuation;
}

int Population::contamination() const
{
  return m_contamination;
}

double Population::radioactiviteEau() const
{
  return m_radioactiviteEau;
}

double Population::radioactiviteAir() const
{
  return m_radioactiviteAir;
}

void Population::majEvacuation(double valeur)
{
  m_evacuation = valeur;
}

void Population::majRadioactiviteEau(double valeur)
{
 m_radioactiviteEau = valeur;
}

void Population::majRadioactiviteAir(double valeur)
{
 m_radioactiviteAir = valeur;
}

void Population::majContamination(int valeur)
{
 m_contamination = valeur;
}

Population::~Population()
{

}
