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

  salleDeControle.majdispatching(centrale);
}


void niveau1(sdl2::window fenetre, Centrale& centrale, SalleDeControle& salleDeControle)
{
  salleDeControle.niveau(1);

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
          sortie[1] = true;

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
    }
    sortie[0] = 0;
  }
}



void niveau2(sdl2::window fenetre, Centrale& centrale, SalleDeControle& salleDeControle)
{
  salleDeControle.niveau(2);

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
          sortie[1] = true;

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
      sortie[1] = salleDeControle.finDispatching();

      auto end = chrono::system_clock::now();
      chrono::duration<double> secondesEcoulees = end - start;
      int tps = 1000 - floor(secondesEcoulees.count()*1000);

      if (secondesEcoulees.count() < 1)
        this_thread::sleep_for(chrono::milliseconds(tps));
    }
  }
}




int menu()
{
  int niveau = 0;
  bool touche = false;

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


void bilan(sdl2::window fenetre, Centrale& centrale, SalleDeControle& salleDeControle)
{
  double etatCentrale = centrale.etatCentrale();

}


void jeu()
{
  sdl2::window fenetre("Nuclear Alert", {1400,750});

  sdl2::image image("image/Menu.jpg", fenetre);

  auto [wph, hph] = fenetre.dimensions();
  image.stretch({wph,hph});

  fenetre << image << sdl2::flush;

  Centrale centrale;
  SalleDeControle salleDeControle;

  int niveau = menu();

  if(niveau == 49)
  {
    niveau1(fenetre,centrale,salleDeControle);
    //bilan(fenetre,centrale,salleDeControle);
  }

  if(niveau == 50)
  {
    niveau1(fenetre,centrale,salleDeControle);
    //bilan(fenetre,centrale,salleDeControle);
  }

  /*if(niveau == 51)
  {
    niveau1(fenetre,centrale,salleDeControle);
    bilan(fenetre,centrale,salleDeControle);
  }*/
}







//
