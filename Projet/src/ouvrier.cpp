#include <chrono>
#include <random>
#include <functional>

#include "ouvrier.hpp"

using namespace std;


Ouvriers::Ouvriers() : m_malade(false), m_chantier(false)
{
}

void Ouvriers::guerison()
{
  random_device hgenerateur;
  default_random_engine generateur(hgenerateur());
  uniform_real_distribution<double> genrand(0,1);

  auto rnd = bind(genrand, generateur);
  double RND = rnd();

  if(RND<=0.4)
    m_malade = false;
}

void Ouvriers::blessure()
{

}

Ouvriers::~Ouvriers()
{
}
