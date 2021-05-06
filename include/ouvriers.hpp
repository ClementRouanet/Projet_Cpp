#ifndef OUVRIERS_HPP_
#define OUVRIERS_HPP_

#include <string>
#include <array>


#include "centrale.hpp"

class Ouvriers
{
public:
  Ouvriers();
  ~Ouvriers();

  std::array<int,145> getEtatSante() const;
  std::array<int,145> getEtatMission() const;
  std::array<std::string,145> getLieuMission() const;
  int getNombreOuvriersDispo() const;
  std::array<int,8> getEtatReparation() const;
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
  std::array<int,145> m_etatSante;
  std::array<int,145> m_etatMission;
  std::array<std::string,145> m_lieuMission;
  std::array<int,145> m_estDispo;
  int m_nombreOuvriersDispo;
  std::array<int,8> m_etatReparation;
};

#endif
