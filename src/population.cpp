#include "population.hpp"

Population::Population():m_evacuation(0.),m_radioactiviteEau(0.),m_radioactiviteAir(0.),m_contamination(0) //constructeur
{

}

double Population::evacuation() const //retoune le nombre de personnes évacuées
{
  return m_evacuation;
}

int Population::contamination() const //retourne le nombre de personnes contaminées
{
  return m_contamination;
}

double Population::radioactiviteEau() const //retourne la radioactivité de l'eau aux alentours
{
  return m_radioactiviteEau;
}

double Population::radioactiviteAir() const //retourne la radioactivité de l'air aux alentours
{
  return m_radioactiviteAir;
}

void Population::majEvacuation(double valeur) //met à jour le nombre de personnes évacuées
{
  m_evacuation = valeur;
}

void Population::majRadioactiviteEau(double valeur) //met à jour la radioactivité de l'eau aux alentours
{
  m_radioactiviteEau = valeur;
}

void Population::majRadioactiviteAir(double valeur) //met à jour la radioc=activité de l'air aux alentours
{
 m_radioactiviteAir = valeur;
}

void Population::majContamination(int valeur) //met à jour le nombre de personnes contaminées
{
 m_contamination = valeur;
}

Population::~Population() //destructeur
{

}
