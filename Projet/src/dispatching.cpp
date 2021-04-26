#include <iostream>
#include <string>
#include <chrono>
#include <random>
#include <functional>

#include "dispatching.hpp"
#include "centrale.hpp"
#include "sdl2.hpp"

using namespace std;


Dispatching::Dispatching():m_tourDebut(0), m_tourActuel(0), m_score(100), m_nbOrdre(0), m_produire(0), m_ordre(false), m_contreOrdre(false), m_objectif(false), m_tourObjectif(0)
{
}


int Dispatching::scoreDispatching()
{
  return m_score;
}


void Dispatching::ordreInitial(sdl2::window& fenetre) const
{
  auto [wph, hph] = fenetre.dimensions();

  sdl2::font fonte_texte("./data/Lato-Bold.ttf",20);
  sdl2::texte texte("Mettre la centrale en divergence : démarrer la réaction en chaîne (lever des barres, baisse du taux d'acide borique, fonctionnement des pompes, pressurisation, etc.) et la production de vapeur dans le générateur", fonte_texte, fenetre, {0x00,0x00,0x00,0x00});

  texte.at(0.02*wph,0.7*hph);

  fenetre << texte;
  m_nbOrdre += 1;
}

void Dispatching::ordre()
{
  int valMin;

  if(m_contreOrdre == true)
    valMin = 100;
  else
    valMin = 900;

  random_device hgenerateur;
  default_random_engine generateur(hgenerateur());
  uniform_real_distribution<double> genrand(0,1400-valMin);
  auto rnd = bind(genrand, generateur);

  int ordre = ceil(rnd());
  m_produire = ordre + (10-(ordre%10)) + valMin; // 900 - 1400 ou 100 - 1400
  m_ordre = true;
  m_contreOrdre = false;
  m_nbOrdre += 1;
}


void Dispatching::affichageDispatching(sdl2::window& fenetre, Centrale& centrale) const
{
  double temperatureVap = centrale.temperatureVapeur();

  auto [wph, hph] = fenetre.dimensions();
  sdl2::font fonte_texte("./data/Lato-Bold.ttf",15);

  if(temperatureVap<=140 && m_nbOrdre==0)
    ordreInitial(fenetre);
  else if(m_tourActuel<65 && m_ordre==true)
  {
    if(m_tourObjectif < 15)
    {
      string sProduire(to_string(m_produire));
      sProduire.erase(2,7);

      sdl2::texte texteProduire("Produire : " + sProduire + " MW", fonte_texte, fenetre, {0x00,0x00,0x00,0x00});
      texteProduire.at(0.02*wph,0.7*hph);

      fenetre << texteProduire;

      if(m_tourActuel>=50)
      {
        sdl2::texte texteAcceleration("Accélérer la procédure", fonte_texte, fenetre, {0xFF,0x00,0x00,0x00});
        texteAcceleration.at(0.02*wph,0.75*hph);
        fenetre << texteAcceleration;
      }
    }
    else
    {
      sdl2::texte texteSucces1("Félicitation vous avez accompli l'ordre", fonte_texte, fenetre, {0xFF,0x00,0x00,0x00});
      sdl2::texte texteSucces2("Attention vous allez recevoir un nouvel ordre", fonte_texte, fenetre, {0x00,0x00,0x00,0x00});

      texteSucces1.at(0.02*wph,0.7*hph);
      texteSucces2.at(0.02*wph,0.75*hph);

      fenetre << texteSucces1 << texteSucces2;
    }
  }
  else
  {
    sdl2::texte texteEchec("Vous avez échoué à la procédure !", fonte_texte, fenetre, {0xFF,0x00,0x00,0x00});
    texteEchec.at(0.02*wph,0.7*hph);
    fenetre << texteEchec;
  }
}


void Dispatching::majdispatching(sdl2::window& fenetre, Centrale& centrale, int tour)
{
  double temperatureVap = centrale.temperatureVapeur();

  if(m_ordre==false && m_nbOrdre>0)
  {
    ordre();
    m_tourDebut = tour;
  }
  else if(m_ordre==true && m_nbOrdre>0)
  {
    if((m_produire>=(m_produire-10) && m_produire<=(m_produire+10)) || m_objectif==true)
    {
      if(m_produire>=(m_produire-10) && m_produire<=(m_produire+10) && m_objectif==true)
        m_tourObjectif += 1;

      if(m_produire<(m_produire-10) && m_produire>(m_produire+10) && m_objectif==true)
      {
        m_objectif = false;
        m_tourObjectif = 0;
      }
      if(m_tourObjectif == 15)
      {
        m_ordre = false;
        m_tourDebut = 0;
        m_tourActuel = 0;
        m_tourObjectif = 0;
        m_score += 10;
      }
    }

    if(m_tourActuel>=8 && m_tourActuel<16 && m_ordre==true)
      m_score -= 1;

    if(m_tourActuel>=16 && m_tourActuel<50 && m_ordre==true)
    {
      auto RND = ((float)(rand()))/((float)(RAND_MAX));
      if(RND <= 0.2)
      {
        m_contreOrdre = true;
        ordre();
        m_tourDebut = tour;
      }
    }

    if(m_tourActuel>=50 && m_tourActuel<65 && m_ordre==true)
    m_score -= 6;

    if(m_tourActuel==65 && m_score!=0)
    {
      m_score -= 3;
      m_ordre = false;
    }
  }

}


Dispatching::~Dispatching()
{
}
