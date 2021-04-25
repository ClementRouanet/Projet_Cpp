#include <iostream>
#include <string>
#include <chrono>
#include <thread>

#include "dispatching.hpp"
#include "centrale.hpp"
#include "sdl2.hpp"

Dispatching::Dispatching():m_tourDebut(0), m_tourActuel(0), m_score(100)
{
}

void Dispatching::premierOrdre(sdl2::window& fenetre)
{

}

void Dispatching::ordre(sdl2::window& fenetre, Centrale& centrale)
{

}

void Dispatching::affichageDispatching(sdl2::window& fenetre, Centrale& centrale)
{

}


Dispatching::~Dispatching()
{
}
