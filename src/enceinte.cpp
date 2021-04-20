#include "enceinte.hpp"

Enceinte::Enceinte()
{
m_etat = 1;
m_pression = 1;
m_radioactivite = 0.00002;
}

double etat() const
{
 return m_etat;
}
double pression() const
{
 return m_pression;
}
double radioactivite() const
{
 return m_radioactivite;
}

void majPression(double valeur)
{
 m_pression = valeur;
}

void majEtat(double valeur)
{
 m_etat = valeur;
}

void majRadioactivite(double valeur)
{
 m_radioactivite = valeur;
}
