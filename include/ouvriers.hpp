#ifndef OUVRIERS_HPP_
#define OUVRIERS_HPP_

#include <string>
#include <array>


#include "centrale.hpp"

class Ouvriers
{
public:
  Ouvriers(); // Constructeur
  ~Ouvriers();  // Destructeur

  std::array<int,145> getEtatSante() const; // Revoie l'état de santé des ouvriers
  std::array<int,145> getEtatMission() const; // Renvoie l'état de mission des ouvriers
  std::array<std::string,145> getLieuMission() const; // Renvoie le lieu de mission des ouvriers ('reserve' si pas de mission)
  int getNombreOuvriersDispo(); // Renvoie le nombre d'ouvriers disponibles
  std::array<int,8> getEtatReparation() const;  // Renvoie l'état de la réparation de chaque organe
  void majEtatSante(Centrale& centrale);  // Met a jour l'état de santé des ouvriers
  int majNombreOuvriersDispo(); // Met a jour le nombre douvriers disponibles
  void envoyerOuvriers(std::string lieu, Centrale& centrale); // Envoie le nombre d'ouvriers requis sur un organe
  void rappelerOuvriers(Centrale& centrale);  // Rappelle les ouvriers en mission
  void guerir();  // Simulation de la guérison des ouvriers blessés
  int nombreEnIntervention(); // Renvoie le nombre d'ouvriers en intervention
  int interventionPossible(Centrale& centrale, std::string lieu); // Renvoie 1 si l'intervention est possible sur un organe, 0 sinon
  void annulerIntervention(std::string lieu); // Annule l'intervention des ouvriers sur un organe
  int nombreOuvriersBlesses();  // Renvoie le nombre d'ouvriers blessés
  bool InterventionEnCours(std::string lieu); // renvoie true si une intervention est en cours sur un organe, false sinon
  int nombreEnInterventionOrgane(std::string lieu); // Renvoie le nombre d'ouvriers en intervention sur un organe
  void reparer(Centrale& centrale); // Repare les organes lorsqueles ouvriers y sont en intervention
  void remplacerOuvrierMalade(std::string lieu);  // Remplace surun chantier un ouvrier malade par un ouvrier disponible

private:
  std::array<int,145> m_etatSante;
  std::array<int,145> m_etatMission;
  std::array<std::string,145> m_lieuMission;
  std::array<int,145> m_estDispo;
  int m_nombreOuvriersDispo;
  std::array<int,8> m_etatReparation;
};

#endif
