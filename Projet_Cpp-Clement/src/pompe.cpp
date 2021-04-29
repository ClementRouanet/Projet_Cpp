#include <random>

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

void Pompe::majRendement(double valeur, double etat)
{
  if(valeur>=0 && valeur<=etat)
    m_rendement = valeur;
  else if(valeur<0)
    m_rendement = 0;
  else
    m_rendement = etat;
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

void Pompe::reparation()
{
  if(m_etat > 0.97)
    m_etat = 1;
  else
  {
    auto RND = ((float)(rand()))/((float)(RAND_MAX))*0.03;
    m_etat += RND;
  }
}

Pompe::~Pompe()
{
}
