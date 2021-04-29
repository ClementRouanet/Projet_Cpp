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
  vector<int> sortie = {0, 0}; // Premier : changement, second : fin session

  bool iskey_down = false;
  bool quitter = false;
  sdl2::event_queue queue;

  while (not quitter && sortie[1] == 0)
  {
    while (not quitter && sortie[0] == 0 && sortie[1] == 0) // Boucle salle de commande
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

    /*  cout << "TBeff : " << centrale.tauxBoreActuel() << endl;
      cout << "TGreff : " << centrale.propGrActuel() << endl;
      cout << "D1 : " << centrale.debitEauPrim() << endl;
      cout << "IT1 : " << centrale.inertieTemperaturePrim() << endl;
      cout << "P1 : " << centrale.pressionPrim() << endl << endl;*/

      auto end = chrono::system_clock::now();
      chrono::duration<double> secondesEcoulees = end - start;
      int tps = 1000 - floor(secondesEcoulees.count()*1000);

      if (secondesEcoulees.count() < 1)
        this_thread::sleep_for(chrono::milliseconds(tps));
    }
  }
}

















//
