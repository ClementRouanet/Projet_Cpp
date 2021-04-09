#include <iostream>
#include "circuit_primaire.hpp"
#include "circuit_secondaire.hpp"

using namespace std;

int main(int argc, char **argv)
{
  CircuitPrim cp;
  cout << cp.etatCircuit() << endl;

  return EXIT_SUCCESS;
}
