#include <chrono>
#include <thread>

#include "niveaux.hpp"

using namespace std;


void miseAJour(Centrale& centrale, SalleDeControle& salleDeControle)
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


int niveau1(sdl2::window fenetre, Centrale& centrale, SalleDeControle& salleDeControle)
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
      miseAJour(centrale, salleDeControle);

      auto end = chrono::system_clock::now();
      chrono::duration<double> secondesEcoulees = end - start;
      int tps = 1000 - floor(secondesEcoulees.count()*1000);

      if (secondesEcoulees.count() < 1)
        this_thread::sleep_for(chrono::milliseconds(tps));

      nbTour += 1;
    }
    sortie[0] = 0;
  }

  return nbTour;
}


int niveau2(sdl2::window fenetre, Centrale& centrale, SalleDeControle& salleDeControle)
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
      miseAJour(centrale, salleDeControle);
      finDispatching = salleDeControle.majdispatching(centrale);


      auto end = chrono::system_clock::now();
      chrono::duration<double> secondesEcoulees = end - start;
      int tps = 1000 - floor(secondesEcoulees.count()*1000);

      if (secondesEcoulees.count() < 1)
        this_thread::sleep_for(chrono::milliseconds(tps));

      nbTour += 1;
    }
  }

  return nbTour;
}


int menu(sdl2::window fenetre)
{
  int niveau = 0;
  bool touche = false;

  sdl2::image image("image/Menu.jpg", fenetre);

  auto [wph, hph] = fenetre.dimensions();
  image.stretch({wph,hph});

  fenetre << image << sdl2::flush;

  bool quitter = false;
  bool iskey_down = false;
  sdl2::event_queue queue;

  while(not quitter && touche == false)
  {
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
          if(key_ev.code()==49 ||key_ev.code()==50 || key_ev.code()==51)
          {
            niveau = key_ev.code();
            touche = true;
          }
          iskey_down = true;
        }
        if (key_ev.type_of_event() == sdl2::event::key_up)
          iskey_down = false;
      }
    }
  }

  return niveau;
}


void bilan(sdl2::window fenetre, Centrale& centrale, SalleDeControle& salleDeControle, int niveau, int nbTour)
{
  double etatCentrale = centrale.etatCentrale();
  double etatReacteur = (centrale.etatCuve() + centrale.etatPiscine()  + centrale.etatBarresGr() + centrale.etatCanaux() + centrale.etatInjBore())/5;
  double etatCircuitPrim = (centrale.etatCircuitPrim() + centrale.etatPompePrim() + centrale.etatPressuriseur() + centrale.etatResistancePressuriseur() + centrale.etatEchangeurChaleur())/5;
  double etatCircuitSec = (centrale.etatCircuitSec() + centrale.etatPompeSec() + centrale.etatGenerateurVapeur() + centrale.etatCondenseur())/4;
  int productionMoy = centrale.productionTotale()/nbTour;

  int score = salleDeControle.scoreDispatching();

  int radioactiviteEnceinte = centrale.radioactiviteEnceinte();
  int radioactivitePrim = centrale.radioactivitePrim();
  int radioactiviteSec = centrale.radioactiviteSec();
  int radioactiviteEau = centrale.radioactiviteEau();
  int contamination = centrale.contamination();
  int radioactiviteAir = centrale.radioactiviteAir();

  auto [wph, hph] = fenetre.dimensions();
  sdl2::font fonte_texte("./data/Lato-Bold.ttf",20);

  sdl2::image image("image/Bilan.jpg", fenetre);
  image.stretch({wph,hph});
  fenetre << image;


  // Etats
  string sEtatCentrale (to_string(etatCentrale));
  string sEtatReacteur (to_string(etatReacteur));
  string sEtatCircuitPrim (to_string(etatCircuitPrim));
  string sEtatCircuitSec (to_string(etatCircuitSec));

  sEtatCentrale.erase(4,5);
  sEtatReacteur.erase(4,5);
  sEtatCircuitPrim.erase(4,5);
  sEtatCircuitSec.erase(4,5);

  sdl2::texte texteEtatCentrale("Etat de la centrale : " + sEtatCentrale, fonte_texte, fenetre, {0x00,0x00,0x00,0x00});
  sdl2::texte texteEtatReacteur("Etat du réacteur : " + sEtatReacteur, fonte_texte, fenetre, {0x00,0x00,0x00,0x00});
  sdl2::texte texteEtatCircuitPrim("Etat du circuit primaire : " + sEtatCircuitPrim, fonte_texte, fenetre, {0x00,0x00,0x00,0x00});
  sdl2::texte texteEtatCircuitSec("Etat du circuit secondaire : " + sEtatCircuitSec, fonte_texte, fenetre, {0x00,0x00,0x00,0x00});

  texteEtatCentrale.at(0.1*wph,0.2*hph);
  texteEtatReacteur.at(0.1*wph,0.23*hph);
  texteEtatCircuitPrim.at(0.1*wph,0.26*hph);
  texteEtatCircuitSec.at(0.1*wph,0.29*hph);

  fenetre << texteEtatCentrale << texteEtatReacteur << texteEtatCircuitPrim << texteEtatCircuitSec;

  if(etatCentrale > 0.8)
  {
    sdl2::texte texteEtat("→ La centrale est en bon état !", fonte_texte, fenetre, {0xFF,0x00,0x00,0x00});
    texteEtat.at(0.15*wph, 0.34*hph);
    fenetre << texteEtat;
  }

  if(etatCentrale<=0.8 && etatCentrale>0.5)
  {
    sdl2::texte texteEtat("→ La centrale est assez endommagée !", fonte_texte, fenetre, {0xFF,0x00,0x00,0x00});
    texteEtat.at(0.15*wph, 0.34*hph);
    fenetre << texteEtat;
  }

  if(etatCentrale<=0.5 && etatCentrale>0.2)
  {
    sdl2::texte texteEtat("→ La centrale est presque détruite !", fonte_texte, fenetre, {0xFF,0x00,0x00,0x00});
    texteEtat.at(0.15*wph, 0.34*hph);
    fenetre << texteEtat;
  }

  if(etatCentrale <= 0.2)
  {
    sdl2::texte texteEtat("→ La centrale est détruite !", fonte_texte, fenetre, {0xFF,0x00,0x00,0x00});
    texteEtat.at(0.15*wph, 0.34*hph);
    fenetre << texteEtat;
  }


  // Production moyenne
  string sProductionMoy (to_string(productionMoy));

  sdl2::texte texteProductionMoy("Production moyenne d'électricité : " + sProductionMoy + " MW", fonte_texte, fenetre, {0x00,0x00,0x00,0x00});
  texteProductionMoy.at(0.6*wph,0.3*hph);
  fenetre << texteProductionMoy;

  if(productionMoy < 300)
  {
    sdl2::texte texteProduction("→ Production faible !", fonte_texte, fenetre, {0xFF,0x00,0x00,0x00});
    texteProduction.at(0.65*wph,0.35*hph);
    fenetre << texteProduction;
  }

  if(productionMoy>=300  && productionMoy<900)
  {
    sdl2::texte texteProduction("→ Production peu rentable !", fonte_texte, fenetre, {0xFF,0x00,0x00,0x00});
    texteProduction.at(0.65*wph,0.35*hph);
    fenetre << texteProduction;
  }

  if(productionMoy>=900  && productionMoy<1200)
  {
    sdl2::texte texteProduction("→ Production correcte !", fonte_texte, fenetre, {0xFF,0x00,0x00,0x00});
    texteProduction.at(0.65*wph,0.35*hph);
    fenetre << texteProduction;
  }

  if(productionMoy>=1200  && productionMoy<1400)
  {
    sdl2::texte texteProduction("→ Production excellente !", fonte_texte, fenetre, {0xFF,0x00,0x00,0x00});
    texteProduction.at(0.65*wph,0.35*hph);
    fenetre << texteProduction;
  }

  if(productionMoy >= 1400)
  {
    sdl2::texte texteProduction("→ Production hors norme !", fonte_texte, fenetre, {0xFF,0x00,0x00,0x00});
    texteProduction.at(0.65*wph,0.35*hph);
    fenetre << texteProduction;
  }


  // Radioactivités
  string sRadioactiviteEnceinte (to_string(radioactiviteEnceinte));
  string sRadioactivitePrim (to_string(radioactivitePrim));
  string sRadioactiviteSec (to_string(radioactiviteSec));
  string sRadioactiviteEau (to_string(radioactiviteEau));
  string sRadioactiviteAir (to_string(radioactiviteAir));
  string sContamination (to_string(contamination));

  sdl2::texte texteRadioactiviteEnceinte("Radioactivité de l'enceinte : " + sRadioactiviteEnceinte + " rem/h", fonte_texte, fenetre, {0x00,0x00,0x00,0x00});
  sdl2::texte texteRadioactivitePrim("Radioactivité du circuit primaire : " + sRadioactivitePrim + " becquerel", fonte_texte, fenetre, {0x00,0x00,0x00,0x00});
  sdl2::texte texteRadioactiviteSec("Radioactivité du circuit secondaire : " + sRadioactiviteSec + " becquerel", fonte_texte, fenetre, {0x00,0x00,0x00,0x00});

  sdl2::texte texteRadioactiviteEau("Radioactivité de l'eau autour de la centrale : " + sRadioactiviteEau + " rem/h", fonte_texte, fenetre, {0x00,0x00,0x00,0x00});
  sdl2::texte texteRadioactiviteAir("Radioactivité de l'air autour de la centrale : " + sRadioactiviteAir + " rem/h", fonte_texte, fenetre, {0x00,0x00,0x00,0x00});
  sdl2::texte texteContamination("Contamination de la population : " + sContamination, fonte_texte, fenetre, {0x00,0x00,0x00,0x00});

  texteRadioactiviteEnceinte.at(0.1*wph,0.6*hph);
  texteRadioactivitePrim.at(0.1*wph,0.64*hph);
  texteRadioactiviteSec.at(0.1*wph,0.68*hph);
  texteRadioactiviteEau.at(0.1*wph,0.72*hph);
  texteRadioactiviteAir.at(0.1*wph,0.76*hph);
  texteContamination.at(0.1*wph,0.8*hph);

  fenetre << texteRadioactiviteEnceinte << texteRadioactivitePrim << texteRadioactiviteSec << texteRadioactiviteEau << texteRadioactiviteAir << texteContamination;


  // Score Dispatching
  if(niveau == 50)
  {
    string sScore (to_string(score));

    sdl2::texte texteScoreDispatching("Production moyenne d'électricité : " + sScore, fonte_texte, fenetre, {0x00,0x00,0x00,0x00});
    texteScoreDispatching.at(0.6*wph,0.6*hph);
    fenetre << texteScoreDispatching;

    if(score > 8)
    {
      sdl2::texte texteScore("→ Performences correctes !", fonte_texte, fenetre, {0xFF,0x00,0x00,0x00});
      texteScore.at(0.65*wph,0.65*hph);
      fenetre << texteScore;
    }

    if(score<=8 && score>5)
    {
      sdl2::texte texteScore("→ Performences moyennes !", fonte_texte, fenetre, {0xFF,0x00,0x00,0x00});
      texteScore.at(0.65*wph,0.65*hph);
      fenetre << texteScore;
    }

    if(score <= 5)
    {
      sdl2::texte texteScore("→ Performences décevantes !", fonte_texte, fenetre, {0xFF,0x00,0x00,0x00});
      texteScore.at(0.65*wph,0.65*hph);
      fenetre << texteScore;
    }
  }

  fenetre << sdl2::flush;
  this_thread::sleep_for(chrono::seconds(2));
}


void jeu()
{
  sdl2::window fenetreMenu("Nuclear Alert menu", {1400,750});

  Centrale centrale;
  SalleDeControle salleDeControle;

  int niveau = menu(fenetreMenu);
  int nbTour = 1;

  if(niveau == 49)
  {
    sdl2::window fenetreJeu("Nuclear Alert", {1400,750});
    nbTour = niveau1(fenetreJeu,centrale,salleDeControle);

    sdl2::window fenetreBilan("Nuclear Alert bilan", {1400,750});
    bilan(fenetreBilan,centrale,salleDeControle,niveau,nbTour);
  }

  if(niveau == 50)
  {
    sdl2::window fenetreJeu("Nuclear Alert", {1400,750});
    nbTour = niveau2(fenetreJeu,centrale,salleDeControle);

    sdl2::window fenetreBilan("Nuclear Alert bilan", {1400,750});
    bilan(fenetreBilan,centrale,salleDeControle,niveau,nbTour);
  }

  /*if(niveau == 51)
  {
    sdl2::window fenetreJeu("Nuclear Alert", {1400,750});
    nbTour = niveau3(fenetreJeu,centrale,salleDeControle);

    sdl2::window fenetreBilan("Nuclear Alert bilan", {1400,750});
    bilan(fenetreBilan,centrale,salleDeControle,niveau,nbTour);
  }*/
}
