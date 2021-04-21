#include <iostream>
#include <random>

#include "ouvrier.hpp"

using namespace std;


Ouvriers::Ouvriers() : m_malade(false), m_chantier(false)
{
}

void Ouvriers::guerison()
{

  auto RND = ((float)(rand()))/((float)(RAND_MAX))*1;

  if(RND<=0.4)
    m_malade = false;
}

void Ouvriers::blessure()
{

}

Ouvriers::~Ouvriers()
{
}
