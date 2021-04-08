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

void Circuit::rendementPompe(double valeur)
{
  m_pompe.ajusterRendement(valeur);
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

Circuit::~Circuit()
{
}
