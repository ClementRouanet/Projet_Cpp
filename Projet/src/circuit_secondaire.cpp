#include "circuit_secondaire.hpp"

using namespace std;


CircuitSec::CircuitSec() : m_etatGenerateurVapeur(1.), m_temperatureVapeur(25), m_pressionVapeur(1.)
{
}

double CircuitSec::etatGenerateurVapeur() const
{
  return m_etatGenerateurVapeur;
}

double CircuitSec::etatCondenseur() const
{
  return m_condenseur.etat();
}

double CircuitSec::rendementPompeCondenseur() const
{
  return m_condenseur.rendementPompe();
}

double CircuitSec::temperatureVapeur() const
{
  return m_temperatureVapeur;
}

double CircuitSec::pressionvapeur() const
{
  return m_pressionVapeur;
}

double CircuitSec::debitCondenseur() const
{
  return m_condenseur.debit();
}

double CircuitSec::differenceChaleurCondenseur() const
{
  return m_condenseur.differenceChaleur();
}

CircuitSec::~CircuitSec()
{
}
