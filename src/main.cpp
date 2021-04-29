#include <iostream>
#include <vector>
#include <chrono>

#include "sdl2.hpp"
#include "centrale.hpp"
#include "salle_de_controle.hpp"
#include "niveaux.hpp"

using namespace std;


void debut()
{
  SalleDeControle sdc;
  Centrale cent;
  vector<int> sortie = {0, 0};

  sdl2::window fenetre("Nuclear Alert", {1400,750});

  bool iskey_down = false;
  bool quitting = false;
  sdl2::event_queue queue;

  while (not quitting && sortie[0] == 0 && sortie[1] == 0)
  {
    sdc.majAffichage(fenetre, cent);

    auto events = queue.pull_events();
    for ( const auto& e : events)
    {
      if (e->kind_of_event() == sdl2::event::quit)
      quitting = true;

      if ((e->kind_of_event() == sdl2::event::key_down) || (e->kind_of_event() == sdl2::event::key_up))
      {
        auto& key_ev = dynamic_cast<sdl2::event_keyboard&>(*e);

        if ((e->kind_of_event() == sdl2::event::key_down) &&  (iskey_down == false))
        {
          sortie = sdc.majCommandes(fenetre, key_ev.code(), cent);
          iskey_down = true;
        }
        if (key_ev.type_of_event() == sdl2::event::key_up)
        iskey_down = false;
      }
    }
  }
}


int main(int argc, char* args[])
{
  sdl2::init(argc,args);
  srand(time(nullptr));

  sdl2::window fenetre("Nuclear Alert", {1400,750});
  Centrale centrale;
  SalleDeControle salleDeControle;

  niveau1(fenetre, centrale, salleDeControle);

  //debut();

  sdl2::finalize();
  return 0;
}
