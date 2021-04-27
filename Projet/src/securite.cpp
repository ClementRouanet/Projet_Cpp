#include <iostream>
#include <string>
#include <chrono>
#include <random>
#include <functional>
#include <vector>

#include "securite.hpp"
#include "centrale.hpp"
#include "sdl2.hpp"

using namespace std;


Securite::Securite():m_nbMessages(0), m_messageActuel(0)
{
}


vector<string> Securite::messages(Centrale& centrale)
{
  vector<string> messages;

  messages.push_back("Température trop élevée dans le circuit primaire");
  m_nbMessages += 1;

  messages.push_back("Risque important de dégradation du circuit primaire dû à la température dans le circuit primaire");
  m_nbMessages += 1;

  messages.push_back("Risque de dégradation du pressuriseur dû à la température dans le circuit primaire");
  m_nbMessages += 1;

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
  sdl2::font fonte_texte1("./data/Lato-Bold.ttf", 30);

  vector<string> alertes = messages(centrale);

  if(m_nbMessages==0)
  {
    sdl2::texte texteInitial("Il n'y a pas d'alerte de dégradation, tout va bien", fonte_texte1, fenetre, {0x00,0x00,0x00,0x00});
    texteInitial.at(0.25*wph,0.5*hph);

    fenetre << texteInitial;
  }
  else
  {
    sdl2::font fonte_texte2("./data/Lato-Bold.ttf", 20);
    sdl2::texte texteAlerte(alertes[m_messageActuel], fonte_texte2, fenetre, {0x00,0x00,0x00,0x00});
    texteAlerte.at(0.3*wph,0.5*hph);

    fenetre << texteAlerte;
  }
}

void Securite::majSecurite(sdl2::window& fenetre, Centrale& centrale)
{
  bool iskey_down = false;
  sdl2::event_queue queue;

  auto events = queue.pull_events();
  for (const auto& e : events)
  {
    if ((e->kind_of_event() == sdl2::event::key_down) || (e->kind_of_event() == sdl2::event::key_up))
    {
      auto& key_ev = dynamic_cast<sdl2::event_keyboard&>(*e);

      if ((e->kind_of_event() == sdl2::event::key_down) &&  (iskey_down == false))
      {
        if (key_ev.code() == sdl2::event_keyboard::right)
        {
          if(m_messageActuel == m_nbMessages-1)
            m_messageActuel = 0;
          else
            m_messageActuel += 1;
        }
        if (key_ev.code() == sdl2::event_keyboard::left)
        {
          if(m_messageActuel == 0)
            m_messageActuel = m_nbMessages-1;
          else
            m_messageActuel -= 1;
        }
        /*switch (key_ev.code())
        {
          case sdl2::event_keyboard::right :
          if(m_messageActuel == m_nbMessages-1)
            m_messageActuel = 0;
          else
            m_messageActuel += 1;
          break;

          case sdl2::event_keyboard::left :
          if(m_messageActuel == 0)
            m_messageActuel = m_nbMessages-1;
          else
            m_messageActuel -= 1;
          break;
        }*/
      }
      if (key_ev.type_of_event() == sdl2::event::key_up)
      iskey_down = false;
    }
  }

}


Securite::~Securite()
{
}
