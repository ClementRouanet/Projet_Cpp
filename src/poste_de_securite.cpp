#include <iostream>
#include <string>

#include "poste_de_securite.hpp"
#include "centrale.hpp"
#include "circuit_primaire.hpp"
#include "circuit_secondaire.hpp"
#include "sdl2.hpp"

using namespace std;

PosteDeSecurite::PosteDeSecurite()
{

}




void PosteDeSecurite::cadre(sdl2::window& fenetre) const // Affiche un cadre
{
  sdl2::image cadre("image/Cadre_SalleDeControle.jpg", fenetre);
  auto [x, y] = fenetre.dimensions();
  cadre.stretch({x,y});

  sdl2::font fonte_titre("./data/Lato-Bold.ttf",50);
  sdl2::texte titre ("Poste de Securité", fonte_titre, fenetre, {0xFF,0x00,0x00,0x00});
  titre.at(2*wph/5-20,0);

  fenetre << cadre << titre;
}
void PosteDeSecurite::affichageReacteur(sdl2::window& fenetre) const // Affichage du réacteur (état canaux, barres de graphite, piscine et cuve)
{

}


//------------------------------CADRAN CIRCUIT PRIMAIRE------------------------------------//
 // Affiche le circuit primaire (état, pompe, pressuriseur, résistances électriques et l'injecteur)
void PosteDeSecurite::affichageCircuitPrim(sdl2::window& fenetre,Centrale& centrale) const
{
 double EtatCircuit = centrale.etatCircuitPrim();
 double EtatPompe = centrale.etatPompePrim();
 double EtatPressuriseur = centrale.etatPressuriseur();
 double EtatResistancePressuriseur = centrale.etatResistancePressuriseur();

 string sEtatCircuit(to_string(EtatCircuit));
 string sEtatPompe(to_string(EtatPompe));
 string sEtatPressuriseur(to_string(EtatPressuriseur));
 string sEtatResistancePressuriseur(to_string(EtatResistancePressuriseur));


 auto [x, y] = fenetre.dimensions();
 //Ajouter la fonte du titre et des textes
 sdl2::font fonte_texte("./data/Lato-Bold.ttf",20);
 sdl2::font fonte_titre("./data/Lato-Bold.ttf",30);

 sdl2::texte titre("Circuit Primaire", fonte_titre, fenetre, {0x00,0x00,0xFF,0x00});
 sdl2::texte texteCircuit("Etat du Circuit : " + sEtatCircuit, fonte_texte, fenetre, {0x00,0x00,0x00,0x00});
 sdl2::texte textePompe("Etat de la pompe : " + sEtatPompe, fonte_texte, fenetre, {0x00,0x00,0x00,0x00});
 sdl2::texte textePressuriseur("Etat du Pressuriseur : " + sEtatPressuriseur, fonte_texte, fenetre, {0x00,0x00,0x00,0x00});
 sdl2::texte texteResistance("Etat de la Resistance du Pressuriseur : " + sEtatResistancePressuriseur, fonte_texte, fenetre, {0x00,0x00,0x00,0x00});

 //Placement dans le cadran : On change après encore
 titre.at(2*x/5+60, 80);
 texteCircuit.at(2*x/5-20,140);
 textePompe.at(2*x/5-20,180);
 textePressuriseur.at(2*x/5-20,220);
 texteResistance.at(2*x/5-20,260);

 fenetre<<titre<<texteCircuit<<textePompe<<textePressuriseur<<texteResistance;
}




//----------------------------------------------------------CADRAN CIRCUIT SECONDAIRE----------------------------------- ------------------------//
//Affiche le circuit secondaire (état, pompe, générateur de vapeur, échangeur de chaleur)
void PosteDeSecurite::affichageCircuitSec(sdl2::window& fenetre,Centrale& centrale) const
{

  double EtatCircuit = centrale.etatCircuitSec();
  double EtatPompe = centrale.etatPompeSec();
  double EtatGenerateurVapeur = centrale.etatGenerateurVapeur();
  double EtatEchangeurChaleur = centrale.etatEchangeurChaleur();

  string sEtatCircuit(to_string(EtatCircuit));
  string sEtatPompe(to_string(EtatPompe));
  string sEtatGenerateurVapeur(to_string(EtatGenerateurVapeur));
  string sEtatEchangeurChaleur(to_string(EtatEchangeurChaleur));


  auto [x, y] = fenetre.dimensions();
  //Ajouter la fonte du titre et des textes
  sdl2::font fonte_texte("./data/Lato-Bold.ttf",20);
  sdl2::font fonte_titre("./data/Lato-Bold.ttf",30);

  sdl2::texte titre("Circuit Secondaire", fonte_titre, fenetre, {0x00,0x00,0xFF,0x00});
  sdl2::texte texteCircuit("Etat du Circuit : " + sEtatCircuit, fonte_texte, fenetre, {0x00,0x00,0x00,0x00});
  sdl2::texte textePompe("Etat de la pompe : " + sEtatPompe, fonte_texte, fenetre, {0x00,0x00,0x00,0x00});
  sdl2::texte texteGenerateurVapeur("Etat du Generateur de Vapeur : " + sEtatGenerateurVapeur, fonte_texte, fenetre, {0x00,0x00,0x00,0x00});
  sdl2::texte texteEchangeurChaleur("Etat de l'Echangeur de Chaleur : " + sEtatEchangeurChaleur, fonte_texte, fenetre, {0x00,0x00,0x00,0x00});

  //Placement dans le cadran : On change après encore
  titre.at(2*x/5+60, 80);
  texteCircuit.at(2*x/5-20,140);
  textePompe.at(2*x/5-20,180);
  texteGenerateurVapeur.at(2*x/5-20,220);
  texteEchangeurChaleur.at(2*x/5-20,260);

  fenetre<<titre<<texteCircuit<<textePompe<<texteGenerateurVapeur<<texteEchangeurChaleur;
}



//----------------------------CADRAN ENCEINTE --------------------------------------//
void PosteDeSecurite::affichageEnceinteConfinement() const  // Affiche l'état de l'enceinte de confinement
{

}

void PosteDeSecurite::affichageCondenseur() const // Affiche l'état du condenseur
{

}

void PosteDeSecurite::affichageOuvriers() const // Affiche les effectifs humains à notre disposition
{

}

void PosteDeSecurite::affichageActivite() const // Affiche le signalement de divers niveaux de contaminations
{

}

void PosteDeSecurite::affichageOrdinateur() const // Affiche l'état courant de la centrale et des alentours
{

}
void PosteDeSecurite::affichageCommandes() const  // Affiche les commandes disponibles pour effectuer des actions
{

}

PosteDeSecurite::~PosteDeSecurite()
{

}
