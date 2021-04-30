#include "ouvriers.hpp"
#include <string>
#include <random>
#include <vector>
using namespace std;

Ouvriers::Ouvriers() : m_nombreOuvriersDispo(145)
{
  for(int i=0;i<145;i++)
  {
    m_etatSante[i] = 1; m_etatMission[i] = 0; m_estDispo[i] = 1; m_lieuMission[i] = "reserve";
  }
}

vector<int> Ouvriers::getEtatSante() const
{
  return m_etatSante;
}

vector<int> Ouvriers::getEtatMission() const
{
  return m_etatMission;
}

vector<string> Ouvriers::getLieuMission() const
{
  return m_lieuMission;
}

int Ouvriers::getNombreOuvriersDispo() const
{
  return m_nombreOuvriersDispo;
}

void Ouvriers::majEtatSante(Centrale& centrale)
{
  for(int i=0;i<145;i++)
  {
    auto RND = ((float)(rand()))/((float)(RAND_MAX))*100;
    if(m_lieuMission[i]=="circuit primaire" && centrale.etatCircuitPrim()<0.2)
    {
      m_etatSante[i] = 0; m_etatMission[i] = 1;
    }
    if(m_lieuMission[i]=="generateur de vapeur" && RND<=10)
    {
      m_etatSante[i] = 0; m_etatMission[i] = 1;
    }
    if(m_lieuMission[i]=="reacteur" && (centrale.radioactiviteEnceinte()>12 || centrale.pressionEnceinte()>3))
    {
      m_etatSante[i] = 0; m_etatMission[i] = 1;
    }
    if(centrale.temperatureVapeur()>300 || centrale.productionCentrale()>1000)
    {
      m_etatSante[i] = 0; m_etatMission[i] = 1;
    }
  }
}

int Ouvriers::majNombreOuvriersDispo()
{
  m_nombreOuvriersDispo = 0;
  for(int i=0;i<145;i++)
  {
    if(m_etatSante[i]==1 && m_etatMission[i]==0)
    {
      m_estDispo[i] = 1;
    }
    if(m_etatSante[i]==0 || m_etatMission[i]==1)
    {
      m_estDispo[i] = 0;
    }
    if(m_estDispo[i]==1)
    {
      m_nombreOuvriersDispo++;
    }
  }
  return m_nombreOuvriersDispo;
}

void Ouvriers::envoyerOuvriers(string lieu, Centrale& centrale)
{
  if(interventionPossible(centrale)!=0)
  {
    m_nombreOuvriersDispo = majNombreOuvriersDispo();
    if(lieu=="pompe primaire" && m_nombreOuvriersDispo>=8)
    {
      centrale.reparationPompePrim();
      int compteur = 0;
      for(int i=0;i<145;i++)
      {
        if(m_estDispo[i]==1 && compteur<8)
        {
          m_etatMission[i] = 1, m_lieuMission[i] = lieu;
          compteur++;
        }
      }
      m_nombreOuvriersDispo = majNombreOuvriersDispo();
    }
    if(lieu=="pompe secondaire" && m_nombreOuvriersDispo>=8)
    {
      centrale.reparationPompeSec();
      int compteur = 0;
      for(int i=0;i<145;i++)
      {
        if(m_estDispo[i]==1 && compteur<8)
        {
          m_etatMission[i] = 1, m_lieuMission[i] = lieu;
          compteur++;
        }
      }
      m_nombreOuvriersDispo = majNombreOuvriersDispo();
    }
    if(lieu=="condenseur" && m_nombreOuvriersDispo>=20)
    {
      centrale.reparationCondenseur();
      int compteur = 0;
      for(int i=0;i<145;i++)
      {
        if(m_estDispo[i]==1 && compteur<20)
        {
          m_etatMission[i] = 1, m_lieuMission[i] = lieu;
          compteur++;
        }
      }
      m_nombreOuvriersDispo = majNombreOuvriersDispo();
    }
    if(lieu=="generateur de vapeur" && m_nombreOuvriersDispo>=60)
    {
      centrale.reparationGenerateurVapeur();
      int compteur = 0;
      for(int i=0;i<145;i++)
      {
        if(m_estDispo[i]==1 && compteur<60)
        {
          m_etatMission[i] = 1, m_lieuMission[i] = lieu;
          compteur++;
        }
      }
      m_nombreOuvriersDispo = majNombreOuvriersDispo();
    }
    if(lieu=="injecteur Bore" && m_nombreOuvriersDispo>=5)
    {
      centrale.reparationInjecteurBore();
      int compteur = 0;
      for(int i=0;i<145;i++)
      {
        if(m_estDispo[i]==1 && compteur<5)
        {
          m_etatMission[i] = 1, m_lieuMission[i] = lieu;
          compteur++;
        }
      }
      m_nombreOuvriersDispo = majNombreOuvriersDispo();
    }
    if(lieu=="circuit primaire" && m_nombreOuvriersDispo>=45)
    {
      centrale.reparationCircuitPrim();
      int compteur = 0;
      for(int i=0;i<145;i++)
      {
        if(m_estDispo[i]==1 && compteur<45)
        {
          m_etatMission[i] = 1, m_lieuMission[i] = lieu;
          compteur++;
        }
      }
      m_nombreOuvriersDispo = majNombreOuvriersDispo();
    }
    if(lieu=="circuit secondaire" && m_nombreOuvriersDispo>=20)
    {
      centrale.reparationCircuitSec();
      int compteur = 0;
      for(int i=0;i<145;i++)
      {
        if(m_estDispo[i]==1 && compteur<20)
        {
          m_etatMission[i] = 1, m_lieuMission[i] = lieu;
          compteur++;
        }
      }
      m_nombreOuvriersDispo = majNombreOuvriersDispo();
    }
    if(lieu=="pressuriseur" && m_nombreOuvriersDispo>=10)
    {
      centrale.reparationPressuriseur();
      int compteur = 0;
      for(int i=0;i<145;i++)
      {
        if(m_estDispo[i]==1 && compteur<10)
        {
          m_etatMission[i] = 1, m_lieuMission[i] = lieu;
          compteur++;
        }
      }
      m_nombreOuvriersDispo = majNombreOuvriersDispo();
    }
  }
}

void Ouvriers::rappelerOuvriers(Centrale& centrale)
{
  for(int i=0;i<145;i++)
  {
    if(m_lieuMission[i]=="pompe primaire" && centrale.etatPompePrim()==1 && m_etatSante[i]==1)
    {
      m_estDispo[i] = 1;
    }
    if(m_lieuMission[i]=="pompe secondaire" && centrale.etatPompeSec()==1 && m_etatSante[i]==1)
    {
      m_estDispo[i] = 1;
    }
    if(m_lieuMission[i]=="condenseur" && centrale.etatCondenseur()==1 && m_etatSante[i]==1)
    {
      m_estDispo[i] = 1;
    }
    if(m_lieuMission[i]=="generateur de vapeur" && centrale.etatGenerateurVapeur()==1 && m_etatSante[i]==1)
    {
      m_estDispo[i] = 1;
    }
    if(m_lieuMission[i]=="injecteur Bore" && centrale.etatInjBore()==1 && m_etatSante[i]==1)
    {
      m_estDispo[i] = 1;
    }
    if(m_lieuMission[i]=="circuit primaire" && centrale.etatCircuitPrim()==1 && m_etatSante[i]==1)
    {
      m_estDispo[i] = 1;
    }
    if(m_lieuMission[i]=="circuit secondaire" && centrale.etatCircuitSec()==1 && m_etatSante[i]==1)
    {
      m_estDispo[i] = 1;
    }
    if(m_lieuMission[i]=="pressuriseur" && centrale.etatPressuriseur()==1 && m_etatSante[i]==1)
    {
      m_estDispo[i] = 1;
    }
  }
}

void Ouvriers::guerir()
{
  auto RND = ((float)(rand()))/((float)(RAND_MAX))*100;
  for(int i=0;i<145;i++)
  {
    if(m_etatSante[i]==0 && RND<=40)
    {
      m_etatSante[i] = 1;
    }
  }
}

int Ouvriers::nombreEnIntervention()
{
  int n(0);
  for(int i=0;i<145;i++)
  {
    if(m_etatMission[i]==1)
    {
      n++;
    }
  }
  return n;
}

int Ouvriers::interventionPossible(Centrale& centrale)
{
  if(centrale.etatCircuitPrim()<0.2)
    return 0;
  if((centrale.radioactiviteEnceinte()>12 || centrale.pressionEnceinte()>3))
    return 0;
  if(centrale.temperatureVapeur()>300 || centrale.productionCentrale()>1000)
    return 0;
  return 1;
}

void Ouvriers::annulerIntervention(string lieu)
{
  for(int i=0;i<145;i++)
  {
    if(m_lieuMission[i]==lieu && m_etatMission[i]==1)
    {
      m_etatMission[i] = 0; m_lieuMission[i] = "reserve";
    }
  }
}

int Ouvriers::nombreOuvriersBlesses()
{
  int n(0);
  for(int i=0;i<145;i++)
  {
    if(m_etatSante[i]==0)
    {
      n++;
    }
  }
  return n;
}

Ouvriers::~Ouvriers()
{

}
