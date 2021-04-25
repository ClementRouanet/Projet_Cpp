#include <iostream>
#include <random>

#include "catastrophe.hpp"
#include "centrale.hpp"

using namespace std;


void catastrophe1(Centrale& centrale)
{
  auto RND = ((float)(rand()))/((float)(RAND_MAX))*0.15;
  centrale.majEtatCircuitPrim(0.3 + RND);

  RND = ((float)(rand()))/((float)(RAND_MAX))*0.15;
  centrale.majEtatPressuriseur(0.65 + RND);

  RND = ((float)(rand()))/((float)(RAND_MAX))*0.03;
  centrale.majEtatPompePrim(centrale.etatCircuitPrim() + RND);

  RND = ((float)(rand()))/((float)(RAND_MAX))*0.15;
  centrale.majEtatEchangeurChaleur(centrale.etatEchangeurChaleur() - (0.1 + RND));

  centrale.majEtatPiscine(centrale.etatPiscine() - 18);

  RND = ((float)(rand()))/((float)(RAND_MAX))*0.1;
  centrale.majEtatCuve(centrale.etatCuve() - (0.03 + RND));

  RND = ((float)(rand()))/((float)(RAND_MAX))*0.25;
  centrale.majEtatInjBore(centrale.etatInjBore() - (0.5 + RND));

  centrale.majEtatBarresGr(centrale.etatBarresGr()/1.5);

  centrale.majEtatResistancePressuriseur(centrale.etatPressuriseur());
}

void catastrophe2(Centrale& centrale)
{
  auto RND = ((float)(rand()))/((float)(RAND_MAX))*0.15;
  centrale.majEtatPiscine(0.5 - RND);

  RND = ((float)(rand()))/((float)(RAND_MAX))*0.07;
  centrale.majEtatCuve(0.55 - RND);

  RND = ((float)(rand()))/((float)(RAND_MAX))*0.02;
  centrale.majEtatBarresGr(centrale.etatBarresGr() - (0.2 + RND));

  centrale.majEtatCanaux(centrale.etatCanaux()/1.5);

  RND = ((float)(rand()))/((float)(RAND_MAX))*0.13;
  centrale.majEtatCircuitPrim(centrale.etatCircuitPrim() - (0.1 + RND));

  centrale.majEtatPressuriseur(centrale.etatPressuriseur() - 3);

  centrale.majEtatResistancePressuriseur(centrale.etatResistancePressuriseur() - 4);

  RND = ((float)(rand()))/((float)(RAND_MAX))*0.1;
  centrale.majEtatGenerateurVapeur(centrale.etatGenerateurVapeur() - (0.03 + RND));

  RND = ((float)(rand()))/((float)(RAND_MAX))*0.1;
  centrale.majEtatInjBore(centrale.etatInjBore() - (0.08 + RND));
}

void catastrophe3(Centrale& centrale)
{
  auto RND = ((float)(rand()))/((float)(RAND_MAX))*0.1;
  centrale.majEtatGenerateurVapeur(0.4 + RND);

  RND = ((float)(rand()))/((float)(RAND_MAX))*0.03;
  centrale.majEtatEchangeurChaleur(0.5 + RND);

  RND = ((float)(rand()))/((float)(RAND_MAX))*0.03;
  centrale.majEtatEnceinte(centrale.etatEnceinte() - RND);

  RND = ((float)(rand()))/((float)(RAND_MAX))*0.03;
  centrale.majEtatCircuitSec(centrale.etatCircuitSec() - (0.25 + RND));

  centrale.majEtatCondenseur(centrale.etatCondenseur() - 0.03);

  RND = ((float)(rand()))/((float)(RAND_MAX))*0.03;
  centrale.majEtatPompePrim(centrale.etatPompePrim() - (0.04 + RND));

  RND = ((float)(rand()))/((float)(RAND_MAX));
  centrale.majEtatInjBore(centrale.etatInjBore()*RND);

  RND = ((float)(rand()))/((float)(RAND_MAX))*0.1;
  centrale.majEtatBarresGr(centrale.etatBarresGr() - (0.2 + RND));
}

void catastrophe4(Centrale& centrale)
{
  centrale.majEtatEnceinte(centrale.etatEnceinte()/2.5);

  centrale.majEtatPiscine(centrale.etatPiscine()/1.5);

  centrale.majEtatCuve(centrale.etatCuve() - 0.2);

  auto RND = ((float)(rand()))/((float)(RAND_MAX))*0.03;
  centrale.majEtatGenerateurVapeur(centrale.etatGenerateurVapeur() - (0.14 + RND));

  RND = ((float)(rand()))/((float)(RAND_MAX))*0.12;
  centrale.majEtatEchangeurChaleur(centrale.etatEchangeurChaleur() - (0.3 + RND));

  RND = ((float)(rand()))/((float)(RAND_MAX))*0.15;
  centrale.majEtatCircuitPrim(centrale.etatCircuitPrim() - (0.2 + RND));

  centrale.majEtatBarresGr(centrale.etatBarresGr()/1.2);

  RND = ((float)(rand()))/((float)(RAND_MAX));
  centrale.majEtatPompePrim(centrale.etatPompePrim()*RND);

  centrale.majEtatPompeSec(centrale.etatPompeSec()/1.3);

  RND = ((float)(rand()))/((float)(RAND_MAX))*0.1;
  centrale.majEtatCircuitSec(centrale.etatCircuitSec() - (0.08 + RND));

  RND = ((float)(rand()))/((float)(RAND_MAX))*0.14;
  centrale.majEtatCondenseur(centrale.etatCondenseur()/2 - RND);

  RND = ((float)(rand()))/((float)(RAND_MAX))*0.1;
  centrale.majEtatInjBore(centrale.etatInjBore()/1.4 - RND);
}

void catastrophe5(Centrale& centrale)
{
  centrale.majEtatEnceinte(centrale.etatEnceinte()/2.6);

  centrale.majEtatCondenseur(centrale.etatCondenseur()/2.6);

  auto RND = ((float)(rand()))/((float)(RAND_MAX))*0.3;
  centrale.majEtatPiscine(centrale.etatPiscine() - (0.3 + RND));

  RND = ((float)(rand()))/((float)(RAND_MAX))*0.3;
  centrale.majEtatCuve(0.2 + RND);

  RND = ((float)(rand()))/((float)(RAND_MAX))*0.1;
  centrale.majEtatEchangeurChaleur(10 + RND);

  centrale.majEtatPompePrim(centrale.etatPompePrim()/1.6);

  RND = ((float)(rand()))/((float)(RAND_MAX))*0.8;
  centrale.majEtatCircuitPrim(centrale.etatCircuitPrim() - (0.2 + RND));

  RND = ((float)(rand()))/((float)(RAND_MAX));
  if (RND<0.5){
    centrale.majEtatCircuitSec(centrale.etatCircuitSec()/1.4);
    centrale.majEtatPompeSec(centrale.etatPompeSec()/2);
  }

  RND = ((float)(rand()))/((float)(RAND_MAX));
  if (RND<=0.7){
    centrale.majEtatCircuitPrim(centrale.etatCircuitPrim()/1.4);
  }

  RND = ((float)(rand()))/((float)(RAND_MAX));
  if (RND<=0.4){
    centrale.majEtatInjBore(centrale.etatInjBore()/3.2);
  }

  RND = ((float)(rand()))/((float)(RAND_MAX));
  if (RND<=0.5){
    centrale.majEtatCanaux(centrale.etatCanaux()/1.5);
    centrale.majEtatBarresGr(centrale.etatBarresGr()/1.5);
  }
}

void catastrophe(Centrale& centrale)
{
  if (centrale.productionCentrale()<900){
    auto RND = ((float)(rand()))/((float)(RAND_MAX));
    if (RND<=0.2){
      RND = ((float)(rand()))/((float)(RAND_MAX));
      if (RND<=0.2)
        catastrophe1(centrale);

      if (0.2<RND && RND<=0.4)
        catastrophe2(centrale);

      if (0.4<RND && RND<=0.6)
        catastrophe3(centrale);

      if (0.6<RND && RND<=0.8)
        catastrophe4(centrale);

      if (0.8<RND && RND<=1)
        catastrophe5(centrale);
    }
  }
}
