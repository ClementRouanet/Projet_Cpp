#include <iostream>

#include "sdl2.hpp"
#include "circuit_primaire.hpp"
#include "circuit_secondaire.hpp"


using namespace std;

void test();

int main(int argc, char* args[])
{
  CircuitPrim cp;
  cout << cp.etatCircuit() << endl;

  sdl2::init(argc,args);
  test();
  sdl2::finalize();
  return 0;
}

void test()
{
  sdl2::window fenetre("La zone", {800,600});
}
