#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <random>
#include <vector>

#include "salle_de_controle.hpp"

using namespace std;


SalleDeControle::SalleDeControle() : m_schemaCentrale(false), m_niveau(1)
{
}

void SalleDeControle::niveau(int niveau)
{
  m_niveau = niveau;
}


void SalleDeControle::majAffichage(sdl2::window& fenetre, Centrale& centrale)
{
  cadre(fenetre);
  dispatching.affichageDispatching(fenetre, centrale, m_niveau);
  securite.affichageSecurite(fenetre, centrale);
  affichageProdElec(fenetre, centrale);
  afficheTauxBorePiscine(fenetre, centrale);
  afficheCircuitPrim(fenetre, centrale);
  afficheCircuitSec(fenetre, centrale);
  affichePressionEnceinte(fenetre, centrale);
  afficheSystRefroidissement(fenetre, centrale);
  afficheEtatBarreGraphite(fenetre, centrale);
  afficheCommandes(fenetre);

  if(m_schemaCentrale == true)
    affichageSchemaCentrale(fenetre, centrale);

  fenetre << sdl2::flush;
}

void SalleDeControle::cadre(sdl2::window& fenetre) const
{
  sdl2::image cadre("image/Salle de contrôle.jpg", fenetre);

  auto [wph, hph] = fenetre.dimensions();
  cadre.stretch({wph,hph});

  fenetre << cadre;
}


void SalleDeControle::affichageProdElec(sdl2::window& fenetre, Centrale& centrale) const
{
  int production = centrale.productionCentrale();

  string sProduction(to_string(production));

  auto [wph, hph] = fenetre.dimensions();
  sdl2::font fonte_texte("./data/Welbut__.ttf",15);
  sdl2::texte texteProduction("Production électrique : " + sProduction + " MW", fonte_texte, fenetre, {0x00,0x00,0x00,0x00});
  texteProduction.at(0.415*wph,0.195*hph);

  fenetre << texteProduction;
}

void SalleDeControle::afficheTauxBorePiscine(sdl2::window& fenetre, Centrale& centrale) const
{
  double boreAct = centrale.tauxBoreActuel();
  double boreDem = centrale.tauxBoreDemande();

  string sBoreAct(to_string(boreAct));
  string sBoreDem(to_string(boreDem));

  sBoreAct.erase(4,5);
  sBoreDem.erase(4,5);

  auto [wph, hph] = fenetre.dimensions();
  sdl2::font fonte_texte("./data/Welbut__.ttf",13);

  sdl2::texte texteBoreAct("Taux de bore actuel dans la piscine : " + sBoreAct, fonte_texte, fenetre, {0x00,0x00,0x00,0x00});
  sdl2::texte texteBoreDem("Taux de bore demandé dans la piscine : " + sBoreDem, fonte_texte, fenetre, {0x00,0x00,0x00,0x00});

  texteBoreAct.at(0.73*wph,0.395*hph);
  texteBoreDem.at(0.73*wph,0.4275*hph);

  fenetre << texteBoreAct << texteBoreDem;
}


void SalleDeControle::afficheCircuitPrim(sdl2::window& fenetre, Centrale& centrale) const
{
  double rendement = centrale.rendementPompePrim();
  double temperature = centrale.temperatureEau();
  double debit = centrale.debitEauPrim();
  double pression = centrale.pressionPrim();
  int radioactivite = centrale.radioactivitePrim();


  string sRendement(to_string(rendement*100));
  string sTemperature(to_string(temperature));
  string sDebit(to_string(debit));
  string sPression(to_string(pression));
  string sRadioactivite(to_string(radioactivite));

  sRendement.erase(2,7);
  sTemperature.erase(5,4);
  sDebit.erase(5,4);
  sPression.erase(4,5);

  auto [wph, hph] = fenetre.dimensions();

  sdl2::font fonte_texte("./data/Welbut__.ttf",15);

  sdl2::texte texteRendement("Rendement de la pompe : " + sRendement + " %", fonte_texte, fenetre, {0x00,0x00,0x00,0x00});
  sdl2::texte texteTemperature("Température dans le circuit : " + sTemperature + " °C", fonte_texte, fenetre, {0x00,0x00,0x00,0x00});
  sdl2::texte texteDebit("Débit de l'eau : " + sDebit + " m^3/s", fonte_texte, fenetre, {0x00,0x00,0x00,0x00});
  sdl2::texte textePression("Pression : " + sPression + " bar", fonte_texte, fenetre, {0x00,0x00,0x00,0x00});
  sdl2::texte texteRadioactivite("Radioactivité : " + sRadioactivite + " becquerels", fonte_texte, fenetre, {0x00,0x00,0x00,0x00});

  texteRendement.at(0.045*wph,0.135*hph);
  texteTemperature.at(0.045*wph,0.175*hph);
  texteDebit.at(0.045*wph,0.215*hph);
  textePression.at(0.045*wph,0.255*hph);
  texteRadioactivite.at(0.045*wph,0.295*hph);

  fenetre << texteRendement << texteTemperature << texteDebit << textePression << texteRadioactivite;
}



void SalleDeControle::afficheCircuitSec(sdl2::window& fenetre, Centrale& centrale) const
{
  double rendement = centrale.rendementPompeSec();
  double temperature = centrale.temperatureVapeur();
  double debit = centrale.debitEauSec();
  double pression = centrale.pressionVapeur();
  int radioactivite = centrale.radioactiviteSec();

  string sRendement(to_string(rendement*100));
  string sTemperature(to_string(temperature));
  string sDebit(to_string(debit));
  string sPression(to_string(pression));
  string sRadioactivite(to_string(radioactivite));

  sRendement.erase(2,7);
  sTemperature.erase(5,4);
  sDebit.erase(5,4);
  sPression.erase(4,5);

  if(temperature < 120)
  {
    sDebit = "0.000";
    sPression = "1.00";
    sTemperature = "rien";
  }

  auto [wph, hph] = fenetre.dimensions();

  sdl2::font fonte_texte("./data/Welbut__.ttf",15);

  sdl2::texte texteRendement("Rendement de la pompe : " + sRendement + " %", fonte_texte, fenetre, {0x00,0x00,0x00,0x00});
  sdl2::texte texteTemperature1("Température dans le circuit : " + sTemperature, fonte_texte, fenetre, {0x00,0x00,0x00,0x00});
  sdl2::texte texteTemperature2("Température dans le circuit : " + sTemperature + " °C", fonte_texte, fenetre, {0x00,0x00,0x00,0x00});
  sdl2::texte texteDebit("Débit de l'eau : " + sDebit + " m^3/s", fonte_texte, fenetre, {0x00,0x00,0x00,0x00});
  sdl2::texte textePression("Pression : " + sPression + " bar", fonte_texte, fenetre, {0x00,0x00,0x00,0x00});
  sdl2::texte texteRadioactivite("Radioactivité : " + sRadioactivite + " becquerel", fonte_texte, fenetre, {0x00,0x00,0x00,0x00});

  texteRendement.at(0.75*wph,0.1375*hph);
  texteDebit.at(0.75*wph,0.1775*hph);
  textePression.at(0.75*wph,0.2175*hph);
  texteRadioactivite.at(0.75*wph,0.2575*hph);
  texteTemperature1.at(0.75*wph,0.2975*hph);
  texteTemperature2.at(0.75*wph,0.3375*hph);

  if(temperature < 120)
    fenetre << texteRendement << texteTemperature1 << texteDebit << textePression << texteRadioactivite;
  else
    fenetre << texteRendement << texteTemperature2 << texteDebit << textePression << texteRadioactivite;
}


void SalleDeControle::affichePressionEnceinte(sdl2::window& fenetre, Centrale& centrale) const
{
  double pression = centrale.pressionEnceinte();

  string sPression(to_string(pression));
  sPression.erase(4,5);

  auto [wph, hph] = fenetre.dimensions();
  sdl2::font fonte_texte("./data/Welbut__.ttf",15);
  sdl2::texte textePression("Pression sur l'enceinte de confinement : " + sPression, fonte_texte, fenetre, {0x00,0x00,0x00,0x00});
  textePression.at(0.37*wph,0.32*hph);

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

  sdl2::font fonte_texte("./data/Welbut__.ttf",15);

  sdl2::texte texteRendement("Rendement pompe condenseur : " + sRendement + " %", fonte_texte, fenetre, {0x00,0x00,0x00,0x00});
  sdl2::texte texteDebit("Débit eau condenseur: " + sDebit + " m^3/s", fonte_texte, fenetre, {0x00,0x00,0x00,0x00});
  sdl2::texte texteDifference("Différence température E-S : " + sDifference + " °C", fonte_texte, fenetre, {0x00,0x00,0x00,0x00});

  texteRendement.at(0.045*wph,0.83*hph);
  texteDebit.at(0.045*wph,0.87*hph);
  texteDifference.at(0.045*wph,0.91*hph);

  fenetre << texteRendement << texteDebit << texteDifference;
}


void SalleDeControle::afficheEtatBarreGraphite(sdl2::window& fenetre, Centrale& centrale) const
{
  double barresGr = centrale.etatBarresGr();
  double proportionD = centrale.propGrDemande();
  double proportionA = centrale.propGrActuel();

  string sbarresGr(to_string(barresGr*100));
  string sProportionD(to_string(proportionD*100));
  string sProportionA(to_string(proportionA*100));

  sbarresGr.erase(2,7);
  sProportionD.erase(4,5);
  sProportionA.erase(4,5);

  auto [wph, hph] = fenetre.dimensions();
  sdl2::font fonte_texte("./data/Welbut__.ttf",14);

  sdl2::texte texteBarresGr("Etat des barres de graphite : " + sbarresGr + " %", fonte_texte, fenetre, {0x00,0x00,0x00,0x00});
  sdl2::texte texteProportionD("Proportion demandée de graphite hors de l'eau : " + sProportionD + " %", fonte_texte, fenetre, {0x00,0x00,0x00,0x00});
  sdl2::texte texteProportionA("Proportion actuelle de graphite hors de l'eau : " + sProportionA + " %", fonte_texte, fenetre, {0x00,0x00,0x00,0x00});

  texteBarresGr.at(0.35*wph,0.855*hph);
  texteProportionA.at(0.35*wph,0.89*hph);
  texteProportionD.at(0.35*wph,0.925*hph);

  fenetre << texteBarresGr << texteProportionD << texteProportionA;
}


void SalleDeControle::afficheCommandes(sdl2::window& fenetre) const
{
  auto [wph, hph] = fenetre.dimensions();

  sdl2::font fonte_texte("./data/Lato-Bold.ttf",15);

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


vector<int> SalleDeControle::majCommandes(sdl2::window& fenetre, int touche, Centrale& centrale)
{
  vector<int> sortie = {false, false};

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
    sortie[0] = 0;
    sortie[1] = finSession();
    break;

    case 9 :  // tab
    m_schemaCentrale = true;
    break;

    case 32 : // Espace
    sortie[0] = 1;
    sortie[1] = 0;
    break;

    case sdl2::event_keyboard::left : // flèche gauche
    securite.majSecuriteGauche();
    break;

    case sdl2::event_keyboard::right :  // flèche droite
    securite.majSecuriteDroite();
    break;
  }

  return sortie;
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
            acideBorique = centrale.tauxBoreDemande();
            centrale.majTauxBoreDemande(acideBorique + 0.05);
            break;

            case sdl2::event_keyboard::down :
            acideBorique = centrale.tauxBoreDemande();
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
  double Ecuve = centrale.etatCuve();
  double Ecanaux = centrale.etatCanaux();
  double Ebarre = centrale.etatBarresGr();

  double probaReussite = 0.7*Ecuve*Ecanaux*Ebarre + 0.15;
  auto RND = ((float)(rand()))/((float)(RAND_MAX));

  if(RND <= probaReussite)
  {
    centrale.majPropGrDemandee(0);
  }
  else
  {
    auto chance1 = ((float)(rand()))/((float)(RAND_MAX));
    auto chance2 = ((float)(rand()))/((float)(RAND_MAX));
    auto chance3 = ((float)(rand()))/((float)(RAND_MAX));

    auto RND1 = ((float)(rand()))/((float)(RAND_MAX))*0.1;
    auto RND2 = ((float)(rand()))/((float)(RAND_MAX))*0.08;
    auto RND3 = ((float)(rand()))/((float)(RAND_MAX))*0.08;

    if(chance1 <= 0.8)
      centrale.majEtatCanaux(Ecanaux - (0.05 + RND1));

    if(chance2 <= 0.3)
      centrale.majEtatBarresGr(Ebarre - (0.02 + RND2));

    if(chance3 <= 0.4)
      centrale.majEtatCuve(Ecuve - RND3);
  }
}


int SalleDeControle::finSession()
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
  return 1;

  return 0;
}


void SalleDeControle::affichageSchemaCentrale(sdl2::window& fenetre, Centrale& centrale)
{
  bool iskey_down = false;
  sdl2::event_queue queue;

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
          m_schemaCentrale = false;

        iskey_down = true;
      }
    if (key_ev.type_of_event() == sdl2::event::key_up)
      iskey_down = false;
    }
  }
}


void SalleDeControle::schemaCentrale(sdl2::window& fenetre, Centrale& centrale)
{
  double etatCentrale = centrale.etatCentrale();
  double etatReacteur = centrale.etatCuve();
  double etatCircuitPrim = centrale.etatCircuitPrim();
  double etatCircuitSec = centrale.etatCircuitSec();
  double etatCondenseur = centrale.etatCondenseur();

  auto [wph, hph] = fenetre.dimensions();

  sdl2::image schema("image/Centrale nucleaire.jpg", fenetre);
  schema.stretch({4*wph/6,4*hph/6});
  schema.at(wph/6,hph/6);

  sdl2::image centraleNucl("image/Centrale.png", fenetre);
  centraleNucl.stretch({4*wph/6,4*hph/6});
  centraleNucl.at(wph/6,hph/6);

  sdl2::image reacteur("image/Reacteur.png", fenetre);
  reacteur.stretch({4*wph/6,4*hph/6});
  reacteur.at(wph/6,hph/6);

  sdl2::image circuitPrim("image/Circuit_primaire.png", fenetre);
  circuitPrim.stretch({4*wph/6,4*hph/6});
  circuitPrim.at(wph/6,hph/6);

  sdl2::image circuitSec("image/Circuit_secondaire.png", fenetre);
  circuitSec.stretch({4*wph/6,4*hph/6});
  circuitSec.at(wph/6,hph/6);

  sdl2::image condenseur("image/Circuit_refroidissement.png", fenetre);
  condenseur.stretch({4*wph/6,4*hph/6});
  condenseur.at(wph/6,hph/6);

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

  this_thread::sleep_for(chrono::milliseconds(400));
}


bool SalleDeControle::majdispatching( Centrale& centrale)
{
  return dispatching.majdispatching(centrale);
}


int SalleDeControle::scoreDispatching()
{
  return dispatching.scoreDispatching();
}


SalleDeControle::~SalleDeControle()
{
}
