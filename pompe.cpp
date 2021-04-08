#include "pompe.hpp"

using namespace std;

Pompe::Pompe() : m_etat(1.), m_rendement(0.)
{
}

void Pompe::ajusterRendement(double valeurDemandee)
{
  m_rendement = valeurDemandee;
}

double Pompe::rendement() const
{
  return m_rendement;
}

double Pompe::etat() const
{
  return m_etat;
}

Pompe::~Pompe()
{
}
