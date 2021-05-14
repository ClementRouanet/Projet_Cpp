#include <random>

#include "condenseur.hpp"
#include "pompe.hpp"

using namespace std;


/* Constructeur */
Condenseur::Condenseur() : m_etat(1.), m_debit(0.), m_diffChaleur(0.)
{
}

/* Renvoie l'état du condenseur */
double Condenseur::etat() const
{
  return m_etat;
}

/* Renvoie le rendement du condenseur */
double Condenseur::rendementPompe() const
{
  return m_pompe.rendement();
}

/* Renvoie le débit du condenseur */
double Condenseur::debit() const
{
  return m_debit;
}

/* Renvoie la différence de chaleur du condenseur */
double Condenseur::differenceChaleur() const
{
  return m_diffChaleur;
}

/* Met a jour l'état du condenseur */
void Condenseur::majEtat(double valeur)
{
  if(valeur>=0 && valeur<=1)
    m_etat = valeur;
  else if(valeur<0)
    m_etat = 0;
  else
    m_etat = 1;
}

/* Met a jour le rendement du condenseur */
void Condenseur::majRendementPompe(double valeur)
{
  m_pompe.majRendement(valeur, m_etat);
}

/* Met a jour le débit du condenseur */
void Condenseur::majDebit(double valeur)
{
  m_debit = valeur;
}

/* Met a jour la différence de chaleur du condenseur */
void Condenseur::majDifferenceChaleur(double valeur)
{
  m_diffChaleur = valeur;
}

/* répare le condenseur lorsque les ouvriers sont sur place */
void Condenseur::reparation()
{
  if(m_etat > 0.98)
    m_etat = 1;
  else
  {
    auto RND = ((float)(rand()))/((float)(RAND_MAX))*0.02;
    m_etat += RND;
  }
}

/* Destructeur */
Condenseur::~Condenseur()
{
}
