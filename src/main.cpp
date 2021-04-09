#include <iostream>

#include "circuit_primaire.hpp"
#include "circuit_secondaire.hpp"


using namespace std;


int main()
{
  CircuitPrim cp;
  cout << cp.etatCircuit() << endl;
  return 0;
}
