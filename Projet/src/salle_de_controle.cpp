#include <iostream>
#include <string>
#include <chrono>

#include "salle_de_controle.hpp"
#include "centrale.hpp"
#include "circuit_primaire.hpp"
#include "circuit_secondaire.hpp"
#include "sdl2.hpp"

using namespace std;


SalleDeControle::SalleDeControle()
{
}

void SalleDeControle::majAffichage(sdl2::window& fenetre, Centrale& centrale)
{
  cadre(fenetre);
  affichageDispatching(fenetre);
  affichageProdElec(fenetre, centrale);
  afficheTauxBorePiscine(fenetre);
  afficheCircuitPrim(fenetre, centrale);
  afficheCircuitSec(fenetre, centrale);
  afficheSystSecurite(fenetre);
  affichePressionEnceinte(fenetre, centrale);
  afficheSystRefroidissement(fenetre, centrale);
  afficheEtatBarreGraphite(fenetre);
  afficheCommandes(fenetre);

  fenetre << sdl2::flush;
}

void SalleDeControle::cadre(sdl2::window& fenetre) const
{
  sdl2::image cadre("image/Cadre_SalleDeControle.jpg", fenetre);
  auto [wph, hph] = fenetre.dimensions();
  cadre.stretch({wph,hph});

  sdl2::font fonte_titre("./data/Lato-Bold.ttf",50);
  sdl2::texte titre ("Salle de contrôle", fonte_titre, fenetre, {0xFF,0x00,0x00,0x00});
  titre.at(2*wph/5-20,0);

  fenetre << cadre << titre;
}


void SalleDeControle::affichageDispatching(sdl2::window& fenetre) const
{

}


void SalleDeControle::affichageProdElec(sdl2::window& fenetre, Centrale& centrale) const
{
  double production = centrale.productionCentrale();

  string sProduction(to_string(production));

  auto [wph, hph] = fenetre.dimensions();
  sdl2::font fonte_texte("./data/Lato-Bold.ttf",20);
  sdl2::texte texteProduction("Production électrique : " + sProduction + " MW", fonte_texte, fenetre, {0x00,0x00,0x00,0x00});
  texteProduction.at(0*wph+40,140);

  fenetre << texteProduction;
}

void SalleDeControle::afficheTauxBorePiscine(sdl2::window& fenetre) const
{

}


void SalleDeControle::afficheCircuitPrim(sdl2::window& fenetre, Centrale& centrale) const
{
  double rendement = centrale.rendementPompePrim();
  double temperature = centrale.temperatureEau();
  double debit = centrale.debitEauPrim();
  double pression = centrale.pressionPrim();
  double radioactivite = centrale.radioactivitePrim();

  string sRendement(to_string(rendement*100));
  string sTemperature(to_string(temperature));
  string sDebit(to_string(debit));
  string sPression(to_string(pression));
  string sRadioactivite(to_string(radioactivite));

  auto [wph, hph] = fenetre.dimensions();

  sdl2::font fonte_texte("./data/Lato-Bold.ttf",20);
  sdl2::font fonte_titre("./data/Lato-Bold.ttf",30);

  sdl2::texte texte("Circuit Primaire", fonte_titre, fenetre, {0x00,0x00,0xFF,0x00});
  sdl2::texte texteRendement("Rendement de la pompe : " + sRendement + " %", fonte_texte, fenetre, {0x00,0x00,0x00,0x00});
  sdl2::texte texteTemperature("Température dans le circuit : " + sTemperature + " °C", fonte_texte, fenetre, {0x00,0x00,0x00,0x00});
  sdl2::texte texteDebit("Débit de l'eau : " + sDebit + " m^3.s^(-1)", fonte_texte, fenetre, {0x00,0x00,0x00,0x00});
  sdl2::texte textePression("Pression : " + sPression + " bar", fonte_texte, fenetre, {0x00,0x00,0x00,0x00});
  sdl2::texte texteRadioactivite("Radioactivité : " + sRadioactivite + " becquerel", fonte_texte, fenetre, {0x00,0x00,0x00,0x00});

  texte.at(2*wph/5+60, 80);
  texteRendement.at(2*wph/5-20,140);
  texteTemperature.at(2*wph/5-20,180);
  texteDebit.at(2*wph/5-20,220);
  textePression.at(2*wph/5-20,260);
  texteRadioactivite.at(2*wph/5-20,300);

  fenetre << texte << texteRendement << texteTemperature << texteDebit << textePression << texteRadioactivite;
}


void SalleDeControle::afficheCircuitSec(sdl2::window& fenetre, Centrale& centrale) const
{
  double rendement = centrale.rendementPompeSec();
  double temperature = centrale.temperatureVapeur();
  double debit = centrale.debitEauSec();
  double pression = centrale.pressionVapeur();
  double radioactivite = centrale.radioactiviteSec();

  string sRendement(to_string(rendement*100));
  string sTemperature(to_string(temperature));
  string sDebit(to_string(debit));
  string sPression(to_string(pression));
  string sRadioactivite(to_string(radioactivite));

  if(temperature < 120)
  {
      sDebit = "0";
      sPression = "1";
  }

  auto [wph, hph] = fenetre.dimensions();

  sdl2::font fonte_texte("./data/Lato-Bold.ttf",20);
  sdl2::font fonte_titre("./data/Lato-Bold.ttf",30);

  sdl2::texte texte("Circuit Secondaire", fonte_titre, fenetre, {0x00,0x00,0xFF,0x00});
  sdl2::texte texteRendement("Rendement de la pompe : " + sRendement + " %", fonte_texte, fenetre, {0x00,0x00,0x00,0x00});
  sdl2::texte texteTemperature("Température dans le circuit : " + sTemperature + " °C", fonte_texte, fenetre, {0x00,0x00,0x00,0x00});
  sdl2::texte texteDebit("Débit de l'eau : " + sDebit + " m^3.s^(-1)", fonte_texte, fenetre, {0x00,0x00,0x00,0x00});
  sdl2::texte textePression("Pression : " + sPression + " bar", fonte_texte, fenetre, {0x00,0x00,0x00,0x00});
  sdl2::texte texteRadioactivite("Radioactivité : " + sRadioactivite + " becquerel", fonte_texte, fenetre, {0x00,0x00,0x00,0x00});

  texte.at(2*wph/5+60, 390);
  texteRendement.at(2*wph/5-20,450);
  texteDebit.at(2*wph/5-20,490);
  textePression.at(2*wph/5-20,530);
  texteRadioactivite.at(2*wph/5-20,570);
  texteTemperature.at(2*wph/5-20,610);


  if(temperature < 120)
    fenetre << texte << texteRendement << texteDebit << textePression << texteRadioactivite;
  else
    fenetre << texte << texteRendement << texteTemperature << texteDebit << textePression << texteRadioactivite;
}


void SalleDeControle::afficheSystSecurite(sdl2::window& fenetre) const
{

}


void SalleDeControle::affichePressionEnceinte(sdl2::window& fenetre, Centrale& centrale) const
{
  double pression = centrale.pressionEnceinte();

  string sPression(to_string(pression));

  auto [wph, hph] = fenetre.dimensions();
  sdl2::font fonte_texte("./data/Lato-Bold.ttf",20);
  sdl2::texte textePression("Pression sur enceinte de confinement : " + sPression, fonte_texte, fenetre, {0x00,0x00,0x00,0x00});
  textePression.at(0*wph+40,540);

  fenetre << textePression;
}


void SalleDeControle::afficheSystRefroidissement(sdl2::window& fenetre, Centrale& centrale) const
{
  double rendement = centrale.rendementPompeCondenseur();
  double debit = centrale.debitCondenseur();
  double difference = centrale.diffChaleurCondenseur();

  string sRendement(to_string(rendement*100));
  string sDebit(to_string(debit));
  string sDifference(to_string(difference));

  auto [wph, hph] = fenetre.dimensions();

  sdl2::font fonte_texte("./data/Lato-Bold.ttf",20);
  sdl2::font fonte_titre("./data/Lato-Bold.ttf",30);

  sdl2::texte texte("Système de refroidissement", fonte_titre, fenetre, {0x00,0x00,0xFF,0x00});
  sdl2::texte texteRendement("Rendement pompe condenseur : " + sRendement + " %", fonte_texte, fenetre, {0x00,0x00,0x00,0x00});
  sdl2::texte texteDebit("Débit eau condenseur: " + sDebit + " m^3.s^(-1)", fonte_texte, fenetre, {0x00,0x00,0x00,0x00});
  sdl2::texte texteDifference("Différence température E-S : " + sDifference + " °C", fonte_texte, fenetre, {0x00,0x00,0x00,0x00});

  texte.at(0*wph+40,250);
  texteRendement.at(0*wph+40,310);
  texteDebit.at(0*wph+40,350);
  texteDifference.at(0*wph+40,390);

  fenetre << texte << texteRendement << texteDebit << texteDifference;
}


void SalleDeControle::afficheEtatBarreGraphite(sdl2::window& fenetre) const
{

}


void SalleDeControle::afficheCommandes(sdl2::window& fenetre) const
{
  auto [wph, hph] = fenetre.dimensions();

  sdl2::font fonte_texte("./data/Lato-Bold.ttf",20);
  sdl2::font fonte_titre("./data/Lato-Bold.ttf",30);

  sdl2::texte texte("Commandes", fonte_titre, fenetre, {0x00,0x00,0xFF,0x00});
  sdl2::texte texte1("1 : rendement pompe circuit primaire", fonte_texte, fenetre, {0x00,0x00,0x00,0x00});
  sdl2::texte texte2("2 : rendement pompe circuit secondaire", fonte_texte, fenetre, {0x00,0x00,0x00,0x00});
  sdl2::texte texteB("B : action sur barres de contrôle", fonte_texte, fenetre, {0x00,0x00,0x00,0x00});
  sdl2::texte texteT("T : action sur taux acide borique", fonte_texte, fenetre, {0x00,0x00,0x00,0x00});
  sdl2::texte texteP("P : rendement pressuriseur", fonte_texte, fenetre, {0x00,0x00,0x00,0x00});
  sdl2::texte texteR("R : rendement pompe condenseur", fonte_texte, fenetre, {0x00,0x00,0x00,0x00});
  sdl2::texte texteU("U : arrêt d'urgence", fonte_texte, fenetre, {0x00,0x00,0x00,0x00});
  sdl2::texte texteS("S (maintenir) : fin session", fonte_texte, fenetre, {0x00,0x00,0x00,0x00});
  sdl2::texte texteTab("Tab : affiche schéma centrale", fonte_texte, fenetre, {0x00,0x00,0x00,0x00});
  sdl2::texte texteEspace("Espace : passer poste sécurité", fonte_texte, fenetre, {0x00,0x00,0x00,0x00});

  texte.at(3*wph/4,330);
  texte1.at(3*wph/4-40,390);
  texte2.at(3*wph/4-40,430);
  texteB.at(3*wph/4-40,470);
  texteT.at(3*wph/4-40,510);
  texteP.at(3*wph/4-40,550);
  texteR.at(3*wph/4-40,590);
  texteU.at(3*wph/4-40,630);
  texteS.at(3*wph/4-40,670);
  texteTab.at(3*wph/4-40,710);
  texteEspace.at(3*wph/4-40,750);

  fenetre << texte << texte1 << texte2 << texteB << texteT << texteP << texteR << texteU << texteS << texteTab << texteEspace;
}


bool SalleDeControle::majCommandes(sdl2::window& fenetre, int touche, Centrale& centrale)
{
    switch (touche)
    {
      case 49 :  // 1
        majRendementPompeCircuitPrim(fenetre, centrale);
        break;

      case 50 :  // 2
        majRendementPompeCircuitSec(fenetre, centrale);
        break;

      case 98 :  // b
        majBarreControle(fenetre, centrale);
        break;

      case 116 :  // t
        majTauxAcideBorique(fenetre, centrale);
        break;

      case 112 :  // p
        majRendementPressuriseur(fenetre, centrale);
        break;

      case 114 :  // r
        majRendementPompeCondenseur(fenetre, centrale);
        break;

      case 117 :  // u
        arretUrgence(fenetre, centrale);
        break;

      case 115 :  // s
        return finSession();
        break;

      case 9 :  // tab
        affichageSchemaCentrale(fenetre, centrale);
        break;

      case 32 : // Espace
        passagePosteSecurite(fenetre, centrale);
        break;
    }
    return false;
}


void SalleDeControle::majRendementPompeCircuitPrim(sdl2::window& fenetre, Centrale& centrale)
{
  double rendement;

  bool quitter = false;
  bool iskey_down = false;
  sdl2::event_queue queue;

  while (not quitter)
  {
    auto events = queue.pull_events();
    for (const auto& e : events)
    {
      if ((e->kind_of_event() == sdl2::event::key_down) || (e->kind_of_event() == sdl2::event::key_up))
      {
        auto& key_ev = dynamic_cast<sdl2::event_keyboard&>(*e);

        if ((e->kind_of_event() == sdl2::event::key_down) &&  (iskey_down == false))
        {
          switch (key_ev.code())
          {
            case 13 :
              quitter = true;
              break;

            case sdl2::event_keyboard::up :
              rendement = centrale.rendementPompePrim();
              centrale.majRendementPompePrim(rendement + 0.05);
              break;

            case sdl2::event_keyboard::down :
              rendement = centrale.rendementPompePrim();
              centrale.majRendementPompePrim(rendement - 0.05);
              break;
          }
          majAffichage(fenetre, centrale);
          iskey_down = true;
        }
      if (key_ev.type_of_event() == sdl2::event::key_up)
          iskey_down = false;
      }
    }
  }
}


void SalleDeControle::majRendementPompeCircuitSec(sdl2::window& fenetre, Centrale& centrale)
{
  double rendement;

  bool quitter = false;
  bool iskey_down = false;
  sdl2::event_queue queue;

  while (not quitter)
  {
    auto events = queue.pull_events();
    for (const auto& e : events)
    {
      if ((e->kind_of_event() == sdl2::event::key_down) || (e->kind_of_event() == sdl2::event::key_up))
      {
        auto& key_ev = dynamic_cast<sdl2::event_keyboard&>(*e);

        if ((e->kind_of_event() == sdl2::event::key_down) &&  (iskey_down == false))
        {
          switch (key_ev.code())
          {
            case 13 :
              quitter = true;
              break;

            case sdl2::event_keyboard::up :
              rendement = centrale.rendementPompeSec();
              centrale.majRendementPompeSec(rendement + 0.05);
              break;

            case sdl2::event_keyboard::down :
              rendement = centrale.rendementPompeSec();
              centrale.majRendementPompeSec(rendement - 0.05);
              break;
          }
          majAffichage(fenetre, centrale);
          iskey_down = true;
        }
        if (key_ev.type_of_event() == sdl2::event::key_up)
            iskey_down = false;
      }
    }
  }
}


void SalleDeControle::majBarreControle(sdl2::window& fenetre, Centrale& centrale)
{

}


void SalleDeControle::majTauxAcideBorique(sdl2::window& fenetre, Centrale& centrale)
{

}


void SalleDeControle::majRendementPressuriseur(sdl2::window& fenetre, Centrale& centrale)
{
  /// PB pas de rendement pressuriseur
}


void SalleDeControle::majRendementPompeCondenseur(sdl2::window& fenetre, Centrale& centrale)
{
  double rendement;

  bool quitter = false;
  bool iskey_down = false;
  sdl2::event_queue queue;

  while (not quitter)
  {
    auto events = queue.pull_events();
    for (const auto& e : events)
    {
      if ((e->kind_of_event() == sdl2::event::key_down) || (e->kind_of_event() == sdl2::event::key_up))
      {
        auto& key_ev = dynamic_cast<sdl2::event_keyboard&>(*e);

        if ((e->kind_of_event() == sdl2::event::key_down) &&  (iskey_down == false))
        {
          switch (key_ev.code())
          {
            case 13 :
              quitter = true;
              break;

            case sdl2::event_keyboard::up :
              rendement = centrale.rendementPompeCondenseur();
              centrale.majRendementPompeCondenseur(rendement + 0.05);
              break;

            case sdl2::event_keyboard::down :
              rendement = centrale.rendementPompeCondenseur();
              centrale.majRendementPompeCondenseur(rendement - 0.05);
              break;
          }
          majAffichage(fenetre, centrale);
          iskey_down = true;
        }
        if (key_ev.type_of_event() == sdl2::event::key_up)
            iskey_down = false;
      }
    }
  }
}


void SalleDeControle::arretUrgence(sdl2::window& fenetre, Centrale& centrale)
{

}


bool SalleDeControle::finSession()
{
  bool iskey_down = true;
  sdl2::event_queue queue;

  chrono::time_point<chrono::system_clock> start, end;
  start = chrono::system_clock::now();

  while (iskey_down == true)
  {
    auto events = queue.pull_events();
    for (const auto& e : events)
    {
      if ((e->kind_of_event() == sdl2::event::key_down) || (e->kind_of_event() == sdl2::event::key_up))
      {
        auto& key_ev = dynamic_cast<sdl2::event_keyboard&>(*e);

        if (key_ev.type_of_event() == sdl2::event::key_up)
            iskey_down = false;
      }
    }
  }
  end = chrono::system_clock::now();
  chrono::duration<double> secondesEcoulees = end - start;

  if (secondesEcoulees.count() >= 2)
    return true;

  return false;
}


void SalleDeControle::affichageSchemaCentrale(sdl2::window& fenetre, Centrale& centrale)
{

}


void SalleDeControle::passagePosteSecurite(sdl2::window& fenetre, Centrale& centrale)
{

}


SalleDeControle::~SalleDeControle()
{
}
