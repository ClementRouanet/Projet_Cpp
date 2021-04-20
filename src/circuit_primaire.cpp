#include "circuit_primaire.hpp"

using namespace std;


CircuitPrim::CircuitPrim() : Circuit(), m_echangChal(1.), m_pression(1.), m_temperatureEau(25)
{
}

double CircuitPrim::etatPressuriseur() const
{
  return m_pressuriseur.etat();
}

double CircuitPrim::etatResistancePressuriseur() const
{
  return m_pressuriseur.etatResistance();
}

double CircuitPrim::etatEchangeurChaleur() const
{
  return m_echangChal;
}

int CircuitPrim::tempPressuriseurDemande() const
{
  return m_pressuriseur.temperatureDemandee();
}

int CircuitPrim::tempPressuriseurActuel() const
{
  return m_pressuriseur.temperatureActuel();
}

double CircuitPrim::pression() const
{
  return m_pression;
}

double CircuitPrim::temperatureEau() const
{
  return m_temperatureEau;
}

CircuitPrim::~CircuitPrim()
{
}
