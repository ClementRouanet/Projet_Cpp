#include <random>

#include "pompe.hpp"

using namespace std;


/* Constructeur */
Pompe::Pompe() : m_etat(1.), m_rendement(0.)
{
}

/* renvoie le rendement de la pompe */
double Pompe::rendement() const
{
  return m_rendement;
}

/* Renvoie l'état de la pompe */
double Pompe::etat() const
{
  return m_etat;
}

/* Met à jour le rendement de la pompe */
void Pompe::majRendement(double valeur, double etat)
{
  if(valeur>=0 && valeur<=etat)
    m_rendement = valeur;
  else if(valeur<0)
    m_rendement = 0;
  else
    m_rendement = etat;
}

/* Met à jour l'état de la pompe */
void Pompe::majEtat(double valeur)
{
  if(valeur>=0 && valeur<=1)
    m_etat = valeur;
  else if(valeur<0)
    m_etat = 0;
  else
    m_etat = 1;
}

/* Répare la pompe lorsque les ouvriers sont sur place */
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

/* Destructeur */
Pompe::~Pompe()
{
}
