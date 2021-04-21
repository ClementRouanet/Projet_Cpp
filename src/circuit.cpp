#include "circuit.hpp"
#include "pompe.hpp"

using namespace std;


Circuit::Circuit()
    : m_etatCircuit(1.), m_debit(0.), m_inertieTemp(0.), m_radioactivite(0.)
{
}

double Circuit::etatCircuit() const
{
  return m_etatCircuit;
}

double Circuit::etatPompe() const
{
  return m_pompe.etat();
}

double Circuit::rendementPompe() const
{
  return m_pompe.rendement();
}

double Circuit::debitEau() const
{
  return m_debit;
}

double Circuit::inertieTemperature() const
{
  return m_inertieTemp;
}

double Circuit::radioactivite() const
{
  return m_radioactivite;
}

void Circuit::majEtatCircuit(double valeur)
{
  if(valeur>=0 && valeur<=1)
    m_etatCircuit = valeur;
  else if(valeur<0)
    m_etatCircuit = 0;
  else
    m_etatCircuit = 1;
}

void Circuit::majEtatPompe(double valeur)
{
  m_pompe.majEtat(valeur);
}

void Circuit::majRendementPompe(double valeur)
{
  m_pompe.majRendement(valeur, m_etatCircuit);
}

Circuit::~Circuit()
{
}
