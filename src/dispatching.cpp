#include <iostream>
#include <string>
#include <chrono>
#include <random>
#include <functional>

#include "dispatching.hpp"
#include "sdl2.hpp"

using namespace std;


Dispatching::Dispatching()
    : m_tourActuel(0), m_score(100), m_nbOrdre(0), m_produire(0), m_ordre(false), m_contreOrdre(false), m_objectif(false), m_tourObjectif(0),
      m_finPosible(false), m_productionNulle(0)
{
}


int Dispatching::scoreDispatching()
{
  return m_score;
}


void Dispatching::ordreInitial(sdl2::window& fenetre)
{
  auto [wph, hph] = fenetre.dimensions();

  sdl2::font fonte_texte("./data/Lato-Bold.ttf",15);
  sdl2::texte texte1("Mettre la centrale en divergence :", fonte_texte, fenetre, {0x00,0x00,0x00,0x00});
  sdl2::texte texte2("- démarrer la réaction en chaîne", fonte_texte, fenetre, {0x00,0x00,0x00,0x00});
  sdl2::texte texte3("- démarrer production de vapeur dans le générateur", fonte_texte, fenetre, {0x00,0x00,0x00,0x00});

  texte1.at(0.02*wph,0.60*hph);
  texte2.at(0.023*wph,0.64*hph);
  texte3.at(0.023*wph,0.68*hph);

  fenetre << texte1 << texte2 << texte3;
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
  m_tourActuel = 0;
}


void Dispatching::affichageDispatching(sdl2::window& fenetre, Centrale& centrale, int niveau)
{
  double temperatureVap = centrale.temperatureVapeur();

  auto [wph, hph] = fenetre.dimensions();

  if(niveau == 1)
  {
    sdl2::font fonte_texte("./data/Lato-Bold.ttf",20);
    sdl2::texte texte("Amusez-vous !", fonte_texte, fenetre, {0x00,0x00,0x00,0x00});
    texte.at(0.02*wph,0.7*hph);
    fenetre << texte;
  }
  else
  {
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
}


void Dispatching::majdispatching(Centrale& centrale)
{
  double temperatureVap = centrale.temperatureVapeur();
  double production = centrale.productionCentrale();

  if(temperatureVap>140 && m_nbOrdre==0)
    m_nbOrdre = 1;

  if(m_ordre==false && m_nbOrdre>0)
  {
    ordre();
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
        m_tourObjectif = 0;
        m_score += 10;
      }
    }

    if(m_tourActuel>=8 && m_tourActuel<16)
      m_score -= 1;

    if(m_tourActuel>=16 && m_tourActuel<50)
    {
      auto RND = ((float)(rand()))/((float)(RAND_MAX));
      if(RND <= 0.2)
      {
        m_contreOrdre = true;
        ordre();
      }
    }

    if(m_tourActuel>=50 && m_tourActuel<65)
      m_score -= 6;

    if(m_tourActuel==65 && m_score!=0)
    {
      m_score -= 3;
      m_ordre = false;
    }

    if(production==0 || m_productionNulle!=0)
    {
      if(production == 0)
        m_productionNulle += 1;

      if(production != 0)
        m_productionNulle = 0;

      if(production==0 && m_productionNulle==6)
        m_finPosible = true;
    }
  }
  m_tourActuel += 1;
}


bool Dispatching::finDispatching()
{
  bool fin = false;

  if(m_score == 0)
    fin = true;

  if(m_finPosible == true)
  {
    auto RND = ((float)(rand()))/((float)(RAND_MAX));

    if(RND <= 0.5)
      fin = true;
  }

  return fin;
}


Dispatching::~Dispatching()
{
}
