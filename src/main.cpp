#include <iostream>
#include <random>
#include <chrono>

#include "sdl2.hpp"
#include "centrale.hpp"
#include "salle_de_controle.hpp"
#include "poste_de_securite.hpp"
#include "ouvriers.hpp"
#include "dispatching.hpp"


using namespace std;


void debut()
{
  PosteDeSecurite pds;
  SalleDeControle sdc;
  Ouvriers ouvriers;
  CircuitPrim cp;
  CircuitSec cs;
  Centrale cent;

  sdl2::window fenetre("Nuclear Alert", {1400,750});

  bool finSession = false;
  bool quitting = false;
  sdl2::event_queue queue;

  while (not quitting && finSession == 0)
  {
    pds.majAffichage(fenetre, cent, ouvriers);

    auto events = queue.pull_events();
    for ( const auto& e : events)
    {
      if (e->kind_of_event() == sdl2::event::quit)
          quitting = true;

    if ( (e->kind_of_event() == sdl2::event::key_down))
      {
        auto& key_ev = dynamic_cast<sdl2::event_keyboard&>(*e);
        //char keychar = key_ev.ascci_code();
        int key =  key_ev.ascci_code();
        finSession = sdc.majCommandes(fenetre, key, cent);
        //auto keychar = key_ev.code();
        //cout << keychar << endl;
      /*  if (keychar == 'a')
          quitting = true;*/
     }
   }
 }
}

int main(int argc, char* args[])
{
  sdl2::init(argc,args);
  srand(time(nullptr));

  debut();

  sdl2::finalize();
  return 0;
}
