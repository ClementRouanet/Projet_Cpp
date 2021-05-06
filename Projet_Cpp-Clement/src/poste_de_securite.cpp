#include <iostream>
#include <string>
#include <chrono>
#include <thread>

#include "poste_de_securite.hpp"

using namespace std;

PosteDeSecurite::PosteDeSecurite() : m_schemaCentrale(false)
{

}

void PosteDeSecurite::majAffichage(sdl2::window& fenetre, Centrale& centrale) // Met à jour l'affichage de la fenêtre graphique
{


  cadre(fenetre);
  affichageReacteur(fenetre,centrale); // Affichage du réacteur (état canaux, barres de graphite, piscine et cuve)
  affichageCircuitPrim(fenetre,centrale);  // Affiche le circuit primaire (état, pompe, pressuriseur, résistances électriques et l'injecteur)
  affichageCircuitSec(fenetre,centrale); //Affiche le circuit secondaire (état, pompe, générateur de vapeur, échangeur de chaleur)
  affichageEnceinteConfinement( fenetre,centrale);  // Affiche l'état de l'enceinte de confinement
  affichageCondenseur(fenetre,centrale); // Affiche l'état du condenseur
  affichageOuvriers(fenetre); // Affiche les effectifs humains à notre disposition
  affichageActivite(fenetre,centrale); // Affiche le signalement de divers niveaux de contaminations
  affichageOrdinateur(fenetre,centrale); // Affiche l'état courant de la centrale et des alentours
  affichageCommandes(fenetre,centrale);  // Affiche les commandes disponibles pour effectuer des actions

  if(m_schemaCentrale == true)
    affichageSchemaCentrale(fenetre, centrale);

  fenetre << sdl2::flush;
}



void PosteDeSecurite::cadre(sdl2::window& fenetre) const // Affiche un cadre
{
  sdl2::image cadre("image/Cadre_SalleDeControle.jpg", fenetre);
  auto [wph, hph] = fenetre.dimensions();
  cadre.stretch({wph,hph});

  fenetre << cadre;
}


void PosteDeSecurite::affichageSchemaCentrale(sdl2::window& fenetre, Centrale& centrale)
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


void PosteDeSecurite::schemaCentrale(sdl2::window& fenetre, Centrale& centrale)
{
  double etatCentrale = centrale.etatCentrale();
  double etatReacteur = centrale.etatCuve();
  double etatCircuitPrim = centrale.etatCircuitPrim();
  double etatCircuitSec = centrale.etatCircuitSec();
  double etatCondenseur = centrale.etatCondenseur();

  auto [wph, hph] = fenetre.dimensions();

  sdl2::image schema("image/Centrale nucleaire.jpg", fenetre);
  schema.stretch({4*wph/6,4*hph/6});
  schema.at(wph/6,hph/6);

  sdl2::image centraleNucl("image/Centrale.png", fenetre);
  centraleNucl.stretch({4*wph/6,4*hph/6});
  centraleNucl.at(wph/6,hph/6);

  sdl2::image reacteur("image/Reacteur.png", fenetre);
  reacteur.stretch({4*wph/6,4*hph/6});
  reacteur.at(wph/6,hph/6);

  sdl2::image circuitPrim("image/Circuit_primaire.png", fenetre);
  circuitPrim.stretch({4*wph/6,4*hph/6});
  circuitPrim.at(wph/6,hph/6);

  sdl2::image circuitSec("image/Circuit_secondaire.png", fenetre);
  circuitSec.stretch({4*wph/6,4*hph/6});
  circuitSec.at(wph/6,hph/6);

  sdl2::image condenseur("image/Circuit_refroidissement.png", fenetre);
  condenseur.stretch({4*wph/6,4*hph/6});
  condenseur.at(wph/6,hph/6);

  fenetre << schema << sdl2::flush;

  this_thread::sleep_for(chrono::milliseconds(500));

  if(etatCentrale < 0.5)
    fenetre << centraleNucl;

  if(etatReacteur < 0.3)
    fenetre << reacteur;

  if(etatCircuitPrim < 0.3)
    fenetre << circuitPrim;

  if(etatCircuitSec < 0.3)
    fenetre << circuitSec;

  if(etatCondenseur < 0.3)
    fenetre << condenseur;

  fenetre << sdl2::flush;

  this_thread::sleep_for(chrono::milliseconds(400));
}


//----------------------------------------------CADRAN REACTEUR --------------------------------------------------------------//
void PosteDeSecurite::affichageReacteur(sdl2::window& fenetre, Centrale& centrale) const // Affichage du réacteur (état canaux, barres de graphite, piscine et cuve)
{
  double EtatCanaux = centrale.etatCanaux();
  double EtatBarresGr = centrale.etatBarresGr();
  double EtatPiscine = centrale.etatPiscine();
  double EtatCuve = centrale.etatCuve();

  string sEtatCanaux(to_string(EtatCanaux));
  string sEtatBarresGr(to_string(EtatBarresGr));
  string sEtatPiscine(to_string(EtatPiscine));
  string sEtatCuve(to_string(EtatCuve));


  auto [x, y] = fenetre.dimensions();
  //Ajouter la fonte du titre et des textes
  sdl2::font fonte_texte("./data/Lato-Bold.ttf",20);

  sdl2::texte texteCanaux("Etat des canaux guidant les barres : " + sEtatCanaux, fonte_texte, fenetre, {0x00,0x00,0x00,0x00});
  sdl2::texte texteBarresGr("Etat des Barres de Graphite : " + sEtatBarresGr, fonte_texte, fenetre, {0x00,0x00,0x00,0x00});
  sdl2::texte textePiscine("Etat de la Piscine : " + sEtatPiscine, fonte_texte, fenetre, {0x00,0x00,0x00,0x00});
  sdl2::texte texteCuve("Etat de la Cuve : " + sEtatCuve, fonte_texte, fenetre, {0x00,0x00,0x00,0x00});

  //Placement dans le cadran : On change après encore
  texteCanaux.at(2*x/5-20,140);
  texteBarresGr.at(2*x/5-20,180);
  textePiscine.at(2*x/5-20,220);
  texteCuve.at(2*x/5-20,260);

  fenetre<<texteCanaux<<texteBarresGr<<textePiscine<<texteCuve;
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

 sdl2::texte texteCircuit("Etat du Circuit : " + sEtatCircuit, fonte_texte, fenetre, {0x00,0x00,0x00,0x00});
 sdl2::texte textePompe("Etat de la pompe : " + sEtatPompe, fonte_texte, fenetre, {0x00,0x00,0x00,0x00});
 sdl2::texte textePressuriseur("Etat du Pressuriseur : " + sEtatPressuriseur, fonte_texte, fenetre, {0x00,0x00,0x00,0x00});
 sdl2::texte texteResistance("Etat de la Resistance du Pressuriseur : " + sEtatResistancePressuriseur, fonte_texte, fenetre, {0x00,0x00,0x00,0x00});

 //Placement dans le cadran : On change après encore
 texteCircuit.at(2*x/5-20,140);
 textePompe.at(2*x/5-20,180);
 textePressuriseur.at(2*x/5-20,220);
 texteResistance.at(2*x/5-20,260);

 fenetre<<texteCircuit<<textePompe<<textePressuriseur<<texteResistance;
}




//-----------------------------------------------------CADRAN CIRCUIT SECONDAIRE----------------------------------- ------------------------//
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

  sdl2::texte texteCircuit("Etat du Circuit : " + sEtatCircuit, fonte_texte, fenetre, {0x00,0x00,0x00,0x00});
  sdl2::texte textePompe("Etat de la pompe : " + sEtatPompe, fonte_texte, fenetre, {0x00,0x00,0x00,0x00});
  sdl2::texte texteGenerateurVapeur("Etat du Generateur de Vapeur : " + sEtatGenerateurVapeur, fonte_texte, fenetre, {0x00,0x00,0x00,0x00});
  sdl2::texte texteEchangeurChaleur("Etat de l'Echangeur de Chaleur : " + sEtatEchangeurChaleur, fonte_texte, fenetre, {0x00,0x00,0x00,0x00});

  //Placement dans le cadran : On change après encore
  texteCircuit.at(2*x/5-20,140);
  textePompe.at(2*x/5-20,180);
  texteGenerateurVapeur.at(2*x/5-20,220);
  texteEchangeurChaleur.at(2*x/5-20,260);

  fenetre<<texteCircuit<<textePompe<<texteGenerateurVapeur<<texteEchangeurChaleur;
}



//----------------------------CADRAN ENCEINTE --------------------------------------//
 // Affiche l'état de l'enceinte de confinement
void PosteDeSecurite::affichageEnceinteConfinement(sdl2::window& fenetre,Centrale& centrale) const
{
 double EtatEnceinte = centrale.etatEnceinte();
 string sEtatEnceinte(to_string(EtatEnceinte));

 auto [x, y] = fenetre.dimensions();
 //Ajouter la fonte du titre et des textes
 sdl2::font fonte_texte("./data/Lato-Bold.ttf",20);

 sdl2::texte texteEnceinte("Etat de l'Enceinte : " + sEtatEnceinte, fonte_texte, fenetre, {0x00,0x00,0x00,0x00});

 //Placement dans le cadran : On change après encore
 texteEnceinte.at(2*x/5-20,140);

 fenetre<<texteEnceinte;
}

//-----------------------------------CADRAN CONDENSEUR--------------------------------------------//
// Affiche l'état du condenseur
void PosteDeSecurite::affichageCondenseur(sdl2::window& fenetre,Centrale& centrale) const
{
  double EtatCondenseur = centrale.etatCondenseur();
  string sEtatCondenseur(to_string(EtatCondenseur));

  auto [x, y] = fenetre.dimensions();
  //Ajouter la fonte du titre et des textes
  sdl2::font fonte_texte("./data/Lato-Bold.ttf",20);

  sdl2::texte texteCondenseur("Etat du Condenseur : " + sEtatCondenseur, fonte_texte, fenetre, {0x00,0x00,0x00,0x00});

  //Placement dans le cadran : On change après encore
  texteCondenseur.at(2*x/5-20,140);

  fenetre<<texteCondenseur;
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
  sdl2::font fonte_texte("./data/Lato-Bold.ttf",20);

  sdl2::texte texteOuvriersDispo("OuvriersDispo : " + sOuvriersDispo, fonte_texte, fenetre, {0x00,0x00,0x00,0x00});
  sdl2::texte texteOuvriersEnIntervention("OuvriersEnIntervention : " + sOuvriersEnIntervention, fonte_texte, fenetre, {0x00,0x00,0x00,0x00});
  sdl2::texte texteOuvriersBlesses("OuvriersBlesses : " + sOuvriersBlesses, fonte_texte, fenetre, {0x00,0x00,0x00,0x00});


  //Placement dans le cadran : On change après encore
  texteOuvriersDispo.at(2*x/5-20,140);
  texteOuvriersEnIntervention.at(2*x/5-20,180);
  texteOuvriersBlesses.at(2*x/5-20,220);


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
  string sRadioactiviteEnceinte(to_string(radioactiviteEnceinte));
  string sRadioactiviteAir(to_string(radioactiviteAir));
  string sRadioactiviteEau(to_string(radioactiviteEau));


  auto [x, y] = fenetre.dimensions();
  //Ajouter la fonte du titre et des textes
  sdl2::font fonte_texte("./data/Lato-Bold.ttf",20);

  sdl2::texte texteRadioactivitePiscine("RadioactivitePiscine : " + sRadioactivitePiscine, fonte_texte, fenetre, {0x00,0x00,0x00,0x00});
  sdl2::texte texteRadioactiviteEnceinte("RadioactiviteEnceinte : " + sRadioactiviteEnceinte, fonte_texte, fenetre, {0x00,0x00,0x00,0x00});
  sdl2::texte texteRadioactiviteAir("RadioactiviteAir : " + sRadioactiviteAir, fonte_texte, fenetre, {0x00,0x00,0x00,0x00});
  sdl2::texte texteRadioactiviteEau("RadioactiviteEau : " + sRadioactiviteEau, fonte_texte, fenetre, {0x00,0x00,0x00,0x00});

  //Placement dans le cadran : On change après encore
  texteRadioactivitePiscine.at(2*x/5-20,140);
  texteRadioactiviteEnceinte.at(2*x/5-20,180);
  texteRadioactiviteAir.at(2*x/5-20,220);
  texteRadioactiviteEau.at(2*x/5-20,260);

  fenetre<<texteRadioactivitePiscine<<texteRadioactiviteEnceinte<<texteRadioactiviteAir<<texteRadioactiviteEau;
}


//------------------------------------------CADRAN ORDINATEUR --------------------------------------------------//
void PosteDeSecurite::affichageOrdinateur(sdl2::window& fenetre,Centrale& centrale) const // Affiche l'état courant de la centrale et des alentours
{
  double EtatCentrale = centrale.etatCentrale();
  int Contamination = centrale.contamination();
  //affichage du niveau d'alerte
  //affichage des ouvriers actifs ou non
  string sEtatCentrale(to_string(EtatCentrale));
  string sContamination(to_string(Contamination));
  //string niveau d'alerte
  //string ouvriers (et pas string des ouvriers lol)


  auto [x, y] = fenetre.dimensions();
  //Ajouter la fonte du titre et des textes
  sdl2::font fonte_texte("./data/Lato-Bold.ttf",20);

  sdl2::texte texteCentrale("Etat de la Centrale : " + sEtatCentrale, fonte_texte, fenetre, {0x00,0x00,0x00,0x00});

  //Placement dans le cadran : On change après encore
  texteCentrale.at(2*x/5-20,140);

  fenetre<<texteCentrale;
}





//--------------------------------------------------AFFICHAGE COMMANDE ------------------------------------//
void PosteDeSecurite::affichageCommandes(sdl2::window& fenetre,Centrale& centrale) const  // Affiche les commandes disponibles pour effectuer des actions
{
  auto [wph, hph] = fenetre.dimensions();

  sdl2::font fonte_texte("./data/Lato-Bold.ttf",20);

  sdl2::texte texteTab("Tab : affiche schéma centrale", fonte_texte, fenetre, {0x00,0x00,0x00,0x00});
  sdl2::texte texteEspace("Espace : passer salle de contrôle", fonte_texte, fenetre, {0x00,0x00,0x00,0x00});
  sdl2::texte texteB1("B :  Bilan actiivité ouvrière", fonte_texte, fenetre, {0x00,0x00,0x00,0x00});
  sdl2::texte texteP1("P :  Demande évacuation population", fonte_texte, fenetre, {0x00,0x00,0x00,0x00});
  sdl2::texte texteO("O : Interventions ouvrier", fonte_texte, fenetre, {0x00,0x00,0x00,0x00});

  sdl2::texte texte1("1 :  pompe circuit primaire", fonte_texte, fenetre, {0x00,0x00,0x00,0x00});
  sdl2::texte texte2("2 :  pompe circuit secondaire", fonte_texte, fenetre, {0x00,0x00,0x00,0x00});
  sdl2::texte texteB2("B :  injecteur d'acide borique", fonte_texte, fenetre, {0x00,0x00,0x00,0x00});
  sdl2::texte texteP2("P :  pressuriseur", fonte_texte, fenetre, {0x00,0x00,0x00,0x00});
  sdl2::texte texteI("I : circuit primaire", fonte_texte, fenetre, {0x00,0x00,0x00,0x00});
  sdl2::texte texteR("R : circuit secondaire", fonte_texte, fenetre, {0x00,0x00,0x00,0x00});
  sdl2::texte texteG("G  : générateur de vapeur", fonte_texte, fenetre, {0x00,0x00,0x00,0x00});
  sdl2::texte texteC("C  : Condenseur", fonte_texte, fenetre, {0x00,0x00,0x00,0x00});


texteTab.at(3*wph/4,330);
texteEspace.at(3*wph/4,330);
texteB1.at(3*wph/4,330);
texteP1.at(3*wph/4,330);
texteO.at(3*wph/4,330);
texte1.at(3*wph/4,330);
texte2.at(3*wph/4,330);
texteB2.at(3*wph/4,330);
texteP2.at(3*wph/4,330);
texteI.at(3*wph/4,330);
texteR.at(3*wph/4,330);
texteG.at(3*wph/4,330);
texteC.at(3*wph/4,330);



  fenetre << texteTab << texteEspace << texteB1 << texteP1 << texteO << texte1 << texte2 << texteB2 << texteP2 << texteI << texteR << texteG << texteC;

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

        case 111 :  // o comme olivier
          interventionOuvriers(fenetre, centrale);
          break;

      }
    return sortie;
}


void PosteDeSecurite::evacuationPopulation(sdl2::window& fenetre, Centrale& centrale)
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
              case 13 ://entrer
              centrale.majEvacuation();
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

void PosteDeSecurite::afficherBilan(sdl2::window& fenetre, Centrale& centrale)
{
  int interventionPrimaire = ouvriers.interventionPossible(centrale,"circuit primaire");
  int interventionCentrale = ouvriers.interventionPossible(centrale,"centrale");

  int nbOuvriersDispo = ouvriers.getNombreOuvriersDispo();
  string snbOuvriersDispo(to_string(nbOuvriersDispo));

  int ouvriersPompePrim = ouvriers.nombreEnInterventionOrgane("pompe primaire");
  int ouvriersPompeSec = ouvriers.nombreEnInterventionOrgane("pompe secondaire");
  int ouvriersCondenseur = ouvriers.nombreEnInterventionOrgane("condenseur");
  int ouvriersGenerateur = ouvriers.nombreEnInterventionOrgane("generateur de vapeur");
  int ouvriersInjecteur = ouvriers.nombreEnInterventionOrgane("injecteur Bore");
  int ouvriersCircuitPrim = ouvriers.nombreEnInterventionOrgane("circuit primaire");
  int ouvriersCircuitSec = ouvriers.nombreEnInterventionOrgane("circuit secondaire");
  int ouvriersPressuriseur = ouvriers.nombreEnInterventionOrgane("pressuriseur");

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

  sdl2::texte texteOui("oui", fonte_texte, fenetre, {0x00,0xFF,0x00,0x00});
  sdl2::texte texteNon("non", fonte_texte, fenetre, {0xFF,0x00,0x00,0x00});

  if(interventionPrimaire == 0 || interventionCentrale == 0)
  {
    texteNon.at(xx+0.24*x,yy+0.2*y); fenetre << texteNon; // Pompe primaire
    texteNon.at(xx+0.71*x,yy+0.57*y); fenetre << texteNon;  // Circuit primaire
  }
  else
  {
    texteOui.at(xx+0.24*x,yy+0.2*y); fenetre << texteOui; // Pompe primaire
    texteOui.at(xx+0.71*x,yy+0.57*y); fenetre << texteOui;  // Circuit primaire
  }

  if(interventionCentrale == 0)
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
                if(ouvriers.InterventionEnCours("pompe primaire") == false)
                  ouvriers.envoyerOuvriers("pompe primaire",centrale);
                else
                  ouvriers.annulerIntervention("pompe primaire");
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

              case 98 : //b
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

                case 13 :
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


PosteDeSecurite::~PosteDeSecurite()
{

}
