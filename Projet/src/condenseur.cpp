#include "condenseur.hpp"
#include "pompe.hpp"

using namespace std;


Condenseur::Condenseur() : m_etat(1.), m_debit(0.), m_diffChaleur(0.)
{
}

double Condenseur::etat() const
{
  return m_etat;
}

double Condenseur::rendementPompe() const
{
  return m_pompe.rendement();
}

double Condenseur::debit() const
{
  return m_debit;
}

double Condenseur::differenceChaleur() const
{
  return m_diffChaleur;
}

void Condenseur::majEtat(double valeur)
{
  if(valeur>=0 && valeur<=1)
    m_etat = valeur;
  else if(valeur<0)
    m_etat = 0;
  else
    m_etat = 1;
}

void Condenseur::majRendementPompe(double valeur)
{
  m_pompe.majRendement(valeur, m_etat);
}

void Condenseur::majDebit(double valeur)
{
  m_debit = valeur;
}

void Condenseur::majDifferenceChaleur(double valeur)
{
  m_diffChaleur = valeur;
}

Condenseur::~Condenseur()
{
}
