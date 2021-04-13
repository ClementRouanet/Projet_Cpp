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

void Condenseur::modifDebit(double valeur)
{
  m_debit = valeur;
}

void Condenseur::modifDifferenceChaleur(double valeur)
{
  m_diffChaleur = valeur;
}

Condenseur::~Condenseur()
{
}
