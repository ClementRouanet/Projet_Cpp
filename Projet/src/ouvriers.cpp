#include <random>
#include <iostream>
#include <algorithm>

#include "ouvriers.hpp"

using namespace std;

Ouvriers::Ouvriers() : m_nombreOuvriersDispo(145)
{
   fill(m_etatSante.begin(),m_etatSante.end(),1);
   m_etatMission = {0};
   fill(m_lieuMission.begin(),m_lieuMission.end(),"reserve");
   fill(m_estDispo.begin(),m_estDispo.end(),1);
   m_etatReparation = {0};
}


array<int,145> Ouvriers::getEtatSante() const
{
  return m_etatSante;
}

array<int,145> Ouvriers::getEtatMission() const
{
  return m_etatMission;
}

array<string,145> Ouvriers::getLieuMission() const
{
  return m_lieuMission;
}

int Ouvriers::getNombreOuvriersDispo() const
{
  return m_nombreOuvriersDispo;
}

array<int,8> Ouvriers::getEtatReparation() const
{
  return m_etatReparation;
}

void Ouvriers::majEtatSante(Centrale& centrale)
{

  for(int i=0;i<145;i++)
  {
    auto RND = ((float)(rand()))/((float)(RAND_MAX))*100;
    if(m_lieuMission[i]=="circuit primaire" && centrale.etatCircuitPrim()<0.2)
    {
      m_etatSante[i] = 0; m_etatMission[i] = 1;
      remplacerOuvrierMalade("circuit primaire");
    }
    if(m_lieuMission[i]=="generateur de vapeur" && RND<=10)
    {
      m_etatSante[i] = 0; m_etatMission[i] = 1;
      remplacerOuvrierMalade("generateur de vapeur");
    }
    if(m_lieuMission[i]=="reacteur" && (centrale.radioactiviteEnceinte()>12 || centrale.pressionEnceinte()>3))
    {
      m_etatSante[i] = 0; m_etatMission[i] = 1;
      remplacerOuvrierMalade("reacteur");
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

  if(interventionPossible(centrale, lieu)!=0)
  {
    m_nombreOuvriersDispo = majNombreOuvriersDispo();
    if(lieu=="pompe primaire" && m_nombreOuvriersDispo>=8)
    {
      m_etatReparation[0] = 1;
      int compteur = 0;
      for(int i=0;i<145;i++)
      {
        if(m_estDispo[i]==1 && compteur<8)
        {
          m_etatMission[i] = 1; m_lieuMission[i] = lieu;
          compteur++;
        }
      }
      m_nombreOuvriersDispo = majNombreOuvriersDispo();
    }
    if(lieu=="pompe secondaire" && m_nombreOuvriersDispo>=8)
    {
      m_etatReparation[1] = 1;
      int compteur = 0;
      for(int i=0;i<145;i++)
      {
        if(m_estDispo[i]==1 && compteur<8)
        {
          m_etatMission[i] = 1; m_lieuMission[i] = lieu;
          compteur++;
        }
      }
      m_nombreOuvriersDispo = majNombreOuvriersDispo();
    }
    if(lieu=="condenseur" && m_nombreOuvriersDispo>=20)
    {
      m_etatReparation[2] = 1;
      int compteur = 0;
      for(int i=0;i<145;i++)
      {
        if(m_estDispo[i]==1 && compteur<20)
        {
          m_etatMission[i] = 1; m_lieuMission[i] = lieu;
          compteur++;
        }
      }
      m_nombreOuvriersDispo = majNombreOuvriersDispo();
    }
    if(lieu=="generateur de vapeur" && m_nombreOuvriersDispo>=60)
    {
      m_etatReparation[3] = 1;
      int compteur = 0;
      for(int i=0;i<145;i++)
      {
        if(m_estDispo[i]==1 && compteur<60)
        {
          m_etatMission[i] = 1; m_lieuMission[i] = lieu;
          compteur++;
        }
      }
      m_nombreOuvriersDispo = majNombreOuvriersDispo();
    }
    if(lieu=="injecteur Bore" && m_nombreOuvriersDispo>=5)
    {
      m_etatReparation[4] = 1;
      int compteur = 0;
      for(int i=0;i<145;i++)
      {
        if(m_estDispo[i]==1 && compteur<5)
        {
          m_etatMission[i] = 1; m_lieuMission[i] = lieu;
          compteur++;
        }
      }
      m_nombreOuvriersDispo = majNombreOuvriersDispo();
    }
    if(lieu=="circuit primaire" && m_nombreOuvriersDispo>=45)
    {
      m_etatReparation[5] = 1;
      int compteur = 0;
      for(int i=0;i<145;i++)
      {
        if(m_estDispo[i]==1 && compteur<45)
        {
          m_etatMission[i] = 1; m_lieuMission[i] = lieu;
          compteur++;
        }
      }
      m_nombreOuvriersDispo = majNombreOuvriersDispo();
    }
    if(lieu=="circuit secondaire" && m_nombreOuvriersDispo>=20)
    {
      m_etatReparation[6] = 1;
      int compteur = 0;
      for(int i=0;i<145;i++)
      {
        if(m_estDispo[i]==1 && compteur<20)
        {
          m_etatMission[i] = 1; m_lieuMission[i] = lieu;
          compteur++;
        }
      }
      m_nombreOuvriersDispo = majNombreOuvriersDispo();
    }
    if(lieu=="pressuriseur" && m_nombreOuvriersDispo>=10)
    {
      m_etatReparation[7] = 1;
      int compteur = 0;
      for(int i=0;i<145;i++)
      {
        if(m_estDispo[i]==1 && compteur<10)
        {
          m_etatMission[i] = 1; m_lieuMission[i] = lieu;
          compteur++;
        }
      }
      m_nombreOuvriersDispo = majNombreOuvriersDispo();
    }
  }
}

void Ouvriers::reparer(Centrale& centrale)
{

  if(m_etatReparation[0]==1)
    centrale.reparationPompePrim();
  if(m_etatReparation[1]==1)
    centrale.reparationPompeSec();
  if(m_etatReparation[2]==1)
    centrale.reparationCondenseur();
  if(m_etatReparation[3]==1)
    centrale.reparationGenerateurVapeur();
  if(m_etatReparation[4]==1)
    centrale.reparationInjecteurBore();
  if(m_etatReparation[5]==1)
    centrale.reparationCircuitPrim();
  if(m_etatReparation[6]==1)
    centrale.reparationCircuitSec();
  if(m_etatReparation[7]==1)
    centrale.reparationPressuriseur();

}

void Ouvriers::rappelerOuvriers(Centrale& centrale)
{

  for(int i=0;i<145;i++)
  {
    if(m_lieuMission[i]=="pompe primaire" && centrale.etatPompePrim()==1 && m_etatSante[i]==1)
    {
      m_estDispo[i] = 1; m_lieuMission[i] = "reserve";
    }
    if(m_lieuMission[i]=="pompe secondaire" && centrale.etatPompeSec()==1 && m_etatSante[i]==1)
    {
      m_estDispo[i] = 1; m_lieuMission[i] = "reserve";
    }
    if(m_lieuMission[i]=="condenseur" && centrale.etatCondenseur()==1 && m_etatSante[i]==1)
    {
      m_estDispo[i] = 1; m_lieuMission[i] = "reserve";
    }
    if(m_lieuMission[i]=="generateur de vapeur" && centrale.etatGenerateurVapeur()==1 && m_etatSante[i]==1)
    {
      m_estDispo[i] = 1; m_lieuMission[i] = "reserve";
    }
    if(m_lieuMission[i]=="injecteur Bore" && centrale.etatInjBore()==1 && m_etatSante[i]==1)
    {
      m_estDispo[i] = 1; m_lieuMission[i] = "reserve";
    }
    if(m_lieuMission[i]=="circuit primaire" && centrale.etatCircuitPrim()==1 && m_etatSante[i]==1)
    {
      m_estDispo[i] = 1; m_lieuMission[i] = "reserve";
    }
    if(m_lieuMission[i]=="circuit secondaire" && centrale.etatCircuitSec()==1 && m_etatSante[i]==1)
    {
      m_estDispo[i] = 1; m_lieuMission[i] = "reserve";
    }
    if(m_lieuMission[i]=="pressuriseur" && centrale.etatPressuriseur()==1 && m_etatSante[i]==1)
    {
      m_estDispo[i] = 1; m_lieuMission[i] = "reserve";
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
      n++;
  }

  return n;

}

int Ouvriers::nombreEnInterventionOrgane(string lieu)
{
  int n(0);
  for(int i=0;i<145;i++)
  {
    if(m_lieuMission[i]==lieu && m_etatMission[i]==1)
      n++;
  }
  return n;
}

int Ouvriers::interventionPossible(Centrale& centrale, string lieu)
{
  if(centrale.etatCircuitPrim()<0.2 && lieu=="circuit primaire")
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
      m_etatMission[i] = 0; m_lieuMission[i] = "reserve"; m_estDispo[i] = 1;
    }
  }
  majNombreOuvriersDispo();

  if(lieu=="pompe primaire")
    m_etatReparation[0] = 0;
  if(lieu=="pompe secondaire")
    m_etatReparation[1] = 0;
  if(lieu=="condenseur")
    m_etatReparation[2] = 0;
  if(lieu=="generateur de vapeur")
    m_etatReparation[3] = 0;
  if(lieu=="injecteur de Bore")
    m_etatReparation[4] = 0;
  if(lieu=="circuit primaire")
    m_etatReparation[5] = 0;
  if(lieu=="circuit secondaire")
    m_etatReparation[6] = 0;
  if(lieu=="pressuriseur")
    m_etatReparation[7] = 0;
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

bool Ouvriers::InterventionEnCours(string lieu)
{
  bool tmp = false;
  for(int i=0;i<145;i++)
  {
    if(m_lieuMission[i]==lieu && m_etatMission[i]==1)
      tmp = true;
  }
  return tmp;
}

void Ouvriers::remplacerOuvrierMalade(string lieu)
{
  majNombreOuvriersDispo();
  int n(0);
  for(int i=0;i<145;i++)
  {
    if(m_etatMission[i]==1 && m_lieuMission[i]==lieu && m_etatSante[i]==0)
    {
      n++;
      if(m_nombreOuvriersDispo>=n)
      {
        m_etatMission[i] = 1; m_lieuMission[i] = lieu;
        majNombreOuvriersDispo();
      }
      else
        annulerIntervention(lieu);
    }
  }
}

Ouvriers::~Ouvriers()
{
}
