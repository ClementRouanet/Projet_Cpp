#include "salle_de_controle.hpp"
#include "circuit_primaire.hpp"
#include "circuit_secondaire.hpp"
#include "sdl2.hpp"
#include <string>

using namespace std;


SalleDeControle::SalleDeControle()
{
}

void SalleDeControle::cadre(sdl2::window& fenetre) const
{
  sdl2::image cadre("image/Cadre_SalleDeControle.jpg", fenetre);
  auto [wph, hph] = fenetre.dimensions();
  cadre.stretch({wph,hph});

  sdl2::font fonte_titre("./data/Lato-Bold.ttf",50);
  sdl2::texte titre ("Salle de contrôle", fonte_titre, fenetre, {0xFF,0x00,0x00,0x00});
  titre.at(2*wph/5-20,0);

  fenetre << cadre << titre;
}


void SalleDeControle::affichageDispatching(sdl2::window& fenetre) const
{

}


void SalleDeControle::affichageProdElec(sdl2::window& fenetre) const
{

}

void SalleDeControle::afficheTauxBorePiscine(sdl2::window& fenetre) const
{

}


void SalleDeControle::afficheCircuitPrim(sdl2::window& fenetre, CircuitPrim& circuitPrim) const
{
  double rendement = circuitPrim.rendementPompe();
  double temperature = circuitPrim.temperatureEau();
  double debit = circuitPrim.debitEau();
  double pression = circuitPrim.pression();
  double radioactivite = circuitPrim.radioactivite();

  string SRendement(to_string(rendement));
  string STemperature(to_string(temperature));
  string SDebit(to_string(debit));
  string SPression(to_string(pression));
  string SRadioactivite(to_string(radioactivite));

  auto [wph, hph] = fenetre.dimensions();

  sdl2::font fonte_texte("./data/Lato-Bold.ttf",20);
  sdl2::font fonte_titre("./data/Lato-Bold.ttf",30);

  sdl2::texte texte("Circuit Primaire", fonte_titre, fenetre, {0x00,0x00,0xFF,0x00});
  sdl2::texte texteRendement("Rendement de la pompe : " + SRendement + " %", fonte_texte, fenetre, {0x00,0x00,0x00,0x00});
  sdl2::texte texteTemperature("Température dans le circuit : " + STemperature + " °C", fonte_texte, fenetre, {0x00,0x00,0x00,0x00});
  sdl2::texte texteDebit("Débit de l'eau : " + SDebit + " m^3.s^(-1)", fonte_texte, fenetre, {0x00,0x00,0x00,0x00});
  sdl2::texte textePression("Pression : " + SPression + " bar", fonte_texte, fenetre, {0x00,0x00,0x00,0x00});
  sdl2::texte texteRadioactivite("Radioactivité : " + SRadioactivite + " becquerel", fonte_texte, fenetre, {0x00,0x00,0x00,0x00});

  texte.at(2*wph/5+60, 80);
  texteRendement.at(2*wph/5-20,140);
  texteTemperature.at(2*wph/5-20,180);
  texteDebit.at(2*wph/5-20,220);
  textePression.at(2*wph/5-20,260);
  texteRadioactivite.at(2*wph/5-20,300);

  fenetre << texte << texteRendement << texteTemperature << texteDebit << textePression << texteRadioactivite;
}


void SalleDeControle::afficheCircuitSec(sdl2::window& fenetre, CircuitSec& circuitSec) const
{
  double rendement = circuitSec.rendementPompe();
  double temperature = circuitSec.temperatureVapeur();
  double debit = circuitSec.debitEau();
  double pression = circuitSec.pressionVapeur();
  double radioactivite = circuitSec.radioactivite();

  string SRendement(to_string(rendement));
  string STemperature(to_string(temperature));
  string SDebit(to_string(debit));
  string SPression(to_string(pression));
  string SRadioactivite(to_string(radioactivite));

// MAJ
}


void SalleDeControle::afficheSystSecurite(sdl2::window& fenetre) const
{

}


void SalleDeControle::afficheSystRefroidissement(sdl2::window& fenetre) const
{

}


void SalleDeControle::afficheEtatBarreGraphite(sdl2::window& fenetre) const
{

}


void SalleDeControle::afficheCommandes(sdl2::window& fenetre) const
{

}


SalleDeControle::~SalleDeControle()
{
}
