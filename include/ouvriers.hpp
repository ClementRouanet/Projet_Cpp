#ifndef OUVRIERS_HPP_
#define OUVRIERS_HPP_
#include <string>
#include <vector>
#include <random>
#include "centrale.hpp"

class Ouvriers
{
public:

Ouvriers();
~Ouvriers();
std::vector<int> getEtatSante() const;
std::vector<int> getEtatMission() const;
std::vector<std::string> getLieuMission() const;
int getNombreOuvriersDispo() const;
void majEtatSante(Centrale& centrale);
int majNombreOuvriersDispo();
void envoyerOuvriers(std::string lieu, Centrale& centrale);
void rappelerOuvriers(Centrale& centrale);
void guerir();
int nombreEnIntervention();
int interventionPossible(Centrale& centrale);
void annulerIntervention(std::string lieu);

private:
std::vector<int> m_etatSante;
std::vector<int> m_etatMission;
std::vector<std::string> m_lieuMission;
std::vector<int> m_estDispo;
int m_nombreOuvriersDispo;
};
#endif
