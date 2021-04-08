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

void Condenseur::rendementPompe(double valeur)
{
  m_pompe.ajusterRendement(valeur);
}

double Condenseur::debit() const
{
  return m_debit;
}

double Condenseur::differenceChaleur() const
{
  return m_diffChaleur;
}

Condenseur::~Condenseur()
{
}
