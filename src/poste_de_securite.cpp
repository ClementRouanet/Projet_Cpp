#include <iostream>
#include <string>
#include <chrono>
#include <thread>

#include "poste_de_securite.hpp"

using namespace std;

PosteDeSecurite::PosteDeSecurite() : m_schemaCentrale(false), m_evacuation(false)
{

}

void PosteDeSecurite::majAffichage(sdl2::window& fenetre, Centrale& centrale) // Met à jour l'affichage de la fenêtre graphique
{
  cadre(fenetre); // Affiche un cadre
  affichageReacteur(fenetre,centrale); // Affichage du réacteur (état canaux, barres de graphite, piscine et cuve)
  affichageCircuitPrim(fenetre,centrale);  // Affiche le circuit primaire (état, pompe, pressuriseur, résistances électriques et l'injecteur)
  affichageCircuitSec(fenetre,centrale); //Affiche le circuit secondaire (état, pompe, générateur de vapeur, échangeur de chaleur)
  affichageEnceinteConfinement( fenetre,centrale);  // Affiche l'état de l'enceinte de confinement
  affichageCondenseur(fenetre,centrale); // Affiche l'état du condenseur
  affichageOuvriers(fenetre); // Affiche les effectifs humains à notre disposition
  affichageActivite(fenetre,centrale); // Affiche le signalement de divers niveaux de contaminations
  affichageOrdinateur(fenetre,centrale); // Affiche l'état courant de la centrale et des alentours

  if(m_schemaCentrale == true)
    affichageSchemaCentrale(fenetre, centrale); //Affichage du schéma de la centrale

  fenetre << sdl2::flush;
}


void PosteDeSecurite::cadre(sdl2::window& fenetre) const // Affiche un cadre
{
  sdl2::image cadre("image/poste_de_securite.jpg", fenetre);
  auto [wph, hph] = fenetre.dimensions();
  cadre.stretch({wph,hph});

  fenetre << cadre;
}


void PosteDeSecurite::affichageSchemaCentrale(sdl2::window& fenetre, Centrale& centrale)//Affichage du schéma de la centrale
{
  bool iskey_down = false;
  sdl2::event_queue queue;

  schemaCentrale(fenetre, centrale);
  auto events = queue.pull_events();
  for (const auto& e : events)
  {
    if ((e->kind_of_event() == sdl2::event::key_down) || (e->kind_of_event() == sdl2::event::key_up))
    {
      auto& key_ev = dynamic_cast<sdl2::event_keyboard&>(*e);

      if ((e->kind_of_event() == sdl2::event::key_down) &&  (iskey_down == false))
      {
        if (key_ev.code() == 13)
          m_schemaCentrale = false;

        iskey_down = true;
      }
    if (key_ev.type_of_event() == sdl2::event::key_up)
      iskey_down = false;
    }
  }
}


void PosteDeSecurite::schemaCentrale(sdl2::window& fenetre, Centrale& centrale) //affiche les différentes composantes de la centrale
{
  //récupération des états des différentes composantes de la centrale
  double etatCentrale = centrale.etatCentrale();
  double etatReacteur = centrale.etatCuve();
  double etatCircuitPrim = centrale.etatCircuitPrim();
  double etatCircuitSec = centrale.etatCircuitSec();
  double etatCondenseur = centrale.etatCondenseur();

  auto [wph, hph] = fenetre.dimensions();

  sdl2::image schema("image/Centrale nucleaire.jpg", fenetre); //affiche le schéma entier de la centrale
  schema.stretch({4*wph/6,4*hph/6});
  schema.at(wph/6,hph/6);

  sdl2::image centraleNucl("image/Centrale.png", fenetre);//affiche la centrale nucleaire en rouge
  centraleNucl.stretch({4*wph/6,4*hph/6});
  centraleNucl.at(wph/6,hph/6);

  sdl2::image reacteur("image/Reacteur.png", fenetre);//affiche le reacteur en rouge
  reacteur.stretch({4*wph/6,4*hph/6});
  reacteur.at(wph/6,hph/6);

  sdl2::image circuitPrim("image/Circuit_primaire.png", fenetre);//affiche le circuit primaire en rouge
  circuitPrim.stretch({4*wph/6,4*hph/6});
  circuitPrim.at(wph/6,hph/6);

  sdl2::image circuitSec("image/Circuit_secondaire.png", fenetre);//affiche le circuit secondaire en rouge
  circuitSec.stretch({4*wph/6,4*hph/6});
  circuitSec.at(wph/6,hph/6);

  sdl2::image condenseur("image/Circuit_refroidissement.png", fenetre);//affiche le condenseur en rouge
  condenseur.stretch({4*wph/6,4*hph/6});
  condenseur.at(wph/6,hph/6);

  fenetre << schema << sdl2::flush;

  this_thread::sleep_for(chrono::milliseconds(500));

// si l'état de la centrale est inférieur à 0,5, on l'affiche en rouge
  if(etatCentrale < 0.5)
    fenetre << centraleNucl;
// si l'état des différentes composantes est inférieur à 0,3, on les affiche en rouge
  if(etatReacteur < 0.5)
    fenetre << reacteur;

  if(etatCircuitPrim < 0.5)
    fenetre << circuitPrim;

  if(etatCircuitSec < 0.5)
    fenetre << circuitSec;

  if(etatCondenseur < 0.5)
    fenetre << condenseur;

  fenetre << sdl2::flush;

  this_thread::sleep_for(chrono::milliseconds(400)); // met le programme en pause pendant 400 milliseconds
}


//----------------------------------------------CADRAN REACTEUR --------------------------------------------------------------//
void PosteDeSecurite::affichageReacteur(sdl2::window& fenetre, Centrale& centrale) const // Affichage du réacteur (état canaux, barres de graphite, piscine et cuve)
{
  //récupération des états des composants du reacteur
  double EtatCanaux = centrale.etatCanaux();
  double EtatBarresGr = centrale.etatBarresGr();
  double EtatPiscine = centrale.etatPiscine();
  double EtatCuve = centrale.etatCuve();

 //transformation en chaine de caractère
  string sEtatCanaux(to_string(EtatCanaux*100));
  string sEtatBarresGr(to_string(EtatBarresGr*100));
  string sEtatPiscine(to_string(EtatPiscine*100));
  string sEtatCuve(to_string(EtatCuve*100));

 //on garde 2 chiffres après la virgule
  sEtatCanaux.erase(2,7);
  sEtatBarresGr.erase(2,7);
  sEtatPiscine.erase(2,7);
  sEtatCuve.erase(2,7);


  auto [x, y] = fenetre.dimensions();
  //Ajouter la fonte du titre et des textes
  sdl2::font fonte_texte("./data/Welbut__.ttf",17);

  //affichage de la barre représentant l'état des composants
  sdl2::rectangle r1({static_cast<short unsigned int>(0.165*x),static_cast<short unsigned int>(0.13*y)}, {static_cast<short unsigned int>(80 - 80*(1-EtatCanaux)),20}, {static_cast<uint8_t>(255*(1-EtatCanaux)),static_cast<uint8_t>(255*EtatCanaux),0}, true);
  sdl2::rectangle r2({static_cast<short unsigned int>(0.165*x),static_cast<short unsigned int>(0.13*y)}, {80,20}, {0,0,0,0}, false);

  //affichage du texte et de la valeur de l'état du composant
  sdl2::texte texteCanaux("Etat des canaux : " + sEtatCanaux + " %", fonte_texte, fenetre, {0x00,0x00,0x00,0x00});

  sdl2::rectangle r3({static_cast<short unsigned int>(0.194*x),static_cast<short unsigned int>(0.18*y)}, {static_cast<short unsigned int>(80 - 80*(1-EtatBarresGr)),20}, {static_cast<uint8_t>(255*(1-EtatBarresGr)),static_cast<uint8_t>(255*EtatBarresGr),0}, true);
  sdl2::rectangle r4({static_cast<short unsigned int>(0.194*x),static_cast<short unsigned int>(0.18*y)}, {80,20}, {0,0,0,0}, false);

  sdl2::texte texteBarresGr("Etat barres graphite : " + sEtatBarresGr + " %", fonte_texte, fenetre, {0x00,0x00,0x00,0x00});

  sdl2::rectangle r5({static_cast<short unsigned int>(0.175*x),static_cast<short unsigned int>(0.23*y)}, {static_cast<short unsigned int>(80 - 80*(1-EtatPiscine)),20}, {static_cast<uint8_t>(255*(1-EtatPiscine)),static_cast<uint8_t>(255*EtatPiscine),0}, true);
  sdl2::rectangle r6({static_cast<short unsigned int>(0.175*x),static_cast<short unsigned int>(0.23*y)}, {80,20}, {0,0,0,0}, false);

  sdl2::texte textePiscine("Etat de la Piscine : " + sEtatPiscine + " %", fonte_texte, fenetre, {0x00,0x00,0x00,0x00});

  sdl2::rectangle r7({static_cast<short unsigned int>(0.16*x),static_cast<short unsigned int>(0.28*y)}, {static_cast<short unsigned int>(80 - 80*(1-EtatCuve)),20}, {static_cast<uint8_t>(255*(1-EtatCuve)),static_cast<uint8_t>(255*EtatCuve),0}, true);
  sdl2::rectangle r8({static_cast<short unsigned int>(0.16*x),static_cast<short unsigned int>(0.28*y)}, {80,20}, {0,0,0,0}, false);

  sdl2::texte texteCuve("Etat de la Cuve : " + sEtatCuve + " %", fonte_texte, fenetre, {0x00,0x00,0x00,0x00});

  //Placement dans le cadran
  texteCanaux.at(x*0.05,y*0.13);
  texteBarresGr.at(x*0.05,y*0.18);
  textePiscine.at(x*0.05,y*0.23);
  texteCuve.at(x*0.05,y*0.28);

  fenetre<<r1<<r2<<r3<<r4<<r5<<r6<<r7<<r8<<texteCanaux<<texteBarresGr<<textePiscine<<texteCuve;
}


//------------------------------CADRAN CIRCUIT PRIMAIRE------------------------------------//
 // Affiche le circuit primaire (état, pompe, pressuriseur, résistances électriques et l'injecteur)
void PosteDeSecurite::affichageCircuitPrim(sdl2::window& fenetre,Centrale& centrale) const
{
 double EtatCircuit = centrale.etatCircuitPrim();
 double EtatPompe = centrale.etatPompePrim();
 double EtatPressuriseur = centrale.etatPressuriseur();
 double EtatResistancePressuriseur = centrale.etatResistancePressuriseur();

 string sEtatCircuit(to_string(EtatCircuit*100));
 string sEtatPompe(to_string(EtatPompe*100));
 string sEtatPressuriseur(to_string(EtatPressuriseur*100));
 string sEtatResistancePressuriseur(to_string(EtatResistancePressuriseur*100));

 sEtatCircuit.erase(2,7);
 sEtatPompe.erase(2,7);
 sEtatPressuriseur.erase(2,7);
 sEtatResistancePressuriseur.erase(2,7);


 auto [x, y] = fenetre.dimensions();
 //Ajouter la fonte du titre et des textes
 sdl2::font fonte_texte("./data/Welbut__.ttf",17);

//affichage de la barre représentant l'état des composants
 sdl2::rectangle r1({static_cast<short unsigned int>(0.158*x),static_cast<short unsigned int>(0.44*y)}, {static_cast<short unsigned int>(80 - 80*(1-EtatCircuit)),20}, {static_cast<uint8_t>(255*(1-EtatCircuit)),static_cast<uint8_t>(255*EtatCircuit),0}, true);
 sdl2::rectangle r2({static_cast<short unsigned int>(0.158*x),static_cast<short unsigned int>(0.44*y)}, {80,20}, {0,0,0,0}, false);

 sdl2::texte texteCircuit("Etat du Circuit : " + sEtatCircuit + " %", fonte_texte, fenetre, {0x00,0x00,0x00,0x00});

 sdl2::rectangle r3({static_cast<short unsigned int>(0.167*x),static_cast<short unsigned int>(0.49*y)}, {static_cast<short unsigned int>(80 - 80*(1-EtatPompe)),20}, {static_cast<uint8_t>(255*(1-EtatPompe)),static_cast<uint8_t>(255*EtatPompe),0}, true);
 sdl2::rectangle r4({static_cast<short unsigned int>(0.167*x),static_cast<short unsigned int>(0.49*y)}, {80,20}, {0,0,0,0}, false);

 sdl2::texte textePompe("Etat de la pompe : " + sEtatPompe + " %", fonte_texte, fenetre, {0x00,0x00,0x00,0x00});

 sdl2::rectangle r5({static_cast<short unsigned int>(0.196*x),static_cast<short unsigned int>(0.54*y)}, {static_cast<short unsigned int>(80 - 80*(1-EtatPressuriseur)),20}, {static_cast<uint8_t>(255*(1-EtatPressuriseur)),static_cast<uint8_t>(255*EtatPressuriseur),0}, true);
 sdl2::rectangle r6({static_cast<short unsigned int>(0.196*x),static_cast<short unsigned int>(0.54*y)}, {80,20}, {0,0,0,0}, false);

 sdl2::texte textePressuriseur("Etat du Pressuriseur : " + sEtatPressuriseur + " %", fonte_texte, fenetre, {0x00,0x00,0x00,0x00});

 sdl2::rectangle r7({static_cast<short unsigned int>(0.224*x),static_cast<short unsigned int>(0.59*y)}, {static_cast<short unsigned int>(80 - 80*(1-EtatResistancePressuriseur)),20}, {static_cast<uint8_t>(255*(1-EtatResistancePressuriseur)),static_cast<uint8_t>(255*EtatResistancePressuriseur),0}, true);
 sdl2::rectangle r8({static_cast<short unsigned int>(0.224*x),static_cast<short unsigned int>(0.59*y)}, {80,20}, {0,0,0,0}, false);

 sdl2::texte texteResistance("Etat Resist Pressuriseur : " + sEtatResistancePressuriseur + " %", fonte_texte, fenetre, {0x00,0x00,0x00,0x00});

 //Placement dans le cadran
 texteCircuit.at(x*0.05,y*0.44);
 textePompe.at(x*0.05,y*0.49);
 textePressuriseur.at(x*0.05,y*0.54);
 texteResistance.at(x*0.05,y*0.59);

 fenetre<<r1<<r2<<r3<<r4<<r5<<r6<<r7<<r8<<texteCircuit<<textePompe<<textePressuriseur<<texteResistance;
}


//-----------------------------------------------------CADRAN CIRCUIT SECONDAIRE----------------------------------- ------------------------//
//Affiche le circuit secondaire (état, pompe, générateur de vapeur, échangeur de chaleur)
void PosteDeSecurite::affichageCircuitSec(sdl2::window& fenetre,Centrale& centrale) const
{

  double EtatCircuit = centrale.etatCircuitSec();
  double EtatPompe = centrale.etatPompeSec();
  double EtatGenerateurVapeur = centrale.etatGenerateurVapeur();
  double EtatEchangeurChaleur = centrale.etatEchangeurChaleur();

  string sEtatCircuit(to_string(EtatCircuit*100));
  string sEtatPompe(to_string(EtatPompe*100));
  string sEtatGenerateurVapeur(to_string(EtatGenerateurVapeur*100));
  string sEtatEchangeurChaleur(to_string(EtatEchangeurChaleur*100));

  sEtatCircuit.erase(2,7);
  sEtatPompe.erase(2,7);
  sEtatGenerateurVapeur.erase(2,7);
  sEtatEchangeurChaleur.erase(2,7);

  auto [x, y] = fenetre.dimensions();
  //Ajouter la fonte du titre et des textes
  sdl2::font fonte_texte("./data/Welbut__.ttf",17);

//affichage de la barre représentant l'état des composants
  sdl2::rectangle r1({static_cast<short unsigned int>(0.158*x),static_cast<short unsigned int>(0.76*y)}, {static_cast<short unsigned int>(80 - 80*(1-EtatCircuit)),20}, {static_cast<uint8_t>(255*(1-EtatCircuit)),static_cast<uint8_t>(255*EtatCircuit),0}, true);
  sdl2::rectangle r2({static_cast<short unsigned int>(0.158*x),static_cast<short unsigned int>(0.76*y)}, {80,20}, {0,0,0,0}, false);

  sdl2::texte texteCircuit("Etat du Circuit : " + sEtatCircuit + " %", fonte_texte, fenetre, {0x00,0x00,0x00,0x00});

  sdl2::rectangle r3({static_cast<short unsigned int>(0.167*x),static_cast<short unsigned int>(0.81*y)}, {static_cast<short unsigned int>(80 - 80*(1-EtatPompe)),20}, {static_cast<uint8_t>(255*(1-EtatPompe)),static_cast<uint8_t>(255*EtatPompe),0}, true);
  sdl2::rectangle r4({static_cast<short unsigned int>(0.167*x),static_cast<short unsigned int>(0.81*y)}, {80,20}, {0,0,0,0}, false);

  sdl2::texte textePompe("Etat de la pompe : " + sEtatPompe + " %", fonte_texte, fenetre, {0x00,0x00,0x00,0x00});

  sdl2::rectangle r5({static_cast<short unsigned int>(0.218*x),static_cast<short unsigned int>(0.86*y)}, {static_cast<short unsigned int>(80 - 80*(1-EtatGenerateurVapeur)),20}, {static_cast<uint8_t>(255*(1-EtatGenerateurVapeur)),static_cast<uint8_t>(255*EtatGenerateurVapeur),0}, true);
  sdl2::rectangle r6({static_cast<short unsigned int>(0.218*x),static_cast<short unsigned int>(0.86*y)}, {80,20}, {0,0,0,0}, false);

  sdl2::texte texteGenerateurVapeur("Etat Generateur Vapeur : " + sEtatGenerateurVapeur + " %", fonte_texte, fenetre, {0x00,0x00,0x00,0x00});

  sdl2::rectangle r7({static_cast<short unsigned int>(0.2145*x),static_cast<short unsigned int>(0.91*y)}, {static_cast<short unsigned int>(80 - 80*(1-EtatEchangeurChaleur)),20}, {static_cast<uint8_t>(255*(1-EtatEchangeurChaleur)),static_cast<uint8_t>(255*EtatEchangeurChaleur),0}, true);
  sdl2::rectangle r8({static_cast<short unsigned int>(0.2145*x),static_cast<short unsigned int>(0.91*y)}, {80,20}, {0,0,0,0}, false);

  sdl2::texte texteEchangeurChaleur("Etat Echangeur Chaleur : " + sEtatEchangeurChaleur + " %", fonte_texte, fenetre, {0x00,0x00,0x00,0x00});

  //Placement dans le cadran
  texteCircuit.at(x*0.05,y*0.76);
  textePompe.at(x*0.05,y*0.81);
  texteGenerateurVapeur.at(x*0.05,y*0.86);
  texteEchangeurChaleur.at(x*0.05,y*0.91);

  fenetre<<r1<<r2<<r3<<r4<<r5<<r6<<r7<<r8<<texteCircuit<<textePompe<<texteGenerateurVapeur<<texteEchangeurChaleur;
}


//----------------------------CADRAN ENCEINTE --------------------------------------//
 // Affiche l'état de l'enceinte de confinement
void PosteDeSecurite::affichageEnceinteConfinement(sdl2::window& fenetre,Centrale& centrale) const
{
 double EtatEnceinte = centrale.etatEnceinte();
 string sEtatEnceinte(to_string(EtatEnceinte*100));
 sEtatEnceinte.erase(2,7);

 auto [x, y] = fenetre.dimensions();
 //Ajouter la fonte du titre et des textes
 sdl2::font fonte_texte("./data/Welbut__.ttf",17);

//affichage de la barre représentant l'état des composants
 sdl2::rectangle r1({static_cast<short unsigned int>(0.505*x),static_cast<short unsigned int>(0.92*y)}, {static_cast<short unsigned int>(80 - 80*(1-EtatEnceinte)),20}, {static_cast<uint8_t>(255*(1-EtatEnceinte)),static_cast<uint8_t>(255*EtatEnceinte),0}, true);
 sdl2::rectangle r2({static_cast<short unsigned int>(0.505*x),static_cast<short unsigned int>(0.92*y)}, {80,20}, {0,0,0,0}, false);

 sdl2::texte texteEnceinte("Etat de l'Enceinte : " + sEtatEnceinte + " %", fonte_texte, fenetre, {0x00,0x00,0x00,0x00});

 //Placement dans le cadran : On change après encore
 texteEnceinte.at(x*0.38,y*0.92);

 fenetre<<r1<<r2<<texteEnceinte;
}

//-----------------------------------CADRAN CONDENSEUR--------------------------------------------//
// Affiche l'état du condenseur
void PosteDeSecurite::affichageCondenseur(sdl2::window& fenetre,Centrale& centrale) const
{
  double EtatCondenseur = centrale.etatCondenseur();
  string sEtatCondenseur(to_string(EtatCondenseur*100));
  sEtatCondenseur.erase(2,7);

  auto [x, y] = fenetre.dimensions();
  //Ajouter la fonte du titre et des textes
  sdl2::font fonte_texte("./data/Welbut__.ttf",17);

//affichage de la barre représentant l'état des composants
  sdl2::rectangle r1({static_cast<short unsigned int>(0.518*x),static_cast<short unsigned int>(0.82*y)}, {static_cast<short unsigned int>(80 - 80*(1-EtatCondenseur)),20}, {static_cast<uint8_t>(255*(1-EtatCondenseur)),static_cast<uint8_t>(255*EtatCondenseur),0}, true);
  sdl2::rectangle r2({static_cast<short unsigned int>(0.518*x),static_cast<short unsigned int>(0.82*y)}, {80,20}, {0,0,0,0}, false);

  sdl2::texte texteCondenseur("Etat du Condenseur : " + sEtatCondenseur + " %", fonte_texte, fenetre, {0x00,0x00,0x00,0x00});

  //Placement dans le cadran
  texteCondenseur.at(x*0.38,y*0.82);

  fenetre<<r1<<r2<<texteCondenseur;
}


//--------------------------------------------CADRAN OUVRIER------------------------------------------------------//

void PosteDeSecurite::affichageOuvriers(sdl2::window& fenetre) // Affiche les effectifs humains à notre disposition
{
  int ouvriersDispo = ouvriers.getNombreOuvriersDispo();
  int ouvriersEnIntervention = ouvriers.nombreEnIntervention();
  int ouvriersBlesses = ouvriers.nombreOuvriersBlesses();

  string sOuvriersDispo(to_string(ouvriersDispo));
  string sOuvriersEnIntervention(to_string(ouvriersEnIntervention));
  string sOuvriersBlesses(to_string(ouvriersBlesses));


  auto [x, y] = fenetre.dimensions();
  //Ajouter la fonte du titre et des textes
  sdl2::font fonte_texte("./data/Welbut__.ttf",17);

  sdl2::texte texteOuvriersDispo("Ouvriers disponibles : " + sOuvriersDispo, fonte_texte, fenetre, {0x00,0x00,0x00,0x00});
  sdl2::texte texteOuvriersEnIntervention("Ouvriers en intervention : " + sOuvriersEnIntervention, fonte_texte, fenetre, {0x00,0x00,0x00,0x00});
  sdl2::texte texteOuvriersBlesses("Ouvriers blesses : " + sOuvriersBlesses, fonte_texte, fenetre, {0x00,0x00,0x00,0x00});


  //Placement dans le cadran
  texteOuvriersDispo.at(x*0.75,y*0.13);
  texteOuvriersEnIntervention.at(x*0.75,y*0.18);
  texteOuvriersBlesses.at(x*0.75,y*0.23);


  fenetre<<texteOuvriersDispo<<texteOuvriersEnIntervention<<texteOuvriersBlesses;

}



//---------------------------------------------CADRAN ACTIVITE ALERTE ---------------------------------------------//
void PosteDeSecurite::affichageActivite(sdl2::window& fenetre,Centrale& centrale) const // Affiche le signalement de divers niveaux de contaminations
{
  double radioactivitePiscine = centrale.radPiscine();
  double radioactiviteEnceinte = centrale.radioactiviteEnceinte();
  double radioactiviteAir = centrale.radioactiviteAir();
  double radioactiviteEau = centrale.radioactiviteEau();

  string sRadioactivitePiscine(to_string(radioactivitePiscine));
  string sRadioactiviteEnceinte(to_string(1000.*radioactiviteEnceinte));
  string sRadioactiviteAir(to_string(1000.*radioactiviteAir));
  string sRadioactiviteEau(to_string(1000.*radioactiviteEau));

  sRadioactivitePiscine.erase(5,4);
  sRadioactiviteEnceinte.erase(4,7);
  sRadioactiviteAir.erase(4,7);
  sRadioactiviteEau.erase(4,7);

  auto [x, y] = fenetre.dimensions();
  //Ajouter la fonte du titre et des textes
  sdl2::font fonte_texte("./data/Welbut__.ttf",17);

  sdl2::texte texteRadioactivitePiscine("Radioactivite de la piscine : " + sRadioactivitePiscine + " bequerel", fonte_texte, fenetre, {0x00,0x00,0x00,0x00});
  sdl2::texte texteRadioactiviteEnceinte("Radioactivite de l'enceinte : " + sRadioactiviteEnceinte + " mrems/h", fonte_texte, fenetre, {0x00,0x00,0x00,0x00});
  sdl2::texte texteRadioactiviteAir("Radioactivite de l'air : " + sRadioactiviteAir + " mrems/h", fonte_texte, fenetre, {0x00,0x00,0x00,0x00});
  sdl2::texte texteRadioactiviteEau("Radioactivitede l'eau : " + sRadioactiviteEau + " mrems/h", fonte_texte, fenetre, {0x00,0x00,0x00,0x00});

  //Placement dans le cadran : On change après encore
  texteRadioactivitePiscine.at(0.36*x,0.53*y);
  texteRadioactiviteEnceinte.at(0.36*x,0.58*y);
  texteRadioactiviteAir.at(0.36*x,0.63*y);
  texteRadioactiviteEau.at(0.36*x,0.68*y);

  fenetre<<texteRadioactivitePiscine<<texteRadioactiviteEnceinte<<texteRadioactiviteAir<<texteRadioactiviteEau;
}


//------------------------------------------CADRAN ORDINATEUR --------------------------------------------------//
void PosteDeSecurite::affichageOrdinateur(sdl2::window& fenetre,Centrale& centrale) const // Affiche l'état courant de la centrale et des alentours
{
  double EtatCentrale = centrale.etatCentrale();
  int Contamination = centrale.contamination();
  double Evacuation = centrale.evacuation();

  string sEtatCentrale(to_string(EtatCentrale*100));
  string sContamination(to_string(Contamination));
  string sEvacuation(to_string(Evacuation));

  sEtatCentrale.erase(2,7);
  sEvacuation.erase(4,7);


  auto [x, y] = fenetre.dimensions();
  //Ajouter la fonte du titre et des textes
  sdl2::font fonte_texte("./data/Welbut__.ttf",17);

//affichage de la barre représentant l'état des composants
  sdl2::rectangle r1({static_cast<short unsigned int>(0.495*x),static_cast<short unsigned int>(0.2*y)}, {static_cast<short unsigned int>(80 - 80*(1-EtatCentrale)),20}, {static_cast<uint8_t>(255*(1-EtatCentrale)),static_cast<uint8_t>(255*EtatCentrale),0}, true);
  sdl2::rectangle r2({static_cast<short unsigned int>(0.495*x),static_cast<short unsigned int>(0.2*y)}, {80,20}, {0,0,0,0}, false);

  sdl2::texte texteCentrale("Etat de la Centrale : " + sEtatCentrale + " %", fonte_texte, fenetre, {0x00,0x00,0x00,0x00});
  sdl2::texte texteContamination("Population contaminée : " + sContamination, fonte_texte, fenetre, {0x00,0x00,0x00,0x00});
  sdl2::texte texteEvacuation("Proportion population évacuée : " + sEvacuation, fonte_texte, fenetre, {0x00,0x00,0x00,0x00});

  //Placement dans le cadran : On change après encore
  texteCentrale.at(0.36*x,y*0.2);
  texteContamination.at(0.36*x,y*0.25);
  texteEvacuation.at(0.36*x,y*0.30);

  fenetre<<r1<<r2<<texteCentrale<<texteContamination<<texteEvacuation;
}




int PosteDeSecurite::majCommandes(sdl2::window& fenetre, int touche, Centrale& centrale)
{
  int sortie = 0;
      switch (touche)
      {
        case 9 :  // tab
          m_schemaCentrale = true;
          break;

        case 32 : // Espace
          sortie = 1;
          break;

        case 112 :  // p
          evacuationPopulation(fenetre, centrale);
          break;

        case 98 :  // b
          bilanOuvriers(fenetre, centrale); //Cette commande affiche les différents organes où sont potentiellement réalisable des interventions humaines
          break;

        case 111 :  // o
          interventionOuvriers(fenetre, centrale);
          break;

      }
    return sortie;
}


void PosteDeSecurite::evacuationPopulation(sdl2::window& fenetre, Centrale& centrale)
{
 //on a appuyé sur p pour accéder à l'évacuation de la population
  bool quitter = false;
  bool iskey_down = false;
  sdl2::event_queue queue;

  while (not quitter)
  {
    auto events = queue.pull_events();
    for (const auto& e : events)
    {
      if ((e->kind_of_event() == sdl2::event::key_down) || (e->kind_of_event() == sdl2::event::key_up))
      {
        auto& key_ev = dynamic_cast<sdl2::event_keyboard&>(*e);

        if ((e->kind_of_event() == sdl2::event::key_down) &&  (iskey_down == false))
        {
          switch (key_ev.code())
          {
              case 13 :// si on appuie sur entrer, on valide l'évacuation
              m_evacuation = true;
              quitter = true;
              break;
           }
              majAffichage(fenetre, centrale);
              iskey_down = true;
        }
          if (key_ev.type_of_event() == sdl2::event::key_up)
          iskey_down = false;
      }
    }
  }
}


void PosteDeSecurite::bilanOuvriers(sdl2::window& fenetre, Centrale& centrale)
{
  bool iskey_down = true;
  sdl2::event_queue queue;

  afficherBilan(fenetre,centrale);

  while (iskey_down == true)
  {
    auto events = queue.pull_events();
    for (const auto& e : events)
    {
      if ((e->kind_of_event() == sdl2::event::key_down) || (e->kind_of_event() == sdl2::event::key_up))
      {
        auto& key_ev = dynamic_cast<sdl2::event_keyboard&>(*e);

        if (key_ev.type_of_event() == sdl2::event::key_up)
          iskey_down = false;
      }
    }
  }
}


// --------------------------------------AFFICHAGE BILAN OUVRIER --------------------------------------------------//
void PosteDeSecurite::afficherBilan(sdl2::window& fenetre, Centrale& centrale)
{
  // on regarde si les interventions sont possibles : 1 si possible et 0 sinon
  int interventionPrimaire = ouvriers.interventionPossible(centrale,"circuit primaire");
  int interventionCentrale = ouvriers.interventionPossible(centrale,"centrale");

 //on récupère le nombre d'ouvriers disponibles
  int nbOuvriersDispo = ouvriers.getNombreOuvriersDispo();
  string snbOuvriersDispo(to_string(nbOuvriersDispo));

 //on récupère le nombre d'ouvriers en interventions selon les organes
  int ouvriersPompePrim = ouvriers.nombreEnInterventionOrgane("pompe primaire");
  int ouvriersPompeSec = ouvriers.nombreEnInterventionOrgane("pompe secondaire");
  int ouvriersCondenseur = ouvriers.nombreEnInterventionOrgane("condenseur");
  int ouvriersGenerateur = ouvriers.nombreEnInterventionOrgane("generateur de vapeur");
  int ouvriersInjecteur = ouvriers.nombreEnInterventionOrgane("injecteur Bore");
  int ouvriersCircuitPrim = ouvriers.nombreEnInterventionOrgane("circuit primaire");
  int ouvriersCircuitSec = ouvriers.nombreEnInterventionOrgane("circuit secondaire");
  int ouvriersPressuriseur = ouvriers.nombreEnInterventionOrgane("pressuriseur");

  // Conversion des int en string
  string souvriersPompePrim(to_string(ouvriersPompePrim));
  string souvriersPompeSec(to_string(ouvriersPompeSec));
  string souvriersCondenseur(to_string(ouvriersCondenseur));
  string souvriersGenerateur(to_string(ouvriersGenerateur));
  string souvriersInjecteur(to_string(ouvriersInjecteur));
  string souvriersCircuitPrim(to_string(ouvriersCircuitPrim));
  string souvriersCircuitSec(to_string(ouvriersCircuitSec));
  string souvriersPressuriseur(to_string(ouvriersPressuriseur));

  auto [wph, hph] = fenetre.dimensions();
  auto x = 4*wph/6, y = 4*hph/6;
  auto xx = x/4, yy = y/4;

  sdl2::image image("image/ActiviteOuvriere.jpg", fenetre);
  image.stretch({x,y});
  image.at(xx,yy);
  fenetre << image;

  sdl2::font fonte_texte("./data/Lato-Bold.ttf",15);

  sdl2::texte texteOui("oui", fonte_texte, fenetre, {0x00,0xFF,0x00,0x00}); //texte "oui" en vert
  sdl2::texte texteNon("non", fonte_texte, fenetre, {0xFF,0x00,0x00,0x00}); //texte "non" en rouge

  if(interventionPrimaire == 0 || interventionCentrale == 0) //intervention dans la pope primaire impossible
  {
    texteNon.at(xx+0.24*x,yy+0.2*y); fenetre << texteNon; // Pompe primaire
    texteNon.at(xx+0.71*x,yy+0.57*y); fenetre << texteNon;  // Circuit primaire
  }
  else
  {
    texteOui.at(xx+0.24*x,yy+0.2*y); fenetre << texteOui; // Pompe primaire
    texteOui.at(xx+0.71*x,yy+0.57*y); fenetre << texteOui;  // Circuit primaire
  }

  if(interventionCentrale == 0) // intervention dans toute la centrale impossible
  {
    texteNon.at(xx+0.71*x,yy+0.2*y); fenetre << texteNon; // Pompe secondaire
    texteNon.at(xx+0.24*x,yy+0.38*y); fenetre << texteNon;  // Condenseur
    texteNon.at(xx+0.71*x,yy+0.38*y); fenetre << texteNon; // Génératuer vapeur
    texteNon.at(xx+0.24*x,yy+0.565*y); fenetre << texteNon;  // Injecteur
    texteNon.at(xx+0.24*x,yy+0.745*y); fenetre << texteNon; // Circuit secondaire
    texteNon.at(xx+0.71*x,yy+0.745*y); fenetre << texteNon;  // Pressuriseur
  }
  else
  {
    texteOui.at(xx+0.71*x,yy+0.2*y); fenetre << texteOui; // Pompe secondaire
    texteOui.at(xx+0.24*x,yy+0.38*y); fenetre << texteOui;  // Condenseur
    texteOui.at(xx+0.71*x,yy+0.38*y); fenetre << texteOui; // Génératuer vapeur
    texteOui.at(xx+0.24*x,yy+0.565*y); fenetre << texteOui;  // Injecteur
    texteOui.at(xx+0.24*x,yy+0.745*y); fenetre << texteOui; // Circuit secondaire
    texteOui.at(xx+0.71*x,yy+0.745*y); fenetre << texteOui;  // Pressuriseur
  }

  sdl2::texte texteOuvriersDispo(snbOuvriersDispo, fonte_texte, fenetre, {0x00,0x00,0x00,0x00});
  texteOuvriersDispo.at(xx+0.625*x,yy+0.91*y);
  fenetre << texteOuvriersDispo;

  sdl2::texte textePompePrimOuvriers(souvriersPompePrim, fonte_texte, fenetre, {0x00,0x00,0x00,0x00});
  sdl2::texte textePompeSecOuvriers(souvriersPompeSec, fonte_texte, fenetre, {0x00,0x00,0x00,0x00});
  sdl2::texte texteCondenseurOuvriers(souvriersCondenseur, fonte_texte, fenetre, {0x00,0x00,0x00,0x00});
  sdl2::texte texteGenerateurOuvriers(souvriersGenerateur, fonte_texte, fenetre, {0x00,0x00,0x00,0x00});
  sdl2::texte texteInjecteurOuvriers(souvriersInjecteur, fonte_texte, fenetre, {0x00,0x00,0x00,0x00});
  sdl2::texte texteCircuitPrimOuvriers(souvriersCircuitPrim, fonte_texte, fenetre, {0x00,0x00,0x00,0x00});
  sdl2::texte texteCircuitSecOuvriers(souvriersCircuitSec, fonte_texte, fenetre, {0x00,0x00,0x00,0x00});
  sdl2::texte textePressuriseurOuvriers(souvriersPressuriseur, fonte_texte, fenetre, {0x00,0x00,0x00,0x00});

 // placement du texte dans le cadran
  textePompePrimOuvriers.at(xx+0.39*x,yy+0.26*y);
  textePompeSecOuvriers.at(xx+0.86*x,yy+0.26*y);
  texteCondenseurOuvriers.at(xx+0.39*x,yy+0.44*y);
  texteGenerateurOuvriers.at(xx+0.86*x,yy+0.44*y);
  texteInjecteurOuvriers.at(xx+0.39*x,yy+0.62*y);
  texteCircuitPrimOuvriers.at(xx+0.86*x,yy+0.62*y);
  texteCircuitSecOuvriers.at(xx+0.39*x,yy+0.805*y);
  textePressuriseurOuvriers.at(xx+0.86*x,yy+0.805*y);

  fenetre << textePompePrimOuvriers << textePompeSecOuvriers << texteCondenseurOuvriers << texteGenerateurOuvriers << texteInjecteurOuvriers << texteCircuitPrimOuvriers << texteCircuitSecOuvriers << textePressuriseurOuvriers;
  fenetre << sdl2::flush;
}


void PosteDeSecurite::interventionOuvriers(sdl2::window& fenetre, Centrale& centrale)
{
  bool quitter = false;
  bool iskey_down = false;
  sdl2::event_queue queue;

  while (not quitter)
  {
    auto events = queue.pull_events();
    for (const auto& e : events)
    {
      if ((e->kind_of_event() == sdl2::event::key_down) || (e->kind_of_event() == sdl2::event::key_up))
      {
        auto& key_ev = dynamic_cast<sdl2::event_keyboard&>(*e);

        if ((e->kind_of_event() == sdl2::event::key_down) &&  (iskey_down == false))
        {
          switch (key_ev.code())
          {
              case 49 : //1
                if(ouvriers.InterventionEnCours("pompe primaire") == false) // on regarde si des ouvriers sont déjà en intervention
                  ouvriers.envoyerOuvriers("pompe primaire",centrale); // on envoie les ouvriers
                else
                  ouvriers.annulerIntervention("pompe primaire");//on rappelle les ouvriers
                break;

              case 50 :  //2
                if(ouvriers.InterventionEnCours("pompe secondaire") == false)
                  ouvriers.envoyerOuvriers("pompe secondaire",centrale);
                else
                  ouvriers.annulerIntervention("pompe secondaire");
                break;

              case 99 : //c
                if(ouvriers.InterventionEnCours("condenseur") == false)
                  ouvriers.envoyerOuvriers("condenseur",centrale);
                else
                  ouvriers.annulerIntervention("condenseur");
                break;

              case 103 : //g
                if(ouvriers.InterventionEnCours("generateur de vapeur") == false)
                  ouvriers.envoyerOuvriers("generateur de vapeur",centrale);
                else
                  ouvriers.annulerIntervention("generateur de vapeur");
                break;

              case 97 : //a
                if(ouvriers.InterventionEnCours("injecteur Bore") == false)
                  ouvriers.envoyerOuvriers("injecteur Bore",centrale);
                else
                  ouvriers.annulerIntervention("injecteur Bore");
                break;

              case 105 : //i
                if(ouvriers.InterventionEnCours("circuit primaire") == false)
                  ouvriers.envoyerOuvriers("circuit primaire",centrale);
                else
                  ouvriers.annulerIntervention("circuit primaire");
                break;

              case 114 : //r
                if(ouvriers.InterventionEnCours("circuit secondaire") == false)
                  ouvriers.envoyerOuvriers("circuit secondaire",centrale);
                else
                  ouvriers.annulerIntervention("circuit secondaire");
                break;

              case 112 : //p
                if(ouvriers.InterventionEnCours("pressuriseur") == false)
                  ouvriers.envoyerOuvriers("pressuriseur",centrale);
                else
                  ouvriers.annulerIntervention("pressuriseur");
                break;

                case 13 : // on quitte la boucle en appuyant sur entrer
                  quitter = true;
                  break;
           }
              majAffichage(fenetre, centrale);
              iskey_down = true;
        }
          if (key_ev.type_of_event() == sdl2::event::key_up)
          iskey_down = false;
      }
    }
  }
}


bool PosteDeSecurite::evacuationPossible() const  // Renvoie true si l'évacuation a commencé, false sinon
{
  return m_evacuation;
}


void PosteDeSecurite::majOuvriers(Centrale& centrale) //mise à jour des ouvriers
{
  ouvriers.majEtatSante(centrale); // met à jour l'état de santé
  ouvriers.reparer(centrale); // met à jour les réparations faites par les ouvriers
  ouvriers.guerir(); // met à jour la guérison des ouvriers
  ouvriers.rappelerOuvriers(centrale);  // Rappelle les ouvriers en mission
}


PosteDeSecurite::~PosteDeSecurite()
{

}
