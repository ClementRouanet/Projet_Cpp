#include <iostream>
#include <string>
#include <chrono>
#include <thread>

#include "salle_de_controle.hpp"
#include "centrale.hpp"
#include "securite.hpp"
#include "dispatching.hpp"
#include "sdl2.hpp"

using namespace std;


SalleDeControle::SalleDeControle(): m_schemaCentrale(false)
{
}

void SalleDeControle::majAffichage(sdl2::window& fenetre, Centrale& centrale)
{
  Securite s;
  Dispatching d;
  if(m_schemaCentrale == false)
  {
    cadre(fenetre);
    s.affichageSecurite(fenetre, centrale);
    d.affichageDispatching(fenetre, centrale);
    affichageProdElec(fenetre, centrale);
    afficheTauxBorePiscine(fenetre, centrale);
    afficheCircuitPrim(fenetre, centrale);
    afficheCircuitSec(fenetre, centrale);
    afficheSystSecurite(fenetre);
    affichePressionEnceinte(fenetre, centrale);
    afficheSystRefroidissement(fenetre, centrale);
    afficheEtatBarreGraphite(fenetre, centrale);
    afficheCommandes(fenetre);

  }
  else
  {
    affichageSchemaCentrale(fenetre, centrale);
  }


  fenetre << sdl2::flush;
}

void SalleDeControle::cadre(sdl2::window& fenetre) const
{
  sdl2::image cadre("image/Cadre.png", fenetre);

  auto [wph, hph] = fenetre.dimensions();
  cadre.stretch({wph,hph});

  /*sdl2::font fonte_titre("./data/Lato-Bold.ttf",50);
  sdl2::texte titre ("Salle de contrôle", fonte_titre, fenetre, {0xFF,0x00,0x00,0x00});
  titre.at(2*wph/5-20,0);*/

  fenetre << cadre; //<< titre;
}


void SalleDeControle::affichageDispatching(sdl2::window& fenetre) const
{

}


void SalleDeControle::affichageProdElec(sdl2::window& fenetre, Centrale& centrale) const
{
  double production = centrale.productionCentrale();

  string sProduction(to_string(production));
  sProduction.erase(5,4);

  auto [wph, hph] = fenetre.dimensions();
  sdl2::font fonte_texte("./data/Lato-Bold.ttf",20);
  sdl2::texte texteProduction("Production électrique : " + sProduction + " MW", fonte_texte, fenetre, {0x00,0x00,0x00,0x00});
  //texteProduction.at(0*wph+40,140);
  texteProduction.at(0.37*wph,0.14*hph);

  fenetre << texteProduction;
}

void SalleDeControle::afficheTauxBorePiscine(sdl2::window& fenetre, Centrale& centrale) const
{
  double bore = centrale.tauxBoreActuel();

  string sBore(to_string(bore));
  sBore.erase(4,5);

  auto [wph, hph] = fenetre.dimensions();
  sdl2::font fonte_texte("./data/Lato-Bold.ttf",20);
  sdl2::texte texteBore("Taux de bore dans la piscine : " + sBore, fonte_texte, fenetre, {0x00,0x00,0x00,0x00});
  texteBore.at(0.35*wph,0.77*hph);

  fenetre << texteBore;
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

  sRendement.erase(2,7);
  sTemperature.erase(5,4);
  sDebit.erase(5,4);
  sPression.erase(4,5);
  sRadioactivite.erase(4,5);

  auto [wph, hph] = fenetre.dimensions();

  sdl2::font fonte_texte("./data/Lato-Bold.ttf",15);
  //sdl2::font fonte_titre("./data/Lato-Bold.ttf",30);

  //sdl2::texte texte("Circuit Primaire", fonte_titre, fenetre, {0x00,0x00,0xFF,0x00});
  sdl2::texte texteRendement("Rendement de la pompe : " + sRendement + " %", fonte_texte, fenetre, {0x00,0x00,0x00,0x00});
  sdl2::texte texteTemperature("Température dans le circuit : " + sTemperature + " °C", fonte_texte, fenetre, {0x00,0x00,0x00,0x00});
  sdl2::texte texteDebit("Débit de l'eau : " + sDebit + " m^3/s", fonte_texte, fenetre, {0x00,0x00,0x00,0x00});
  sdl2::texte textePression("Pression : " + sPression + " bar", fonte_texte, fenetre, {0x00,0x00,0x00,0x00});
  sdl2::texte texteRadioactivite("Radioactivité : " + sRadioactivite + " becquerel", fonte_texte, fenetre, {0x00,0x00,0x00,0x00});

  /*texte.at(2*wph/5+60, 80);
  texteRendement.at(2*wph/5-20,140);
  texteTemperature.at(2*wph/5-20,180);
  texteDebit.at(2*wph/5-20,220);
  textePression.at(2*wph/5-20,260);
  texteRadioactivite.at(2*wph/5-20,300);*/

  //texte.at(0.1*wph,0.2*hph);
  texteRendement.at(0.02*wph,0.25*hph);
  texteTemperature.at(0.02*wph,0.3*hph);
  texteDebit.at(0.02*wph,0.35*hph);
  textePression.at(0.02*wph,0.4*hph);
  texteRadioactivite.at(0.02*wph,0.45*hph);

  fenetre << texteRendement << texteTemperature << texteDebit << textePression << texteRadioactivite;
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

  sRendement.erase(2,7);
  sTemperature.erase(5,4);
  sDebit.erase(5,4);
  sPression.erase(4,5);
  sRadioactivite.erase(4,5);

  if(temperature < 120)
  {
    sDebit = "0.000";
    sPression = "1.00";
    sTemperature = "rien";
  }

  auto [wph, hph] = fenetre.dimensions();

  sdl2::font fonte_texte("./data/Lato-Bold.ttf",15);
  //sdl2::font fonte_titre("./data/Lato-Bold.ttf",30);

  //sdl2::texte texte("Circuit Secondaire", fonte_titre, fenetre, {0x00,0x00,0xFF,0x00});
  sdl2::texte texteRendement("Rendement de la pompe : " + sRendement + " %", fonte_texte, fenetre, {0x00,0x00,0x00,0x00});
  sdl2::texte texteTemperature1("Température dans le circuit : " + sTemperature, fonte_texte, fenetre, {0x00,0x00,0x00,0x00});
  sdl2::texte texteTemperature2("Température dans le circuit : " + sTemperature + " °C", fonte_texte, fenetre, {0x00,0x00,0x00,0x00});
  sdl2::texte texteDebit("Débit de l'eau : " + sDebit + " m^3/s", fonte_texte, fenetre, {0x00,0x00,0x00,0x00});
  sdl2::texte textePression("Pression : " + sPression + " bar", fonte_texte, fenetre, {0x00,0x00,0x00,0x00});
  sdl2::texte texteRadioactivite("Radioactivité : " + sRadioactivite + " becquerel", fonte_texte, fenetre, {0x00,0x00,0x00,0x00});

  //texte.at(2*wph/5+60, 390);
  texteRendement.at(0.73*wph,0.25*hph);
  texteDebit.at(0.73*wph,0.3*hph);
  textePression.at(0.73*wph,0.35*hph);
  texteRadioactivite.at(0.73*wph,0.4*hph);
  texteTemperature1.at(0.73*wph,0.45*hph);
  texteTemperature2.at(0.73*wph,0.45*hph);

  if(temperature < 120)
    fenetre << texteRendement << texteTemperature1 << texteDebit << textePression << texteRadioactivite;
  else
    fenetre << texteRendement << texteTemperature2 << texteDebit << textePression << texteRadioactivite;
}


void SalleDeControle::afficheSystSecurite(sdl2::window& fenetre) const
{

}


void SalleDeControle::affichePressionEnceinte(sdl2::window& fenetre, Centrale& centrale) const
{
  double pression = centrale.pressionEnceinte();

  string sPression(to_string(pression));
  sPression.erase(4,5);

  auto [wph, hph] = fenetre.dimensions();
  sdl2::font fonte_texte("./data/Lato-Bold.ttf",20);
  sdl2::texte textePression("Pression sur l'enceinte de confinement : " + sPression, fonte_texte, fenetre, {0x00,0x00,0x00,0x00});
  textePression.at(0.33*wph,0.26*hph);

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

  sRendement.erase(2,7);
  sDebit.erase(5,4);
  sDifference.erase(5,4);

  auto [wph, hph] = fenetre.dimensions();

  sdl2::font fonte_texte("./data/Lato-Bold.ttf",15);
  //sdl2::font fonte_titre("./data/Lato-Bold.ttf",30);

  //sdl2::texte texte("Système de refroidissement", fonte_titre, fenetre, {0x00,0x00,0xFF,0x00});
  sdl2::texte texteRendement("Rendement pompe condenseur : " + sRendement + " %", fonte_texte, fenetre, {0x00,0x00,0x00,0x00});
  sdl2::texte texteDebit("Débit eau condenseur: " + sDebit + " m^3/s", fonte_texte, fenetre, {0x00,0x00,0x00,0x00});
  sdl2::texte texteDifference("Différence température E-S : " + sDifference + " °C", fonte_texte, fenetre, {0x00,0x00,0x00,0x00});

  //texte.at(0*wph+40,250);
  texteRendement.at(0.02*wph,0.84*hph);
  texteDebit.at(0.02*wph,0.89*hph);
  texteDifference.at(0.02*wph,0.94*hph);

  fenetre << texteRendement << texteDebit << texteDifference;
}


void SalleDeControle::afficheEtatBarreGraphite(sdl2::window& fenetre, Centrale& centrale) const
{
  double barresGr = centrale.etatBarresGr();

  string sbarresGr(to_string(barresGr*100));
  sbarresGr.erase(2,7);

  auto [wph, hph] = fenetre.dimensions();
  sdl2::font fonte_texte("./data/Lato-Bold.ttf",20);
  sdl2::texte texteBarresGr("Etat des barres de graphite : " + sbarresGr + " %", fonte_texte, fenetre, {0x00,0x00,0x00,0x00});
  texteBarresGr.at(0.35*wph,0.9*hph);

  fenetre << texteBarresGr;
}


void SalleDeControle::afficheCommandes(sdl2::window& fenetre) const
{
  auto [wph, hph] = fenetre.dimensions();

  sdl2::font fonte_texte("./data/Lato-Bold.ttf",15);
  //sdl2::font fonte_titre("./data/Lato-Bold.ttf",30);

  //sdl2::texte texte("Commandes", fonte_titre, fenetre, {0x00,0x00,0xFF,0x00});
  sdl2::texte texte1("1 : rendement pompe circuit primaire", fonte_texte, fenetre, {0x00,0x00,0x00,0x00});
  sdl2::texte texte2("2 : rendement pompe circuit secondaire", fonte_texte, fenetre, {0x00,0x00,0x00,0x00});
  sdl2::texte texteB("B : action sur barres de contrôle", fonte_texte, fenetre, {0x00,0x00,0x00,0x00});
  sdl2::texte texteT("T : action sur taux acide borique", fonte_texte, fenetre, {0x00,0x00,0x00,0x00});
  sdl2::texte texteP("P : température pressuriseur", fonte_texte, fenetre, {0x00,0x00,0x00,0x00});
  sdl2::texte texteR("R : rendement pompe condenseur", fonte_texte, fenetre, {0x00,0x00,0x00,0x00});
  sdl2::texte texteU("U : arrêt d'urgence", fonte_texte, fenetre, {0x00,0x00,0x00,0x00});
  sdl2::texte texteS("S (maintenir) : fin session", fonte_texte, fenetre, {0x00,0x00,0x00,0x00});
  sdl2::texte texteTab("Tab : affiche schéma centrale", fonte_texte, fenetre, {0x00,0x00,0x00,0x00});
  sdl2::texte texteEspace("Espace : passer poste sécurité", fonte_texte, fenetre, {0x00,0x00,0x00,0x00});

  //texte.at(3*wph/4,300);
  texte1.at(0.73*wph,0.65*hph);
  texte2.at(0.73*wph,0.68*hph);
  texteB.at(0.73*wph,0.71*hph);
  texteT.at(0.73*wph,0.74*hph);
  texteP.at(0.73*wph,0.77*hph);
  texteR.at(0.73*wph,0.8*hph);
  texteU.at(0.73*wph,0.83*hph);
  texteS.at(0.73*wph,0.86*hph);
  texteTab.at(0.73*wph,0.89*hph);
  texteEspace.at(0.73*wph,0.92*hph);

  fenetre << texte1 << texte2 << texteB << texteT << texteP << texteR << texteU << texteS << texteTab << texteEspace;
}


bool SalleDeControle::majCommandes(sdl2::window& fenetre, int touche, Centrale& centrale)
{
  Securite s;
  Dispatching d;

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
    m_schemaCentrale = true;
    //affichageSchemaCentrale(fenetre, centrale);
    break;

    case 32 : // Espace
    passagePosteSecurite(fenetre, centrale);
    break;

    s.majSecurite(fenetre,centrale);
    d.majDispatching(fenetre, centrale, 1);
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
  double barre;

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
            barre = centrale.propGrDemande();
            centrale.majPropGrDemandee(barre + 0.05);
            break;

            case sdl2::event_keyboard::down :
            barre = centrale.propGrDemande();
            centrale.majPropGrDemandee(barre - 0.05);
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


void SalleDeControle::majTauxAcideBorique(sdl2::window& fenetre, Centrale& centrale)
{
  double acideBorique;

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
            acideBorique = centrale.tauxBoreActuel();
            centrale.majTauxBoreDemande(acideBorique + 0.05);
            break;

            case sdl2::event_keyboard::down :
            acideBorique = centrale.tauxBoreActuel();
            centrale.majTauxBoreDemande(acideBorique - 0.05);
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


void SalleDeControle::majRendementPressuriseur(sdl2::window& fenetre, Centrale& centrale)
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
            rendement = centrale.tempPressuriseurDemande();
            centrale.majTempPressuriseurDemande(rendement + 5);
            break;

            case sdl2::event_keyboard::down :
            rendement = centrale.tempPressuriseurDemande();
            centrale.majTempPressuriseurDemande(rendement - 5);
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

  if (secondesEcoulees.count() >= 0.75)
  return true;

  return false;
}


void SalleDeControle::affichageSchemaCentrale(sdl2::window& fenetre, Centrale& centrale)
{
  bool quitter = false;
  bool iskey_down = false;
  sdl2::event_queue queue;

  if (not quitter)
  {
    schemaCentrale(fenetre, centrale);
    auto events = queue.pull_events();
    for (const auto& e : events)
    {
      if ((e->kind_of_event() == sdl2::event::key_down) || (e->kind_of_event() == sdl2::event::key_up))
      {
        auto& key_ev = dynamic_cast<sdl2::event_keyboard&>(*e);

        if ((e->kind_of_event() == sdl2::event::key_down) &&  (iskey_down == false))
        {
          if (key_ev.code() == 13)
          {
            quitter = true;
            m_schemaCentrale = false;
          }

        iskey_down = true;
        }
      if (key_ev.type_of_event() == sdl2::event::key_up)
      iskey_down = false;
      }
    }
  }
  //majAffichage(fenetre, centrale);
}


void SalleDeControle::schemaCentrale(sdl2::window& fenetre, Centrale& centrale)
{
  double etatCentrale = centrale.etatCentrale();
  double etatReacteur = centrale.tauxBoreActuel(); //etatCuve();
  double etatCircuitPrim = centrale.rendementPompePrim(); //etatCircuitPrim();
  double etatCircuitSec = centrale.rendementPompeSec(); //etatCircuitSec();
  double etatCondenseur = centrale.rendementPompeCondenseur(); //etatCondenseur();

  auto [wph, hph] = fenetre.dimensions();

  sdl2::image schema("image/Centrale nucleaire.jpg", fenetre);
  schema.stretch({4*wph/6,4*hph/6});
  schema.at(wph/6,hph/6);

  sdl2::image centraleNucl("image/Centrale.png", fenetre);
  centraleNucl.stretch({4*wph/6,4*hph/6});
  centraleNucl.at(wph/6,hph/6);
  centraleNucl.color_filter({0xFF,0x00,0x00,0xFF});

  sdl2::image reacteur("image/Reacteur.png", fenetre);
  reacteur.stretch({4*wph/6,4*hph/6});
  reacteur.at(wph/6,hph/6);
  reacteur.color_filter({0xFF,0x00,0x00,0xFF});

  sdl2::image circuitPrim("image/Circuit_primaire.png", fenetre);
  circuitPrim.stretch({4*wph/6,4*hph/6});
  circuitPrim.at(wph/6,hph/6);
  //circuitPrim.color_filter({0xFF,0x00,0x00,0xFF});

  sdl2::image circuitSec("image/Circuit_secondaire.png", fenetre);
  circuitSec.stretch({4*wph/6,4*hph/6});
  circuitSec.at(wph/6,hph/6);
  circuitSec.color_filter({0xFF,0x00,0x00,0xFF});

  sdl2::image condenseur("image/Circuit_refroidissement.png", fenetre);
  condenseur.stretch({4*wph/6,4*hph/6});
  condenseur.at(wph/6,hph/6);
  condenseur.color_filter({0xFF,0x00,0x00,0xFF});

  fenetre << schema << sdl2::flush;

  this_thread::sleep_for(chrono::milliseconds(500));

  if(etatCentrale < 0.5)
  fenetre << centraleNucl;

  if(etatReacteur < 0.3)
  fenetre << reacteur;

  if(etatCircuitPrim < 0.3)
  fenetre << circuitPrim;

  if(etatCircuitSec < 0.3)
  fenetre << circuitSec;

  if(etatCondenseur < 0.3)
  fenetre << condenseur;

  fenetre << sdl2::flush;

  this_thread::sleep_for(chrono::milliseconds(500));
}


void SalleDeControle::passagePosteSecurite(sdl2::window& fenetre, Centrale& centrale)
{

}


SalleDeControle::~SalleDeControle()
{
}
