#include "reacteur.hpp"
#include <random>

Reacteur::Reacteur() : m_propGrAct(0), m_propGrDemandee(0), m_tauxBoreDemande(0.47), m_tauxBoreAct(0.47), m_etatCuve(1.), m_radPiscine(), m_etatPiscine(1.), m_etatBarresGr(1.), m_etatCanaux(1.), m_etatInjBore(1.)
{
}

double Reacteur::getPropGrAct() const
{
  return m_propGrAct;
}

double Reacteur::getPropGrDemandee() const
{
  return m_propGrDemandee;
}

double Reacteur::getTauxBoreDemande() const
{
  return m_tauxBoreDemande;
}

double Reacteur::getTauxBoreAct() const
{
  return m_tauxBoreAct;
}

double Reacteur::getEtatCuve() const
{
  return m_etatCuve;
}

double Reacteur::getRadPiscine() const
{
  return m_radPiscine;
}

double Reacteur::getEtatPiscine() const
{
  return m_etatPiscine;
}

double Reacteur::getEtatBarresGr() const
{
  return m_etatBarresGr;
}

double Reacteur::getEtatCanaux() const
{
  return m_etatCanaux;
}

double Reacteur::getEtatInjBore() const
{
  return m_etatInjBore;
}

void Reacteur::majPropGrDemandee(double valeur_demandee)
{
  if((1-m_etatBarresGr)<=valeur_demandee && valeur_demandee<=1.)
    m_propGrDemandee = valeur_demandee;
  else if(valeur_demandee<1-m_etatBarresGr)
    m_propGrDemandee = 1-m_etatBarresGr;
  else
    m_propGrDemandee = 1.;
}

void Reacteur::majPropGrAct()
{
  if(m_propGrAct<m_propGrDemandee)
    m_propGrAct += 0.01;

  if(m_propGrAct>m_propGrDemandee)
    m_propGrAct -= 0.01;
}

void Reacteur::majTauxBoreDemande(double valeur_demandee)
{
  if(0<=valeur_demandee && valeur_demandee<=0.5)
    m_tauxBoreDemande = valeur_demandee;
  else if(valeur_demandee<0)
    m_tauxBoreDemande = 0.;
  else
    m_tauxBoreDemande = 0.5;
}

void Reacteur::majTauxBoreAct()
{
  if(m_tauxBoreAct<m_tauxBoreDemande)
    m_tauxBoreAct += 0.01;

  if(m_tauxBoreAct>m_tauxBoreDemande)
    m_tauxBoreAct -= 0.01;
}

void Reacteur::majEtatCuve(double valeur_demandee)
{
  if(0<=valeur_demandee && valeur_demandee<=1)
    m_etatCuve = valeur_demandee;
  else if(valeur_demandee<0)
    m_etatCuve = 0.;
  else
    m_etatCuve = 1.;
}

void Reacteur::majRadPiscine(double R1)
{
  auto RND = ((float)(rand()))/((float)(RAND_MAX))*45;
  m_radPiscine = (1-m_etatCuve)*R1 + 100 + RND;
}

void Reacteur::majEtatPiscine(double valeur_demandee)
{
  if(0<=valeur_demandee && valeur_demandee<=1)
    m_etatPiscine = valeur_demandee;
  else if(valeur_demandee<0)
    m_etatPiscine = 0.;
  else
    m_etatPiscine = 1.;
}

void Reacteur::majEtatBarresGr(double valeur_demandee)
{
  if(0<=valeur_demandee && valeur_demandee<=1)
    m_etatBarresGr = valeur_demandee;
  else if(valeur_demandee<0)
    m_etatBarresGr = 0.;
  else
    m_etatBarresGr = 1.;
}

void Reacteur::majEtatCanaux(double valeur_demandee)
{
  if(0<=valeur_demandee && valeur_demandee<=1)
    m_etatCanaux = valeur_demandee;
  else if(valeur_demandee<0)
    m_etatCanaux = 0.;
  else
    m_etatCanaux = 1.;
}

void Reacteur::majEtatInjBore(double valeur_demandee)
{
  if(0<=valeur_demandee && valeur_demandee<=1)
    m_etatInjBore = valeur_demandee;
  else if(valeur_demandee<0)
    m_etatInjBore = 0.;
  else
    m_etatInjBore = 1.;
}

void Reacteur::reparationInjecteurBore()
{
  if(m_etatInjBore > 0.96)
    m_etatInjBore = 1;
  else
  {
    auto RND = ((float)(rand()))/((float)(RAND_MAX))*0.04;
    m_etatInjBore += RND;
  }
}

Reacteur::~Reacteur()
{
}
