#include <chrono>
#include <thread>
#include <vector>

#include "niveaux.hpp"
#include "catastrophe.hpp"

using namespace std;


void miseAJour(Centrale& centrale)
{
  centrale.majPressionEnceinte(); // met à jour la Pression subit par l'enceinte de Confinement
  centrale.majRadioactiviteEnceinte(); // met à jour la radioactivité de l'enceinte de confinement

  centrale.majEtatCentrale(); // met à jour l'état général de la centrale
  centrale.majProductionCentrale(); // met à jour la production générale de la centrale
  centrale.madProductionTotale();  //met à jour la production totale de la centrale

  centrale.majTempPressuriseurActuel();  // Modifie la température du pressuriseur actuel
  centrale.majPressionEau(); // Modifie la pression de l'eau
  centrale.majDebitEauPrim(); // Modifie le débit de l'eau
  centrale.majInertietemperaturePrim(); // Modifie l'inertie température eau circuit
  centrale.majTemperatureEau(); // Modifie la température de l'eau dans le circuit
  centrale.majRadioactivitePrim();  // Modifie la radioactivité du circuit

  centrale.majTemperatureVapeur();  // Modifie la température de la vapeur
  centrale.majPressionVapeur(); // Modifie la pression exercée par la vapeur
  centrale.majDebitEauSec(); // Modifie le débit de l'eau
  centrale.majDebitCondenseur();  // Modifie le débit au niveau du condenseur
  centrale.majDiffChaleurCondenseur();  // modifie la différence de chaleur entre l'entrée et la sortie du condenseur
  centrale.majInertieTemperatureSec(); // Modifie l'inertie température eau circuit
  centrale.majRadioactivite();  // Modifie la radioactivité du circuit

  centrale.majPropGrAct();
  centrale.majTauxBoreAct();
  centrale.majRadPiscine();
}


int niveau1(sdl2::window& fenetre, Centrale& centrale, SalleDeControle& salleDeControle, PosteDeSecurite& posteDeSecurite)
{
  salleDeControle.niveau(1);

  int nbTour = 0;
  vector<int> sortie = {0, 0}; // Premier : changement, second : fin session

  bool iskey_down = false;
  sdl2::event_queue queue;

  while (sortie[1] == 0)
  {
    while (sortie[0] == 0 && sortie[1] == 0) // Boucle salle de commande
    {
      auto start = chrono::system_clock::now();

      salleDeControle.majAffichage(fenetre, centrale);

      auto events = queue.pull_events();
      for ( const auto& e : events)
      {
        if (e->kind_of_event() == sdl2::event::quit)
          sortie[1] = 1;

        if ((e->kind_of_event() == sdl2::event::key_down) || (e->kind_of_event() == sdl2::event::key_up))
        {
          auto& key_ev = dynamic_cast<sdl2::event_keyboard&>(*e);

          if ((e->kind_of_event() == sdl2::event::key_down) &&  (iskey_down == false))
          {
            sortie = salleDeControle.majCommandes(fenetre, key_ev.code(), centrale);
            iskey_down = true;
          }
          if (key_ev.type_of_event() == sdl2::event::key_up)
            iskey_down = false;
        }
      }
      miseAJour(centrale);
      nbTour += 1;

      auto end = chrono::system_clock::now();
      chrono::duration<double> secondesEcoulees = end - start;
      int tps = 1000 - floor(secondesEcoulees.count()*1000);

      if (secondesEcoulees.count() < 1)
        this_thread::sleep_for(chrono::milliseconds(tps));
    }
    sortie[0] = 0;

    while (sortie[0] == 0 && sortie[1] == 0) // Boucle poste de securite
    {
      auto start = chrono::system_clock::now();

      posteDeSecurite.majAffichage(fenetre, centrale);

      auto events = queue.pull_events();
      for ( const auto& e : events)
      {
        if (e->kind_of_event() == sdl2::event::quit)
          sortie[1] = 1;

        if ((e->kind_of_event() == sdl2::event::key_down) || (e->kind_of_event() == sdl2::event::key_up))
        {
          auto& key_ev = dynamic_cast<sdl2::event_keyboard&>(*e);

          if ((e->kind_of_event() == sdl2::event::key_down) &&  (iskey_down == false))
          {
            sortie[0] = posteDeSecurite.majCommandes(fenetre, key_ev.code(), centrale);
            iskey_down = true;
          }
          if (key_ev.type_of_event() == sdl2::event::key_up)
            iskey_down = false;
        }
      }
      //miseAJour(centrale);
      nbTour += 1;

      auto end = chrono::system_clock::now();
      chrono::duration<double> secondesEcoulees = end - start;
      int tps = 1000 - floor(secondesEcoulees.count()*1000);

      if (secondesEcoulees.count() < 1)
        this_thread::sleep_for(chrono::milliseconds(tps));
    }

    sortie[0] = 0;
  }

  return nbTour;
}


int niveau2(sdl2::window& fenetre, Centrale& centrale, SalleDeControle& salleDeControle, PosteDeSecurite& posteDeSecurite)
{
  salleDeControle.niveau(2);

  int nbTour = 0;
  vector<int> sortie = {0, 0}; // Premier : changement, second : fin session
  bool finDispatching = false;

  bool quitter = false;
  bool iskey_down = false;
  sdl2::event_queue queue;

  while (not quitter && sortie[1] == 0 && not finDispatching)
  {
    while (not quitter && sortie[0] == 0 && sortie[1] == 0 && not finDispatching) // Boucle salle de commande
    {
      auto start = chrono::system_clock::now();

      salleDeControle.majAffichage(fenetre, centrale);

      auto events = queue.pull_events();
      for ( const auto& e : events)
      {
        if (e->kind_of_event() == sdl2::event::quit)
          quitter = true;

        if ((e->kind_of_event() == sdl2::event::key_down) || (e->kind_of_event() == sdl2::event::key_up))
        {
          auto& key_ev = dynamic_cast<sdl2::event_keyboard&>(*e);

          if ((e->kind_of_event() == sdl2::event::key_down) &&  (iskey_down == false))
          {
            sortie = salleDeControle.majCommandes(fenetre, key_ev.code(), centrale);
            iskey_down = true;
          }
          if (key_ev.type_of_event() == sdl2::event::key_up)
            iskey_down = false;
        }
      }
      miseAJour(centrale);
      finDispatching = salleDeControle.majdispatching(centrale);
      nbTour += 1;

      auto end = chrono::system_clock::now();
      chrono::duration<double> secondesEcoulees = end - start;
      int tps = 1000 - floor(secondesEcoulees.count()*1000);

      if (secondesEcoulees.count() < 1)
        this_thread::sleep_for(chrono::milliseconds(tps));
    }
    sortie[0] = 0;

    while (sortie[0] == 0 && sortie[1] == 0) // Boucle poste de securite
    {
      auto start = chrono::system_clock::now();

      posteDeSecurite.majAffichage(fenetre, centrale);

      auto events = queue.pull_events();
      for ( const auto& e : events)
      {
        if (e->kind_of_event() == sdl2::event::quit)
          sortie[1] = 1;

        if ((e->kind_of_event() == sdl2::event::key_down) || (e->kind_of_event() == sdl2::event::key_up))
        {
          auto& key_ev = dynamic_cast<sdl2::event_keyboard&>(*e);

          if ((e->kind_of_event() == sdl2::event::key_down) &&  (iskey_down == false))
          {
            sortie[0] = posteDeSecurite.majCommandes(fenetre, key_ev.code(), centrale);
            iskey_down = true;
          }
          if (key_ev.type_of_event() == sdl2::event::key_up)
            iskey_down = false;
        }
      }
      //miseAJour(centrale);
      nbTour += 1;

      auto end = chrono::system_clock::now();
      chrono::duration<double> secondesEcoulees = end - start;
      int tps = 1000 - floor(secondesEcoulees.count()*1000);

      if (secondesEcoulees.count() < 1)
        this_thread::sleep_for(chrono::milliseconds(tps));
    }
    sortie[0] = 0;
  }

  return nbTour;
}


int niveau3(sdl2::window& fenetre, Centrale& centrale, SalleDeControle& salleDeControle, PosteDeSecurite& posteDeSecurite)
{
  salleDeControle.niveau(2);

  int nbTour = 0, tourCatastrophe = 0;
  bool catastrophePossible = false;
  vector<int> sortie = {0, 0}; // Premier : changement, second : fin session
  bool finDispatching = false;

  bool quitter = false;
  bool iskey_down = false;
  sdl2::event_queue queue;

  while (not quitter && sortie[1] == 0 && not finDispatching)
  {
    while (not quitter && sortie[0] == 0 && sortie[1] == 0 && not finDispatching) // Boucle salle de commande
    {
      auto start = chrono::system_clock::now();

      salleDeControle.majAffichage(fenetre, centrale);

      auto events = queue.pull_events();
      for ( const auto& e : events)
      {
        if (e->kind_of_event() == sdl2::event::quit)
          quitter = true;

        if ((e->kind_of_event() == sdl2::event::key_down) || (e->kind_of_event() == sdl2::event::key_up))
        {
          auto& key_ev = dynamic_cast<sdl2::event_keyboard&>(*e);

          if ((e->kind_of_event() == sdl2::event::key_down) &&  (iskey_down == false))
          {
            sortie = salleDeControle.majCommandes(fenetre, key_ev.code(), centrale);
            iskey_down = true;
          }
          if (key_ev.type_of_event() == sdl2::event::key_up)
            iskey_down = false;
        }
      }
      miseAJour(centrale);
      finDispatching = salleDeControle.majdispatching(centrale);

      if(centrale.productionCentrale() >= 900)
        catastrophePossible = true;

      if(catastrophePossible == true)
      {
        if(tourCatastrophe%10 == 0)
          catastrophe(centrale);

        tourCatastrophe +=1;
      }

      nbTour += 1;

      auto end = chrono::system_clock::now();
      chrono::duration<double> secondesEcoulees = end - start;
      int tps = 1000 - floor(secondesEcoulees.count()*1000);

      if (secondesEcoulees.count() < 1)
        this_thread::sleep_for(chrono::milliseconds(tps));
    }
    sortie[0] = 0;

    while (sortie[0] == 0 && sortie[1] == 0) // Boucle poste de securite
    {
      auto start = chrono::system_clock::now();

      posteDeSecurite.majAffichage(fenetre, centrale);

      auto events = queue.pull_events();
      for ( const auto& e : events)
      {
        if (e->kind_of_event() == sdl2::event::quit)
          sortie[1] = 1;

        if ((e->kind_of_event() == sdl2::event::key_down) || (e->kind_of_event() == sdl2::event::key_up))
        {
          auto& key_ev = dynamic_cast<sdl2::event_keyboard&>(*e);

          if ((e->kind_of_event() == sdl2::event::key_down) &&  (iskey_down == false))
          {
            sortie[0] = posteDeSecurite.majCommandes(fenetre, key_ev.code(), centrale);
            iskey_down = true;
          }
          if (key_ev.type_of_event() == sdl2::event::key_up)
            iskey_down = false;
        }
      }
      //miseAJour(centrale);

      if(centrale.productionCentrale() >= 900)
        catastrophePossible = true;

      if(catastrophePossible == true)
      {
        if(tourCatastrophe%10 == 0)
          catastrophe(centrale);

        tourCatastrophe +=1;
      }

      nbTour += 1;

      auto end = chrono::system_clock::now();
      chrono::duration<double> secondesEcoulees = end - start;
      int tps = 1000 - floor(secondesEcoulees.count()*1000);

      if (secondesEcoulees.count() < 1)
        this_thread::sleep_for(chrono::milliseconds(tps));
    }
    sortie[0] = 0;
  }

  return nbTour;
}


int menu(sdl2::window& fenetre)
{
  bool entrer = false;
  int position = 0;

  auto [wph, hph] = fenetre.dimensions();
  double coordx = 0.65*wph;
  vector<double> coordy = {0.36*hph, 0.46*hph, 0.56*hph, 0.66*hph};

  sdl2::image image("image/Menu.jpg", fenetre);
  sdl2::image fleche("image/Fleche.jpg", fenetre);
  image.stretch({wph,hph});
  fleche.stretch({30,40});

  bool quitter = false;
  bool iskey_down = false;
  sdl2::event_queue queue;

  while(not quitter && entrer == false)
  {
    fleche.at(coordx, coordy[position]);
    fenetre << image << fleche << sdl2::flush;

    auto events = queue.pull_events();
    for ( const auto& e : events)
    {
      if (e->kind_of_event() == sdl2::event::quit)
      {
        quitter = true;
        position = -1;
      }

      if ((e->kind_of_event() == sdl2::event::key_down) || (e->kind_of_event() == sdl2::event::key_up))
      {
        auto& key_ev = dynamic_cast<sdl2::event_keyboard&>(*e);

        if ((e->kind_of_event() == sdl2::event::key_down) &&  (iskey_down == false))
        {
          if(key_ev.code() == sdl2::event_keyboard::up)
          {
            if(position > 0)
              position -= 1;
            else
              position = 0;
          }

          if(key_ev.code() == sdl2::event_keyboard::down)
          {
            if(position < 3)
              position += 1;
            else
              position = 3;
          }

          if(key_ev.code() == 13)
            entrer = true;

          iskey_down = true;
        }
        if (key_ev.type_of_event() == sdl2::event::key_up)
          iskey_down = false;
      }
    }
  }

  return position + 1;
}


void affichageEtats(sdl2::window& fenetre, Centrale& centrale)
{
  auto [wph, hph] = fenetre.dimensions();
  sdl2::font fonte_texte("./data/Simpsonfont.otf",27);

  double etatCentrale = centrale.etatCentrale();
  double etatReacteur = (centrale.etatCuve() + centrale.etatPiscine()  + centrale.etatBarresGr() + centrale.etatCanaux() + centrale.etatInjBore())/5;
  double etatCircuitPrim = (centrale.etatCircuitPrim() + centrale.etatPompePrim() + centrale.etatPressuriseur() + centrale.etatResistancePressuriseur() + centrale.etatEchangeurChaleur())/5;
  double etatCircuitSec = (centrale.etatCircuitSec() + centrale.etatPompeSec() + centrale.etatGenerateurVapeur() + centrale.etatCondenseur())/4;

  string sEtatCentrale (to_string(etatCentrale));
  string sEtatReacteur (to_string(etatReacteur));
  string sEtatCircuitPrim (to_string(etatCircuitPrim));
  string sEtatCircuitSec (to_string(etatCircuitSec));

  sEtatCentrale.erase(4,5);
  sEtatReacteur.erase(4,5);
  sEtatCircuitPrim.erase(4,5);
  sEtatCircuitSec.erase(4,5);

  sdl2::texte texteEtatCentrale("ETAT  DE  LA  CENTRALE : " + sEtatCentrale, fonte_texte, fenetre, {255,244,0,0});
  sdl2::texte texteEtatReacteur("ETAT  DU  REACTEUR : " + sEtatReacteur, fonte_texte, fenetre, {255,244,0,0});
  sdl2::texte texteEtatCircuitPrim("ETAT  DU  CIRCUIT  PRIMAIRE : " + sEtatCircuitPrim, fonte_texte, fenetre, {255,244,0,0});
  sdl2::texte texteEtatCircuitSec("ETAT  DU  CIRCUIT  SECONDAIRE : " + sEtatCircuitSec, fonte_texte, fenetre, {255,244,0,0});

  texteEtatCentrale.at(0.28*wph,0.36*hph);
  texteEtatReacteur.at(0.28*wph,0.44*hph);
  texteEtatCircuitPrim.at(0.28*wph,0.52*hph);
  texteEtatCircuitSec.at(0.28*wph,0.6*hph);

  fenetre << texteEtatCentrale << texteEtatReacteur << texteEtatCircuitPrim << texteEtatCircuitSec;

  if(etatCentrale > 0.8)
  {
    sdl2::texte texteEtat("LA  CENTRALE  EST  EN  BON  ETAT  !", fonte_texte, fenetre, {210,200,0,0});
    texteEtat.at(0.3*wph, 0.68*hph);
    fenetre << texteEtat;
  }

  if(etatCentrale<=0.8 && etatCentrale>0.5)
  {
    sdl2::texte texteEtat("→  LA CENTRALE EST ASSEZ ENDOMMAGEES !", fonte_texte, fenetre, {210,200,0,0});
    texteEtat.at(0.3*wph, 0.68*hph);
    fenetre << texteEtat;
  }

  if(etatCentrale<=0.5 && etatCentrale>0.2)
  {
    sdl2::texte texteEtat("LA  CENTRALE  EST  PRESQUE  DETRUITE  !", fonte_texte, fenetre, {210,200,0,0});
    texteEtat.at(0.3*wph, 0.68*hph);
    fenetre << texteEtat;
  }

  if(etatCentrale <= 0.2)
  {
    sdl2::texte texteEtat("LA  CENTRALE  EST  DETRUITE  !", fonte_texte, fenetre, {210,200,0,0});
    texteEtat.at(0.3*wph, 0.68*hph);
    fenetre << texteEtat;
  }
}


void affichageProduction(sdl2::window& fenetre, Centrale& centrale, int nbTour)
{
  auto [wph, hph] = fenetre.dimensions();
  sdl2::font fonte_texte("./data/Simpsonfont.otf",27);

  int productionTot = centrale.productionTotale();
  int productionMoy = productionTot/nbTour;

  string sProductionTot (to_string(productionTot));
  string sProductionMoy (to_string(productionMoy));

  sdl2::texte texteProductionTot("PRODUCTION  TOTALE  ELECTRICITE : " + sProductionTot + "  MW", fonte_texte, fenetre, {255,244,0,0});
  sdl2::texte texteProductionMoy("PRODUCTION  MOYENNE  ELECTRICITE : " + sProductionMoy + "  MW", fonte_texte, fenetre, {255,244,0,0});

  texteProductionTot.at(0.25*wph,0.44*hph);
  texteProductionMoy.at(0.25*wph,0.52*hph);
  fenetre << texteProductionTot << texteProductionMoy;

  if(productionMoy < 300)
  {
    sdl2::texte texteProduction("PRODUCTION  FAIBLE !", fonte_texte, fenetre, {210,200,0,0});
    texteProduction.at(0.3*wph,0.6*hph);
    fenetre << texteProduction;
  }

  if(productionMoy>=300  && productionMoy<900)
  {
    sdl2::texte texteProduction("PrRODUCTION  PEU  RENTABLE !", fonte_texte, fenetre, {210,200,0,0});
    texteProduction.at(0.3*wph,0.6*hph);
    fenetre << texteProduction;
  }

  if(productionMoy>=900  && productionMoy<1200)
  {
    sdl2::texte texteProduction("PRODUCTION  CORRECTE !", fonte_texte, fenetre, {210,200,0,0});
    texteProduction.at(0.3*wph,0.6*hph);
    fenetre << texteProduction;
  }

  if(productionMoy>=1200  && productionMoy<1400)
  {
    sdl2::texte texteProduction("PRODUCTION  EXCELLENTE !", fonte_texte, fenetre, {210,200,0,0});
    texteProduction.at(0.3*wph,0.6*hph);
    fenetre << texteProduction;
  }

  if(productionMoy >= 1400)
  {
    sdl2::texte texteProduction("PRODUCTION HORS NORME !", fonte_texte, fenetre, {210,200,0,0});
    texteProduction.at(0.3*wph,0.6*hph);
    fenetre << texteProduction;
  }
}


void affichageRadioactivite(sdl2::window& fenetre, Centrale& centrale)
{
  auto [wph, hph] = fenetre.dimensions();
  sdl2::font fonte_texte("./data/Simpsonfont.otf",27);

  int radioactiviteEnceinte = centrale.radioactiviteEnceinte();
  int radioactivitePrim = centrale.radioactivitePrim();
  int radioactiviteSec = centrale.radioactiviteSec();
  int radioactiviteEau = centrale.radioactiviteEau();
  int contamination = centrale.contamination();
  int radioactiviteAir = centrale.radioactiviteAir();

  string sRadioactiviteEnceinte (to_string(radioactiviteEnceinte));
  string sRadioactivitePrim (to_string(radioactivitePrim));
  string sRadioactiviteSec (to_string(radioactiviteSec));
  string sRadioactiviteEau (to_string(radioactiviteEau));
  string sRadioactiviteAir (to_string(radioactiviteAir));
  string sContamination (to_string(contamination));

  sdl2::texte texteRadioactiviteEnceinte("RADIOACTIVITE  ENCEINTE : " + sRadioactiviteEnceinte + "  rem/h", fonte_texte, fenetre, {255,244,0,0});
  sdl2::texte texteRadioactivitePrim("RADIOACTIVITE  CIRCUIT  PRIMAIRE : " + sRadioactivitePrim + "  becquerel", fonte_texte, fenetre, {255,244,0,0});
  sdl2::texte texteRadioactiviteSec("RADIOACTIVITE  CIRCUIT  SECONDAIRE : " + sRadioactiviteSec + "  becquerel", fonte_texte, fenetre, {255,244,0,0});

  sdl2::texte texteRadioactiviteEau("RADIOACTIVITE  EAU  AUTOUR  CENTRALE : " + sRadioactiviteEau + "  rem/h", fonte_texte, fenetre, {255,244,0,0});
  sdl2::texte texteRadioactiviteAir("RADIOACTIVITE  AIR  AUTOUR  CENTRALE : " + sRadioactiviteAir + "  rem/h", fonte_texte, fenetre, {255,244,0,0});
  sdl2::texte texteContamination("CONTAMINATION  POPULATION : " + sContamination, fonte_texte, fenetre, {255,244,0,0});

  texteRadioactiviteEnceinte.at(0.28*wph,0.36*hph);
  texteRadioactivitePrim.at(0.28*wph,0.44*hph);
  texteRadioactiviteSec.at(0.28*wph,0.52*hph);
  texteRadioactiviteEau.at(0.28*wph,0.6*hph);
  texteRadioactiviteAir.at(0.28*wph,0.68*hph);
  texteContamination.at(0.28*wph,0.76*hph);

  fenetre << texteRadioactiviteEnceinte << texteRadioactivitePrim << texteRadioactiviteSec << texteRadioactiviteEau << texteRadioactiviteAir << texteContamination;
}


void affichageScore(sdl2::window& fenetre, SalleDeControle& salleDeControle)
{
  auto [wph, hph] = fenetre.dimensions();
  sdl2::font fonte_texte("./data/Simpsonfont.otf",27);

  int score = salleDeControle.scoreDispatching();

  string sScore (to_string(score));

  sdl2::texte texteScoreDispatching("SCORE  DU  DISPATCHING  NATIONAL : " + sScore, fonte_texte, fenetre, {255,244,0,0});
  texteScoreDispatching.at(0.28*wph,0.5*hph);
  fenetre << texteScoreDispatching;

  if(score > 8)
  {
    sdl2::texte texteScore("PERFORMANCES  CORECTES !", fonte_texte, fenetre, {210,200,0,0});
    texteScore.at(0.3*wph,0.58*hph);
    fenetre << texteScore;
  }

  if(score<=8 && score>5)
  {
    sdl2::texte texteScore("PERFORMANCES  MOYENNES !", fonte_texte, fenetre, {210,200,0,0});
    texteScore.at(0.3*wph,0.58*hph);
    fenetre << texteScore;
  }

  if(score <= 5)
  {
    sdl2::texte texteScore("PERFORMANCES  DECEVANTE !", fonte_texte, fenetre, {210,200,0,0});
    texteScore.at(0.3*wph,0.58*hph);
    fenetre << texteScore;
  }
}


void bilan(sdl2::window& fenetre, Centrale& centrale, SalleDeControle& salleDeControle, int niveau, int nbTour)
{
  auto [wph, hph] = fenetre.dimensions();
  sdl2::image image("image/Bilan.jpg", fenetre);
  image.stretch({wph,hph});

  int fenetreActuelle = 1;

  bool quitter = false;
  bool iskey_down = false;
  sdl2::event_queue queue;

  while (not quitter)
  {
    fenetre << image;

    switch(fenetreActuelle)
    {
      case 1 :
        affichageEtats(fenetre, centrale);
        break;

      case 2 :
        affichageProduction(fenetre,centrale, nbTour);
        break;

      case 3 :
        affichageRadioactivite(fenetre, centrale);
        break;

      case 4 :
        affichageScore(fenetre, salleDeControle);
        break;
    }

    fenetre << sdl2::flush;

    auto events = queue.pull_events();
    for ( const auto& e : events)
    {
      if (e->kind_of_event() == sdl2::event::quit)
        quitter = true;

      if ((e->kind_of_event() == sdl2::event::key_down) || (e->kind_of_event() == sdl2::event::key_up))
      {
        auto& key_ev = dynamic_cast<sdl2::event_keyboard&>(*e);

        if ((e->kind_of_event() == sdl2::event::key_down) &&  (iskey_down == false))
        {
          if(key_ev.code() == 13)
            quitter = true;

          if(key_ev.code() == sdl2::event_keyboard::up)
          {
            if(fenetreActuelle > 1)
              fenetreActuelle -= 1;
          }

          if(key_ev.code() == sdl2::event_keyboard::down)
          {
            if(niveau == 1)
            {
              if(fenetreActuelle < 3)
                fenetreActuelle += 1;
            }
            else
            {
              if(fenetreActuelle < 4)
                fenetreActuelle += 1;
            }
          }

          iskey_down = true;
        }
        if (key_ev.type_of_event() == sdl2::event::key_up)
          iskey_down = false;
      }
    }
  }
}


void jeu()
{
  int x = 1400;
  int y = 750;

  sdl2::window fenetre("Nuclear Alert", {x,y});

  Centrale centrale;
  SalleDeControle salleDeControle;
  PosteDeSecurite posteDeSecurite;

  int niveau = menu(fenetre);
  int nbTour = 1;

  if(niveau == 1) //49
  {
    nbTour = niveau1(fenetre,centrale,salleDeControle,posteDeSecurite);
    bilan(fenetre,centrale,salleDeControle,niveau,nbTour);
  }

  if(niveau == 2) //50
  {
    nbTour = niveau2(fenetre,centrale,salleDeControle,posteDeSecurite);
    bilan(fenetre,centrale,salleDeControle,niveau,nbTour);
  }

  if(niveau == 3) //51
  {
    nbTour = niveau3(fenetre,centrale,salleDeControle,posteDeSecurite);
    bilan(fenetre,centrale,salleDeControle,niveau,nbTour);
  }
}
