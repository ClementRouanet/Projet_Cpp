#include "pompe.hpp"

using namespace std;

Pompe::Pompe() : m_etat(1.), m_rendement(0.)
{
}

double Pompe::rendement() const
{
  return m_rendement;
}

double Pompe::etat() const
{
  return m_etat;
}

void Pompe::majRendement(double valeur)
{
  if(valeur>=0 && valeur<=m_etat)
    m_rendement = valeur;
  else if(valeur<0)
    m_rendement = 0;
  else
    m_rendement = m_etat;
}

void Pompe::majEtat(double valeur)
{
  if(valeur>=0 && valeur<=1)
    m_etat = valeur;
  else if(valeur<0)
    m_etat = 0;
  else
    m_etat = 1;
}

Pompe::~Pompe()
{
}
