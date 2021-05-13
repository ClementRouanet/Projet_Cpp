#include <iostream>
#include <string>
#include <chrono>
#include <random>
#include <functional>
#include <vector>

#include "securite.hpp"


using namespace std;


Securite::Securite():m_nbMessages(0), m_fenetreActuelle(0)
{
}


vector<string> Securite::messages(Centrale& centrale)
{
  m_nbMessages = 0;
  vector<string> messages;

  //m_nbMessages = 10;
  // messages.push_back("Température trop élevée dans le circuit primaire\n");
  // messages.push_back("Température trop élevée dans le circuit\n");
  // messages.push_back("Température trop élevée dans le\n");
  // messages.push_back("Température trop élevée dans ahhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhh\n");
  // messages.push_back("Température trop élevée ahhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhh\n");
  // messages.push_back("Température trop ahhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhh\n");
  // messages.push_back("Températ\n");
  // messages.push_back("Temp\n");
  // messages.push_back("Temp\n");
  // messages.push_back("Temp\n");


  if(400 < centrale.temperatureEau() && centrale.temperatureEau() < 420){
    messages.push_back("Température trop élevée dans le circuit primaire");
    m_nbMessages += 1;
  }
  if(centrale.temperatureEau() >= 420){
    messages.push_back("Risque important de dégradation du circuit primaire dû à la température dans le circuit primaire");
    m_nbMessages += 1;
    auto RND = ((float)(rand()))/((float)(RAND_MAX))*0.02;
    centrale.majEtatCircuitPrim(centrale.etatCircuitPrim() - RND);
    messages.push_back("Risque de dégradation du pressuriseur dû à la température dans le circuit primaire");
    m_nbMessages += 1;
    RND = ((float)(rand()))/((float)(RAND_MAX));
    if(RND<=0.3)
    {
      RND = ((float)(rand()))/((float)(RAND_MAX))*0.02;
      centrale.majEtatPressuriseur(centrale.etatPressuriseur() - RND);
      RND = ((float)(rand()))/((float)(RAND_MAX))*0.02;
      centrale.majEtatResistancePressuriseur(centrale.etatResistancePressuriseur() - RND);
    }
  }
  if(centrale.temperatureEau() >= 420 && centrale.etatBarresGr() > 0.2){
    messages.push_back("Risque de dégradation des barres de graphite dû à la température dans le circuit primaire");
    m_nbMessages += 1;
    auto RND = ((float)(rand()))/((float)(RAND_MAX))*0.03;
    centrale.majEtatBarresGr(centrale.etatBarresGr() - RND);
  }
  if(centrale.temperatureEau() >= 40*centrale.pressionPrim()){
    messages.push_back("Risque important de dégradation du circuit primaire dû à la formation de vapeur dans le circuit primaire");
    m_nbMessages += 1;
    auto RND = ((float)(rand()))/((float)(RAND_MAX))*0.03;
    centrale.majEtatCircuitPrim(centrale.etatCircuitPrim() - RND);
    messages.push_back("Risque important de dégradation du pressuriseur dû à la formation de vapeur dans le circuit primaire");
    m_nbMessages += 1;
    RND = ((float)(rand()))/((float)(RAND_MAX))*0.02;
    centrale.majEtatPressuriseur(centrale.etatPressuriseur() - RND);
    messages.push_back("Risque de dégradation du pressuriseur dû à la formation de vapeur dans le circuit primaire");
    m_nbMessages += 1;
    RND = ((float)(rand()))/((float)(RAND_MAX));
    if(RND<=0.3)
    {
      RND = ((float)(rand()))/((float)(RAND_MAX))*0.02;
      centrale.majEtatResistancePressuriseur(centrale.etatResistancePressuriseur() - RND);
    }
  }
  if(centrale.temperatureEau() >= 50 && centrale.etatCircuitPrim() < 0.5){
    messages.push_back("Risque important de dégradation de l’échangeur de chaleur");
    m_nbMessages += 1;
    auto RND = ((float)(rand()))/((float)(RAND_MAX));
    if(RND<=0.4)
    {
      auto RND = ((float)(rand()))/((float)(RAND_MAX))*0.04;
      centrale.majEtatEchangeurChaleur(centrale.etatEchangeurChaleur() - RND);
    }
    messages.push_back("Risque de dégradation du générateur de vapeur");
    m_nbMessages += 1;
    if(RND<=0.2)
    {
      RND = ((float)(rand()))/((float)(RAND_MAX))*0.02;
      centrale.majEtatGenerateurVapeur(centrale.etatGenerateurVapeur() - RND);
    }
  }
  if(centrale.temperatureEau() >= 50 && centrale.etatCircuitPrim() < 0.58){
    messages.push_back("Risque important de dégradation de la pompe du circuit primaire");
    m_nbMessages += 1;
    auto RND = ((float)(rand()))/((float)(RAND_MAX));
    if(RND<=0.5)
    {
      RND = ((float)(rand()))/((float)(RAND_MAX))*0.03;
      centrale.majEtatPompePrim(centrale.etatPompePrim() - RND);
    }
  }
  if(centrale.temperatureEau() >= 50 && centrale.etatPressuriseur() < 0.5){
    messages.push_back("Risque très important de dégradation de la résistance du pressuriseur");
    m_nbMessages += 1;
    auto RND = ((float)(rand()))/((float)(RAND_MAX));
    if(RND<=0.8)
    {
      RND = ((float)(rand()))/((float)(RAND_MAX))*0.03;
      centrale.majEtatResistancePressuriseur(centrale.etatResistancePressuriseur() - RND);
    }
  }
  if(centrale.temperatureEau() >= 50 && centrale.etatCircuitPrim() < 0.6){
    messages.push_back("Risque de forte dégradation de la cuve");
    m_nbMessages += 1;
    auto RND = ((float)(rand()))/((float)(RAND_MAX));
    if(RND<=0.4)
    {
      RND = ((float)(rand()))/((float)(RAND_MAX))*0.02;
      centrale.majEtatCuve(centrale.etatCuve() - RND);
    }
  }
  if(centrale.temperatureEau() >= 50 && centrale.etatCircuitPrim() < 0.3){
    messages.push_back("Risque de forte dégradation de la cuve");
    m_nbMessages += 1;
    auto RND = ((float)(rand()))/((float)(RAND_MAX));
    if(RND<=0.3)
    {
      RND = ((float)(rand()))/((float)(RAND_MAX))*0.03;
      centrale.majEtatCuve(centrale.etatCuve() - RND);
    }
  }
  if(centrale.temperatureEau() >= 50 && centrale.etatCircuitPrim() < 0.2){
    messages.push_back("Risque de dégradation de la cuve");
    m_nbMessages += 1;
    auto RND = ((float)(rand()))/((float)(RAND_MAX));
    if(RND<=0.8)
    {
      RND = ((float)(rand()))/((float)(RAND_MAX))*0.06;
      centrale.majEtatCuve(centrale.etatCuve() - RND);
    }
    messages.push_back("Risque très important de dégradation de la piscine");
    m_nbMessages += 1;
    RND = ((float)(rand()))/((float)(RAND_MAX));
    if(RND<=0.8)
    {
      RND = ((float)(rand()))/((float)(RAND_MAX))*0.06;
      centrale.majEtatPiscine(centrale.etatPiscine() - RND);
    }
  }
  if(centrale.temperatureEau() >= 50 && centrale.pressionPrim() > 10){
    messages.push_back("Risque faible de dégradation du circuit primaire dû à une pression trop forte");
    m_nbMessages += 1;
    auto RND = ((float)(rand()))/((float)(RAND_MAX));
    if(RND<=0.2)
    {
      RND = ((float)(rand()))/((float)(RAND_MAX))*0.02;
      centrale.majEtatCircuitPrim(centrale.etatCircuitPrim() - RND);
    }
  }
  if(centrale.temperatureEau() >= 50 && centrale.etatCuve() < 0.7 && centrale.propGrDemande() > 0.4){
    messages.push_back("Risque important de dégradation des barres de graphite");
    m_nbMessages += 1;
    auto RND = ((float)(rand()))/((float)(RAND_MAX));
    if(RND<=0.4)
    {
      RND = ((float)(rand()))/((float)(RAND_MAX))*0.03;
      centrale.majEtatBarresGr(centrale.etatBarresGr() - RND);
    }
  }
  if(centrale.temperatureEau() >= 50 && centrale.etatCuve() < 0.5){
    messages.push_back("Risque important de dégradation importante des canaux");
    m_nbMessages += 1;
    auto RND = ((float)(rand()))/((float)(RAND_MAX));
    if(RND<=0.5)
    {
      RND = ((float)(rand()))/((float)(RAND_MAX))*0.05;
      centrale.majEtatCanaux(centrale.etatCanaux() - RND);
    }
  }
  if(centrale.temperatureEau() >= 50 && centrale.etatEchangeurChaleur() < 0.6){
    messages.push_back("Risque faible de dégradation faible du circuit primaire");
    m_nbMessages += 1;
    auto RND = ((float)(rand()))/((float)(RAND_MAX));
    if(RND<=0.3)
    {
      RND = ((float)(rand()))/((float)(RAND_MAX))*0.015;
      centrale.majEtatCircuitPrim(centrale.etatCircuitPrim() - RND);
    }
  }
  if(centrale.temperatureEau() >= 50 && centrale.etatEchangeurChaleur() < 0.6 && centrale.pressionPrim() > 3){
    messages.push_back("Risque important  de dégradation du générateur de vapeur");
    m_nbMessages += 1;
    auto RND = ((float)(rand()))/((float)(RAND_MAX));
    if(RND<=0.5)
    {
      RND = ((float)(rand()))/((float)(RAND_MAX))*0.02;
      centrale.majEtatGenerateurVapeur(centrale.etatGenerateurVapeur() - RND);
    }
  }
  if(centrale.temperatureEau() >= 50 && centrale.etatCanaux() < 0.6 && centrale.propGrDemande() > 0.4){
    messages.push_back("Risque de dégradation des barres de graphite");
    m_nbMessages += 1;
    auto RND = ((float)(rand()))/((float)(RAND_MAX));
    if(RND<=0.3)
    {
      RND = ((float)(rand()))/((float)(RAND_MAX))*0.02;
      centrale.majEtatBarresGr(centrale.etatBarresGr() - RND);
    }
  }
  if(centrale.temperatureEau() >= 50 && centrale.etatCuve() < 0.5 && centrale.etatCircuitPrim() < 0.5){
    messages.push_back("Risque important de dégradation de l’injecteur d’acide borique");
    m_nbMessages += 1;
    auto RND = ((float)(rand()))/((float)(RAND_MAX));
    if(RND<=0.5)
    {
      RND = ((float)(rand()))/((float)(RAND_MAX))*0.02;
      centrale.majEtatInjBore(centrale.etatInjBore() - RND);
    }
  }
  if(centrale.etatEchangeurChaleur() < 0.7){
    messages.push_back("Problème d’échange entre le circuit primaire et le circuit secondaire");
    m_nbMessages += 1;
  }
  if(centrale.etatEchangeurChaleur() < 0.4){
    messages.push_back("Risque important de dégradation de l’injecteur d’acide borique");
    m_nbMessages += 1;
    auto RND = ((float)(rand()))/((float)(RAND_MAX));
    if(RND<=0.25)
    {
      RND = ((float)(rand()))/((float)(RAND_MAX))*0.03;
      centrale.majEtatEchangeurChaleur(centrale.etatEchangeurChaleur() - RND);
    }
  }
  if(centrale.temperatureVapeur() >= 310){
    messages.push_back("Risque important de dégradation du circuit secondaire dû à la température de la vapeur");
    m_nbMessages += 1;
    auto RND = ((float)(rand()))/((float)(RAND_MAX));
    if(RND<=0.25)
    {
      RND = ((float)(rand()))/((float)(RAND_MAX))*0.04;
      centrale.majEtatCircuitSec(centrale.etatCircuitSec() - RND);
    }
  }
  if(centrale.diffChaleurCondenseur() < 11 && centrale.temperatureVapeur() >= 130){
    messages.push_back("Risque possible de dégradation du circuit secondaire dû au refroidissement");
    m_nbMessages += 1;
  }
  if(centrale.etatCircuitSec() < 0.5 && centrale.temperatureVapeur() > 130){
    messages.push_back("Risque important de dégradation du circuit secondaire");
    m_nbMessages += 1;
    auto RND = ((float)(rand()))/((float)(RAND_MAX));
    if(RND<=0.3)
    {
      RND = ((float)(rand()))/((float)(RAND_MAX))*0.015;
      centrale.majEtatCircuitSec(centrale.etatCircuitSec() - RND);
    }
  }
  if(centrale.etatCircuitSec() < 0.6){
    messages.push_back("Risque important de dégradation de la pompe du circuit secondaire");
    m_nbMessages += 1;
    auto RND = ((float)(rand()))/((float)(RAND_MAX));
    if(RND<=0.3)
    {
      RND = ((float)(rand()))/((float)(RAND_MAX))*0.02;
      centrale.majEtatPompeSec(centrale.etatPompeSec() - RND);
    }
  }
  if(centrale.etatCircuitSec() < 0.4){
    messages.push_back("Risque important de dégradation de la pompe du circuit secondaire");
    m_nbMessages += 1;
    auto RND = ((float)(rand()))/((float)(RAND_MAX));
    if(RND<=0.4)
    {
      RND = ((float)(rand()))/((float)(RAND_MAX))*0.02;
      centrale.majEtatGenerateurVapeur(centrale.etatGenerateurVapeur() - RND);
    }
  }
  if(centrale.diffChaleurCondenseur() > 19){
    messages.push_back("Dégradation potentielle du condenseur à cause de la différence de température");
    m_nbMessages += 1;
    auto RND = ((float)(rand()))/((float)(RAND_MAX));
    if(RND<=0.4)
    {
      RND = ((float)(rand()))/((float)(RAND_MAX))*0.03;
      centrale.majEtatCondenseur(centrale.etatCondenseur() - RND);
    }
  }
  if(2 < centrale.pressionEnceinte() && centrale.pressionEnceinte() < 3.4){
    messages.push_back("Dégradation potentielle de l’enceinte de confinement dû à la pression");
    m_nbMessages += 1;
  }
  if(2 < centrale.pressionEnceinte() && centrale.pressionEnceinte() < 3.4 && centrale.etatEnceinte() > 0.5){
    messages.push_back("Dégradation potentielle de l’enceinte de confinement dû à la pression");
    m_nbMessages += 1;
    auto RND = ((float)(rand()))/((float)(RAND_MAX));
    if(RND<=0.3)
    {
      RND = ((float)(rand()))/((float)(RAND_MAX))*0.02;
      centrale.majEtatEnceinte(centrale.etatEnceinte() - RND);
    }
  }
  if(3.4 < centrale.pressionEnceinte() && centrale.pressionEnceinte() < 4.5){
    messages.push_back("Risque important de dégradation de l’enceinte de confinement dû à la pression");
    m_nbMessages += 1;
  }
  if(3.4 < centrale.pressionEnceinte() && centrale.pressionEnceinte() < 4.5 && centrale.etatEnceinte() > 0.25){
    messages.push_back("Risque important de dégradation de l’enceinte de confinement dû à la pression");
    m_nbMessages += 1;
    auto RND = ((float)(rand()))/((float)(RAND_MAX));
    if(RND<=0.6)
    {
      RND = ((float)(rand()))/((float)(RAND_MAX))*0.06;
      centrale.majEtatEnceinte(centrale.etatEnceinte() - RND);
    }
  }
  if(centrale.etatEnceinte() == 0 || centrale.pressionEnceinte() >= 4.5){
    messages.push_back("Destruction totale de l’enceinte de confinement");
    m_nbMessages += 1;
    auto RND = ((float)(rand()))/((float)(RAND_MAX))*0.1;
    centrale.majEtatGenerateurVapeur(centrale.etatGenerateurVapeur() - (0.1 + RND));
    if(centrale.etatGenerateurVapeur() < 0.4){
      messages.push_back("Détérioration importante du générateur de vapeur dûe à la destruction totale de l’enceinte de confinement");
      m_nbMessages += 1;
    }
    messages.push_back("Détérioration potentielle importante du circuit primaire et du pressuriseur dûe à la destruction totale de l’enceinte de confinement");
    m_nbMessages += 1;
    RND = ((float)(rand()))/((float)(RAND_MAX));
    if(RND<=0.8)
    {
      RND = ((float)(rand()))/((float)(RAND_MAX))*0.1;
      centrale.majEtatCircuitPrim(centrale.etatCircuitPrim() - (0.1 + RND));
      centrale.majEtatPressuriseur(centrale.etatPressuriseur() - 0.1);
      if(centrale.etatPressuriseur() < 0.9){
        RND = ((float)(rand()))/((float)(RAND_MAX));
        if(RND<=0.8)
        {
          RND = ((float)(rand()))/((float)(RAND_MAX))*0.1;
          centrale.majEtatResistancePressuriseur(centrale.etatResistancePressuriseur() - RND);
        }
      }
    }
    messages.push_back("Détérioration potentielle importante de la cuve et de la piscine due à la destruction toale de l’enceinte de confinement");
    m_nbMessages += 1;
    RND = ((float)(rand()))/((float)(RAND_MAX))*0.16;
    if(RND<=0.65)
    {
      RND = ((float)(rand()))/((float)(RAND_MAX))*0.16;
      centrale.majEtatPiscine(centrale.etatPiscine() - (0.6 + RND));
      RND = ((float)(rand()))/((float)(RAND_MAX))*0.1;
      centrale.majEtatCuve(centrale.etatCuve() - (0.5 + RND));
    }
  }
  return messages;
}

void Securite::affichageSecurite(sdl2::window& fenetre, Centrale& centrale)
{
  auto [wph, hph] = fenetre.dimensions();
  sdl2::font fonte_texte1("./data/Welbut__.ttf", 20);

  vector<string> alertes = messages(centrale);

  if(m_nbMessages==0)
  {
    sdl2::texte texteInitial("Il n'y a pas d'alerte de dégradation, tout va bien", fonte_texte1, fenetre, 0.35*wph, 0.08*hph,{0x00,0x00,0x00,0x00}, {0xE0,0xD2,0xA3,0x00});
    texteInitial.at(0.33*wph,0.5*hph);

    fenetre << texteInitial;
    affichagePoints(fenetre);
  }
  else
  {
    int nbMessages_fin = m_nbMessages % 3;
    m_nbFenetres = m_nbMessages/3 + 1;

    sdl2::font fonte_texte2("./data/Welbut__.ttf",16);

    if(m_fenetreActuelle != 0 && m_fenetreActuelle != m_nbFenetres - 1)
    {
      sdl2::texte texte1(alertes[m_fenetreActuelle*3], fonte_texte2, fenetre, 0.35*wph, 0.08*hph, {0x00,0x00,0x00,0x00}, {0xE0,0xD2,0xA3,0x00});
      sdl2::texte texte2(alertes[m_fenetreActuelle*3 + 1], fonte_texte2, fenetre, 0.35*wph, 0.08*hph, {0x00,0x00,0x00,0x00}, {0xE0,0xD2,0xA3,0x00});
      sdl2::texte texte3(alertes[m_fenetreActuelle*3 + 2], fonte_texte2, fenetre, 0.35*wph, 0.08*hph, {0x00,0x00,0x00,0x00}, {0xE0,0xD2,0xA3,0x00});

      texte1.at(0.33*wph,0.5*hph);
      texte2.at(0.33*wph,0.58*hph);
      texte3.at(0.33*wph,0.66*hph);

      fenetre << texte1 << texte2 << texte3;
      affichagePoints(fenetre);
    }

    if(m_fenetreActuelle == 0)
    {
      if(m_nbMessages < 3)
      {
        if(nbMessages_fin == 1)
        {
          sdl2::texte texte1(alertes[0], fonte_texte2, fenetre, 0.35*wph, 0.08*hph, {0x00,0x00,0x00,0x00}, {0xE0,0xD2,0xA3,0x00});

          texte1.at(0.33*wph,0.5*hph);

          fenetre << texte1;
          affichagePoints(fenetre);
        }
        if(nbMessages_fin == 2)
        {
          sdl2::texte texte1(alertes[0], fonte_texte2, fenetre, 0.35*wph, 0.08*hph, {0x00,0x00,0x00,0x00}, {0xE0,0xD2,0xA3,0x00});
          sdl2::texte texte2(alertes[1], fonte_texte2, fenetre, 0.35*wph, 0.08*hph, {0x00,0x00,0x00,0x00}, {0xE0,0xD2,0xA3,0x00});

          texte1.at(0.33*wph,0.5*hph);
          texte2.at(0.33*wph,0.58*hph);

          fenetre << texte1 << texte2;
          affichagePoints(fenetre);
        }
      }
      else
      {
        sdl2::texte texte1(alertes[0], fonte_texte2, fenetre, 0.35*wph, 0.08*hph, {0x00,0x00,0x00,0x00}, {0xE0,0xD2,0xA3,0x00});
        sdl2::texte texte2(alertes[1], fonte_texte2, fenetre, 0.35*wph, 0.08*hph, {0x00,0x00,0x00,0x00}, {0xE0,0xD2,0xA3,0x00});
        sdl2::texte texte3(alertes[2], fonte_texte2, fenetre, 0.35*wph, 0.08*hph, {0x00,0x00,0x00,0x00}, {0xE0,0xD2,0xA3,0x00});

        texte1.at(0.33*wph,0.5*hph);
        texte2.at(0.33*wph,0.58*hph);
        texte3.at(0.33*wph,0.66*hph);

        fenetre << texte1 << texte2 << texte3;
        affichagePoints(fenetre);
      }
    }

    if(m_fenetreActuelle == m_nbFenetres - 1)
    {
      if(nbMessages_fin == 1)
      {
        sdl2::texte texte1(alertes[m_nbMessages - 1], fonte_texte2, fenetre, 0.35*wph, 0.08*hph, {0x00,0x00,0x00,0x00}, {0xE0,0xD2,0xA3,0x00});

        texte1.at(0.33*wph,0.5*hph);

        fenetre << texte1;
        affichagePoints(fenetre);
      }
      if(nbMessages_fin == 2)
      {
        sdl2::texte texte1(alertes[m_nbMessages - 2], fonte_texte2, fenetre, 0.35*wph, 0.08*hph, {0x00,0x00,0x00,0x00}, {0xE0,0xD2,0xA3,0x00});
        sdl2::texte texte2(alertes[m_nbMessages - 1], fonte_texte2, fenetre, 0.35*wph, 0.08*hph, {0x00,0x00,0x00,0x00}, {0xE0,0xD2,0xA3,0x00});

        texte1.at(0.33*wph,0.5*hph);
        texte2.at(0.33*wph,0.58*hph);

        fenetre << texte1 << texte2;
        affichagePoints(fenetre);
      }
      if(nbMessages_fin == 0)
      {
        sdl2::texte texte1(alertes[m_nbMessages - 3], fonte_texte2, fenetre, 0.35*wph, 0.08*hph, {0x00,0x00,0x00,0x00}, {0xE0,0xD2,0xA3,0x00});
        sdl2::texte texte2(alertes[m_nbMessages - 2], fonte_texte2, fenetre, 0.35*wph, 0.08*hph, {0x00,0x00,0x00,0x00}, {0xE0,0xD2,0xA3,0x00});
        sdl2::texte texte3(alertes[m_nbMessages - 1], fonte_texte2, fenetre, 0.35*wph, 0.08*hph, {0x00,0x00,0x00,0x00}, {0xE0,0xD2,0xA3,0x00});

        texte1.at(0.33*wph,0.5*hph);
        texte2.at(0.33*wph,0.58*hph);
        texte3.at(0.33*wph,0.66*hph);

        fenetre << texte1 << texte2 << texte3;
        affichagePoints(fenetre);
      }
    }
  }
}


void Securite::majSecuriteDroite()
{
  if(m_fenetreActuelle == m_nbFenetres - 1)
    m_fenetreActuelle = 0;
  else
    m_fenetreActuelle += 1;
}

void Securite::majSecuriteGauche()
{
  if(m_fenetreActuelle == 0)
    m_fenetreActuelle = m_nbFenetres - 1;
  else
    m_fenetreActuelle -= 1;
}

void Securite::affichagePoints(sdl2::window& fenetre)
{
  if(m_nbMessages > 3)
  {
    auto [wph, hph] = fenetre.dimensions();

    sdl2::font fonte_texte("./data/Welbut__.ttf", 50);

    for(int i=0; i < m_nbFenetres; i++)
    {
      if(i == m_fenetreActuelle)
      {
        sdl2::texte point(".", fonte_texte, fenetre, {0xFF,0x00,0x00,0x00});
        point.at(((0.51 - (m_nbFenetres*0.03)/2) + i*(0.03))*wph, 0.7*hph);

        fenetre << point;
      }
      else
      {
        sdl2::texte point(".", fonte_texte, fenetre, {0x00,0x00,0x00,0x00});
        point.at(((0.51 - (m_nbFenetres*0.03)/2) + i*(0.03))*wph, 0.7*hph);

        fenetre << point;
      }
    }
  }
}


Securite::~Securite()
{
}
