#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <random>
#include <vector>

#include "salle_de_controle.hpp"

using namespace std;


/* Constructeur */
SalleDeControle::SalleDeControle() : m_schemaCentrale(false), m_niveau(1)
{
}

/* Permet de connaitre le niveau du jeu pour le dispatching (niveau1 : pas de dispatching) */
void SalleDeControle::niveau(int niveau)
{
  m_niveau = niveau;
}


/* Affiche les différents textes et images de la salle de controle */
void SalleDeControle::majAffichage(sdl2::window& fenetre, Centrale& centrale)
{
  cadre(fenetre); // Affiche l'image de font
  dispatching.affichageDispatching(fenetre, centrale, m_niveau);  // Affiche le dispatching
  securite.affichageSecurite(fenetre, centrale);  // Affiche les message de sécurité & alertes
  affichageProdElec(fenetre, centrale); // Affiche la production d'électricité
  afficheTauxBorePiscine(fenetre, centrale);  // Affiche le taux de bore dans la piscine
  afficheCircuitPrim(fenetre, centrale);  // Affiche les différentes composantes du circuit primaire
  afficheCircuitSec(fenetre, centrale);  // Affiche les différentes composantes du circuit secondaire
  affichePressionEnceinte(fenetre, centrale); // Affiche la pression dans l'enceinte
  afficheSystRefroidissement(fenetre, centrale);  // Affiche les différentes composantes du système de refroidissement
  afficheEtatBarreGraphite(fenetre, centrale);  // Affiche l'état des barres de graphite

  if(m_schemaCentrale == true)
    affichageSchemaCentrale(fenetre, centrale); // Affiche le schéma de la centrale

  fenetre << sdl2::flush; // Met a jour la fentre graphique
}


/* Affiche l'image de font */
void SalleDeControle::cadre(sdl2::window& fenetre) const
{
  sdl2::image cadre("image/Salle de contrôle.jpg", fenetre); // Initialisation de l'image de font

  auto [wph, hph] = fenetre.dimensions(); // Donne la taile de la fenetre graphique
  cadre.stretch({wph,hph}); // Taille de l'image de font

  fenetre << cadre; // Affiche sur la fenetre
}


/* Affiche la production d'électricité de la centrale */
void SalleDeControle::affichageProdElec(sdl2::window& fenetre, Centrale& centrale) const
{
  int production = centrale.productionCentrale(); //donne la production de la centrale

  string sProduction(to_string(production));  // conversion du int en string

  auto [wph, hph] = fenetre.dimensions(); // Donne la taille de la fenetre graphique
  sdl2::font fonte_texte("./data/Welbut__.ttf",15); // Initialisation de la fonte du texte
  sdl2::texte texteProduction("Production électrique : " + sProduction + " MW", fonte_texte, fenetre, {0x00,0x00,0x00,0x00}); // Initialisation du texte
  texteProduction.at(0.415*wph,0.195*hph);  // Emplacement du texte

  fenetre << texteProduction; // Affiche sur la fenetre
}


/* Affiche le taux de bore dans la piscine */
void SalleDeControle::afficheTauxBorePiscine(sdl2::window& fenetre, Centrale& centrale) const
{
  // Récupération des valeurs
  double boreAct = centrale.tauxBoreActuel();
  double boreDem = centrale.tauxBoreDemande();

  // Conversiondes double en string
  string sBoreAct(to_string(boreAct));
  string sBoreDem(to_string(boreDem));

  // Suppression des décimales des string car la conversion d'un double en string, donne un string avec 8 décimales
  sBoreAct.erase(4,5);
  sBoreDem.erase(4,5);

  auto [wph, hph] = fenetre.dimensions(); // Donne la taille de la fenetre graphique
  sdl2::font fonte_texte("./data/Welbut__.ttf",13); // Initialisation de la fonte du texte

  // Initialisation des textes
  sdl2::texte texteBoreAct("Taux de bore actuel dans la piscine : " + sBoreAct, fonte_texte, fenetre, {0x00,0x00,0x00,0x00});
  sdl2::texte texteBoreDem("Taux de bore demandé dans la piscine : " + sBoreDem, fonte_texte, fenetre, {0x00,0x00,0x00,0x00});

  // Emplacement des textes
  texteBoreAct.at(0.73*wph,0.395*hph);
  texteBoreDem.at(0.73*wph,0.4275*hph);

  fenetre << texteBoreAct << texteBoreDem;  // Affichage sur la fenetre
}


/* Affichage des composantes du circuit primaire */
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


/* Affichage des composantes du circuit secondaire */
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

  if(temperature < 120) // S'il n'y a pas de vapeur dans le circuit secondaire
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
  texteTemperature2.at(0.75*wph,0.2975*hph);

  if(temperature < 120)
    fenetre << texteRendement << texteTemperature1 << texteDebit << textePression << texteRadioactivite;
  else
    fenetre << texteRendement << texteTemperature2 << texteDebit << textePression << texteRadioactivite;
}


/* Affichage de la pression de l'enceinte */
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


/* Affichage du système de refroidissement */
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


/* Affichage de l'états et proportion demandée/actuelle des barres de graphite */
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

  // Initialisation des rectangles représentant la jauge de l'état des barres
  sdl2::rectangle r1({static_cast<short unsigned int>(0.515*wph),static_cast<short unsigned int>(0.855*hph)}, {static_cast<short unsigned int>(80 - 80*(1 - barresGr)),20}, {static_cast<uint8_t>(255*(1-barresGr)),static_cast<uint8_t>(255*barresGr),0}, true);
  sdl2::rectangle r2({static_cast<short unsigned int>(0.515*wph),static_cast<short unsigned int>(0.855*hph)}, {80,20}, {0,0,0,0}, false);

  sdl2::texte texteBarresGr("Etat des barres de graphite : " + sbarresGr + " %", fonte_texte, fenetre, {0x00,0x00,0x00,0x00});
  sdl2::texte texteProportionD("Proportion demandée de graphite hors de l'eau : " + sProportionD + " %", fonte_texte, fenetre, {0x00,0x00,0x00,0x00});
  sdl2::texte texteProportionA("Proportion actuelle de graphite hors de l'eau : " + sProportionA + " %", fonte_texte, fenetre, {0x00,0x00,0x00,0x00});

  texteBarresGr.at(0.35*wph,0.855*hph);
  texteProportionA.at(0.35*wph,0.89*hph);
  texteProportionD.at(0.35*wph,0.925*hph);

  fenetre << r1 << r2 << texteBarresGr << texteProportionD << texteProportionA;
}


/* Actionne les fonctionnalités des touches de la salle de contrôle */
vector<int> SalleDeControle::majCommandes(sdl2::window& fenetre, int touche, Centrale& centrale)
{
  vector<int> sortie = {0, 0};  // Premier : changement poste/salle, second : fin session

  switch (touche) // valeur de la touche enfoncée
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
    sortie[1] = finSession();
    break;

    case 9 :  // tab
    m_schemaCentrale = true;
    break;

    case 32 : // Espace
    sortie[0] = 1;
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


/* Met a jour le rendement de la pompe du circuit primaire */
void SalleDeControle::majRendementPompeCircuitPrim(sdl2::window& fenetre, Centrale& centrale)
{
  double rendement;

  bool quitter = false; // vaut true si la touche 'Entrée' est enfoncée, faux sinon
  bool iskey_down = false;  // Vaut faux si la touche n'est pas enfoncée, vrai sinon
  sdl2::event_queue queue;

  while (not quitter) // Tant que 'Entrée' n'est pas enfoncée
  {
    auto events = queue.pull_events();
    for (const auto& e : events) // On regarde chaque évènements(touche, clic, ...)
    {
      // Si l'évènement et de type 'clavier' et qu'il s'agit d'une touche enfoncée ou relevée
      if ((e->kind_of_event() == sdl2::event::key_down) || (e->kind_of_event() == sdl2::event::key_up))
      {
        auto& key_ev = dynamic_cast<sdl2::event_keyboard&>(*e);

        if ((e->kind_of_event() == sdl2::event::key_down) &&  (iskey_down == false)) // Si touche enfoncée et non relachée
        {
          switch (key_ev.code())  // Valeur de key_ev
          {
            case 13 : // Entrée
            quitter = true;
            break;

            case sdl2::event_keyboard::up : // Flèche du haut
            rendement = centrale.rendementPompePrim();
            centrale.majRendementPompePrim(rendement + 0.05);
            break;

            case sdl2::event_keyboard::down : // Flèche du bas
            rendement = centrale.rendementPompePrim();
            centrale.majRendementPompePrim(rendement - 0.05);
            break;
          }
          majAffichage(fenetre, centrale);  // Affichage textes/images salle de controle
          iskey_down = true;
        }
        if (key_ev.type_of_event() == sdl2::event::key_up)  // Si touche relachée
        iskey_down = false;
      }
    }
  }
}


/* Met a jour le rendement de la pompe du circuit secondaire */
void SalleDeControle::majRendementPompeCircuitSec(sdl2::window& fenetre, Centrale& centrale)
{
  double rendement;

  bool quitter = false; // vaut true si la touche 'Entrée' est enfoncée, faux sinon
  bool iskey_down = false;  // Vaut faux si la touche n'est pas enfoncée, vrai sinon
  sdl2::event_queue queue;

  while (not quitter) // Tant que 'Entrée' n'est pas enfoncée
  {
    auto events = queue.pull_events();
    for (const auto& e : events) // On regarde chaque évènements(touche, clic, ...)
    {
      // Si l'évènement et de type 'clavier' et qu'il s'agit d'une touche enfoncée ou relevée
      if ((e->kind_of_event() == sdl2::event::key_down) || (e->kind_of_event() == sdl2::event::key_up))
      {
        auto& key_ev = dynamic_cast<sdl2::event_keyboard&>(*e);

        if ((e->kind_of_event() == sdl2::event::key_down) &&  (iskey_down == false)) // Si touche enfoncée et non relachée
        {
          switch (key_ev.code())  // Valeur de key_ev
          {
            case 13 : // Entrée
            quitter = true;
            break;

            case sdl2::event_keyboard::up : // Flèche du haut
            rendement = centrale.rendementPompeSec();
            centrale.majRendementPompeSec(rendement + 0.05);
            break;

            case sdl2::event_keyboard::down : // Flèche du bas
            rendement = centrale.rendementPompeSec();
            centrale.majRendementPompeSec(rendement - 0.05);
            break;
          }
          majAffichage(fenetre, centrale);  // Affichage textes/images salle de controle
          iskey_down = true;
        }
        if (key_ev.type_of_event() == sdl2::event::key_up)  // Si touche relachée
        iskey_down = false;
      }
    }
  }
}


/* Met a jour la proportion des barres de controle */
void SalleDeControle::majBarreControle(sdl2::window& fenetre, Centrale& centrale)
{
  double barre;

  bool quitter = false; // vaut true si la touche 'Entrée' est enfoncée, faux sinon
  bool iskey_down = false;  // Vaut faux si la touche n'est pas enfoncée, vrai sinon
  sdl2::event_queue queue;

  while (not quitter) // Tant que 'Entrée' n'est pas enfoncée
  {
    auto events = queue.pull_events();
    for (const auto& e : events) // On regarde chaque évènements(touche, clic, ...)
    {
      // Si l'évènement et de type 'clavier' et qu'il s'agit d'une touche enfoncée ou relevée
      if ((e->kind_of_event() == sdl2::event::key_down) || (e->kind_of_event() == sdl2::event::key_up))
      {
        auto& key_ev = dynamic_cast<sdl2::event_keyboard&>(*e);

        if ((e->kind_of_event() == sdl2::event::key_down) &&  (iskey_down == false)) // Si touche enfoncée et non relachée
        {
          switch (key_ev.code())  // Valeur de key_ev
          {
            case 13 : // Entrée
            quitter = true;
            break;

            case sdl2::event_keyboard::up : // Flèche du haut
            barre = centrale.propGrDemande();
            centrale.majPropGrDemandee(barre + 0.05);
            break;

            case sdl2::event_keyboard::down : // Flèche du bas
            barre = centrale.propGrDemande();
            centrale.majPropGrDemandee(barre - 0.05);
            break;
          }
          majAffichage(fenetre, centrale);  // Affichage textes/images salle de controle
          iskey_down = true;
        }
        if (key_ev.type_of_event() == sdl2::event::key_up)  // Si touche relachée
        iskey_down = false;
      }
    }
  }
}


/* Met a jour le taux d'acide borique */
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


/* Met a jour le rendement du pressuriseur */
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


/* Met a jour le rendement de la pompe du condenseur */
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


/* Simule l'arrêt d'urgencede la centrale */
void SalleDeControle::arretUrgence(sdl2::window& fenetre, Centrale& centrale)
{
  double Ecuve = centrale.etatCuve();
  double Ecanaux = centrale.etatCanaux();
  double Ebarre = centrale.etatBarresGr();

  double probaReussite = 0.7*Ecuve*Ecanaux*Ebarre + 0.15;
  auto RND = ((float)(rand()))/((float)(RAND_MAX)); // Nombre réel aléatoire entre 0 et 1

  if(RND <= probaReussite)
  {
    centrale.majPropGrDemandee(0);
  }
  else
  {
    // Nombre réel aléatoire entre 0 et 1
    auto chance1 = ((float)(rand()))/((float)(RAND_MAX));
    auto chance2 = ((float)(rand()))/((float)(RAND_MAX));
    auto chance3 = ((float)(rand()))/((float)(RAND_MAX));

    auto RND1 = ((float)(rand()))/((float)(RAND_MAX))*0.1; // Nombre réel aléatoire entre 0 et 0.1
    auto RND2 = ((float)(rand()))/((float)(RAND_MAX))*0.08; // Nombre réel aléatoire entre 0 et 0.08
    auto RND3 = ((float)(rand()))/((float)(RAND_MAX))*0.08; // Nombre réel aléatoire entre 0 et 0.08

    if(chance1 <= 0.8)
      centrale.majEtatCanaux(Ecanaux - (0.05 + RND1));

    if(chance2 <= 0.3)
      centrale.majEtatBarresGr(Ebarre - (0.02 + RND2));

    if(chance3 <= 0.4)
      centrale.majEtatCuve(Ecuve - RND3);
  }
}


/* Arrête le jeu lorsque S est maintenue */
int SalleDeControle::finSession()
{
  bool iskey_down = true;
  sdl2::event_queue queue;

  chrono::time_point<chrono::system_clock> start, end;  // Initialisation de deux variables chrono
  start = chrono::system_clock::now();  // Prend l'heure qu'il est actuellement

  while (iskey_down == true)  // Tant que la touche 'S' est enfoncée
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
  end = chrono::system_clock::now();  // Prend l'heure qu'il est actuellement
  chrono::duration<double> secondesEcoulees = end - start;  // Différence entre l'heure de début et de fin

  if (secondesEcoulees.count() >= 0.75) // Si la touche 'S' a été enfoncé plus de 0.75 seconde
  return 1;

  return 0;
}


/* Affiche le schéma de la centrale */
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


/* Charge le schéma de la centrale et la fait clignoter */
void SalleDeControle::schemaCentrale(sdl2::window& fenetre, Centrale& centrale)
{
  // Donne la valeur des états
  double etatCentrale = centrale.etatCentrale();
  double etatReacteur = centrale.etatCuve();
  double etatCircuitPrim = centrale.etatCircuitPrim();
  double etatCircuitSec = centrale.etatCircuitSec();
  double etatCondenseur = centrale.etatCondenseur();

  auto [wph, hph] = fenetre.dimensions();

  // Image de toute la centrale
  sdl2::image schema("image/Centrale nucleaire.jpg", fenetre);
  schema.stretch({4*wph/6,4*hph/6});
  schema.at(wph/6,hph/6);

  // Image de la centrale en rouge
  sdl2::image centraleNucl("image/Centrale.png", fenetre);
  centraleNucl.stretch({4*wph/6,4*hph/6});
  centraleNucl.at(wph/6,hph/6);

  // Image du réacteur en rouge
  sdl2::image reacteur("image/Reacteur.png", fenetre);
  reacteur.stretch({4*wph/6,4*hph/6});
  reacteur.at(wph/6,hph/6);

  // Image du circuit primaire en rouge
  sdl2::image circuitPrim("image/Circuit_primaire.png", fenetre);
  circuitPrim.stretch({4*wph/6,4*hph/6});
  circuitPrim.at(wph/6,hph/6);

  // Image du circuit secondaire en rouge
  sdl2::image circuitSec("image/Circuit_secondaire.png", fenetre);
  circuitSec.stretch({4*wph/6,4*hph/6});
  circuitSec.at(wph/6,hph/6);

  // Image du circuit de refroidissement en rouge
  sdl2::image condenseur("image/Circuit_refroidissement.png", fenetre);
  condenseur.stretch({4*wph/6,4*hph/6});
  condenseur.at(wph/6,hph/6);

  fenetre << schema << sdl2::flush;

  this_thread::sleep_for(chrono::milliseconds(500));  // On attend 500 millisecondes avant de continuer

  if(etatCentrale < 0.5)
    fenetre << centraleNucl;

  if(etatReacteur < 0.5)
    fenetre << reacteur;

  if(etatCircuitPrim < 0.5)
    fenetre << circuitPrim;

  if(etatCircuitSec < 0.5)
    fenetre << circuitSec;

  if(etatCondenseur < 0.5)
    fenetre << condenseur;

  fenetre << sdl2::flush;

  this_thread::sleep_for(chrono::milliseconds(400));  // On attend 400 millisecondes avant de continuer
}


/* Met a jour le dispatching national */
bool SalleDeControle::majdispatching( Centrale& centrale)
{
  return dispatching.majdispatching(centrale);
}


/* Renvoie le score du dispatching national */
int SalleDeControle::scoreDispatching()
{
  return dispatching.scoreDispatching();
}


/* Destructeur */
SalleDeControle::~SalleDeControle()
{
}
