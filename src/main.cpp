#include <iostream>

#include "sdl2.hpp"


using namespace std;


int main(int argc, char* args[])
{
  sdl2::init(argc,args);
  srand(time(nullptr));

  jeu();

  sdl2::finalize();
  return 0;
}
