#include <iostream>

#include "sdl2.hpp"
#include "circuit_primaire.hpp"
#include "circuit_secondaire.hpp"
#include "salle_de_controle.hpp"


using namespace std;


void debut()
{
  SalleDeControle sdc;
  CircuitPrim cp;

  sdl2::window fenetre("Nuclear Alert", {1400,750});
  //sdl2::font fonte_titre("./data/Lato-Bold.ttf",28);
  //sdl2::texte titre ("Console d'application élaborée", fonte_titre, fenetre, {0x00,0xFF,0xFF,0xFF});
  //titre.at(0,0);
  sdc.cadre(fenetre);
  sdc.afficheCircuitPrim(fenetre,cp);
  //fenetre << titre;
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
