#include "circuit.hpp"

using namespace std;


/* Constructeur */
Circuit::Circuit()
    : m_etatCircuit(1.), m_debit(0.), m_inertieTemp(0.), m_radioactivite(0.)
{
}

/* Renvoie l'état du circuit */
double Circuit::etatCircuit() const
{
  return m_etatCircuit;
}

/* Renvoie l'état de la pompe du circuit*/
double Circuit::etatPompe() const
{
  return m_pompe.etat();
}

/* renvoie le rendement de la pompe du circuit*/
double Circuit::rendementPompe() const
{
  return m_pompe.rendement();
}

/* Renvoie le débit de l'eau dans le circuit */
double Circuit::debitEau() const
{
  return m_debit;
}

/* Renvoie l'inertie de température dans le circuit */
double Circuit::inertieTemperature() const
{
  return m_inertieTemp;
}

/* Renvoie la radioactivité du circuit */
double Circuit::radioactivite() const
{
  return m_radioactivite;
}

/* Met a jour l'état du circuit */
void Circuit::majEtatCircuit(double valeur)
{
  if(valeur>=0 && valeur<=1)
    m_etatCircuit = valeur;
  else if(valeur<0)
    m_etatCircuit = 0;
  else
    m_etatCircuit = 1;
}

/* Met a jour l'état de la pompe du circuit */
void Circuit::majEtatPompe(double valeur)
{
  m_pompe.majEtat(valeur);
}

/* Met a jour le rendement de la pompe du circuit */
void Circuit::majRendementPompe(double valeur)
{
  m_pompe.majRendement(valeur, m_etatCircuit);
}

/* Répare le circuit lorsque les ouvriers sont sur place */
void Circuit::reparationPompe()
{
  m_pompe.reparation();
}

/* Destructeur */
Circuit::~Circuit()
{
}
