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
std::vector<int> getEtatReparation() const;
void majEtatSante(Centrale& centrale);
int majNombreOuvriersDispo();
void envoyerOuvriers(std::string lieu, Centrale& centrale);
void rappelerOuvriers(Centrale& centrale);
void guerir();
int nombreEnIntervention();
int interventionPossible(Centrale& centrale, std::string lieu);
void annulerIntervention(std::string lieu);
int nombreOuvriersBlesses();
bool InterventionEnCours(std::string lieu);
int nombreEnInterventionOrgane(std::string lieu);
void reparer(Centrale& centrale);
void remplacerOuvrierMalade(std::string lieu);

private:
std::vector<int> m_etatSante = {1};
std::vector<int> m_etatMission = {0};
std::vector<std::string> m_lieuMission = {"reserve"};
std::vector<int> m_estDispo = {1};
int m_nombreOuvriersDispo;
std::vector<int> m_etatReparation = {0};
};
#endif
