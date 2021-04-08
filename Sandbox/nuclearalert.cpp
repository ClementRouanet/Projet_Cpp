#include <thread>
#include <chrono>
#include <random>
#include <functional>
#include <iostream>
#include <utility>
//#include "centrale.hpp"
//#include "console.hpp"
//#include "radioprotection.hpp"

// Pour pouvoir utiliser les unités de temps (3h, 1s, 10ms, 1000ns, etc.)
using namespace std::chrono_literals;

int main()
{
  // Création d'un générateur de nombre au hasard entre 0. et 1.
  // Le moteur de création de nombre stochastique
  std::random_device hgenerator; // Permet à chaque run du programme d'avoir un entier différent
  // hgenerator() va servir la graine aléatoire (seed)
  std::default_random_engine generator(hgenerator()); // Equivalent au générateur du rand du langage C
  std::uniform_real_distribution<double> genrand(0.,1.);
  std::uniform_int_distribution<int> igenran(0, 90);

  double x = genrand(generator);
  // Création d'une fonction rnd qui permet d'avoir un nombre entre 0 et 1
  auto drnd = std::bind(genrand, generator);
  auto irnd = std::bind(igenran, generator);

  for ( int i = 0; i < 10; ++i )
  {
      double y = drnd();
      double a = irnd();
      std::cout << "max(x,y) = " << std::max(x,y)  << ", a = " << a << std::endl;
      std::this_thread::sleep_for(750ms);
  }

  bool quit = false;
  bool console_state = true;
  salle_de_controle_t salle_de_controle(&centrale);
  radioprotection_t radioprotection(...);
  do
  {
      auto start = std::chrono::high_resolution_clock::now();
      std::chrono::duration<double> diff;
      do
      {   // On ne fait que gérer l'affichage (raffraichissement) et les événements provoqués par
          // le joueur.
          if (console_state)
              salle_de_controle.display_and_run();
          else
              radioprotection.display_and_run();

          auto end = std::chrono::high_resolution_clock::now();
          diff   = end-start;// Diff delta t en secondes
      } while (diff < 1);
      // Met à jour les différents paramètres...
      // Changer les objectifs demandés dans la boucle interne (exemple abaisser le rendement d'une pompe
      // ou le taux de graphite immergé demandé pendant la seconde qui s'est écoulée).
      //
      // Met le processus en veille pendant une seconde.
      // std::this_thread::sleep_for(1s);
  } while(quit == false);
  return EXIT_SUCCESS;
}
