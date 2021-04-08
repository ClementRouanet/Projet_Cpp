#include <SDL.h>
#include <iostream>

using namespace std;
int main(int argc, char **argv)
{
  SDL_version nb;
  SDL_VERSION(&nb);
  cout << "Hello" << nb.major << nb.minor << nb.patch << endl;

  return EXIT_SUCCESS;
}
 // g++ src/main.cpp -o bin/main -I include -L lib -lmingw32 -lSDL2main -lSDL2
