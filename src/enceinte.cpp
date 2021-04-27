#include "enceinte.hpp"

Enceinte::Enceinte()
{
m_etat = 1.;
m_pression = 1.;
m_radioactivite = 0.00002;
}

double Enceinte::etat() const
{
 return m_etat;
}
double Enceinte::pression() const
{
 return m_pression;
}
double Enceinte::radioactivite() const
{
 return m_radioactivite;
}

void Enceinte::majPression(double valeur)
{
 m_pression = valeur;
}

void Enceinte::majEtat(double valeur)
{
 m_etat = valeur;
}

void Enceinte::majRadioactivite(double valeur)
{
 m_radioactivite = valeur;
}

Enceinte::~Enceinte()
{

}
