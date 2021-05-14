#include "enceinte.hpp"

Enceinte::Enceinte() : m_etat(1), m_pression(1), m_radioactivite(0.00002) //constructeur
{
}


double Enceinte::etat() const //retourne l'état de l'enceinte
{
 return m_etat;
}


double Enceinte::pression() const //retourne la pression de l'enceinte
{
 return m_pression;
}


double Enceinte::radioactivite() const //retourne la radioactivité de l'enceinte
{
 return m_radioactivite;
}


void Enceinte::majPression(double valeur) //affecte une nouvelle valeure à la pression
{
 m_pression = valeur;
}


void Enceinte::majEtat(double valeur) //affecte une nouvelle valeur à l'état de l'enceinte
{
 m_etat = valeur;
}


void Enceinte::majRadioactivite(double valeur) //affecte une nouvelle valeur à la  radioactivité
{
 m_radioactivite = valeur;
}

Enceinte::~Enceinte() //destructeur
{
}
