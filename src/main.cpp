#include <iostream>

#include "sdl2.hpp"
#include "centrale.hpp"
#include "circuit_primaire.hpp"
#include "circuit_secondaire.hpp"
#include "salle_de_controle.hpp"


using namespace std;


void debut()
{
  SalleDeControle sdc;
  CircuitPrim cp;
  CircuitSec cs;
  Centrale cent;

  sdl2::window fenetre("Nuclear Alert", {1400,750});

  sdc.cadre(fenetre);
  sdc.affichageProdElec(fenetre, cent);
  sdc.afficheCircuitPrim(fenetre, cp);
  sdc.afficheCircuitSec(fenetre,cs);
  sdc.affichePressionEnceinte(fenetre,cent);
  sdc.afficheSystRefroidissement(fenetre,cs);
  sdc.afficheCommandes(fenetre);
  
  fenetre << sdl2::flush;

  bool quitting = false;
  sdl2::event_queue queue;

  while (not quitting)
  {
    auto events = queue.pull_events();
    for ( const auto& e : events)
    {
      if (e->kind_of_event() == sdl2::event::quit)
          quitting = true;

      if ( (e->kind_of_event() == sdl2::event::key_down))
      {
        auto& key_ev = dynamic_cast<sdl2::event_keyboard&>(*e);
        char keychar = key_ev.ascci_code();
        if (keychar == 'a')
          quitting = true;
     }
    }
  }
}

int main(int argc, char* args[])
{
  sdl2::init(argc,args);
  debut();
  sdl2::finalize();
  return 0;
}
