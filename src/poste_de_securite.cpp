#include <iostream>
#include <string>

#include "poste_de_securite.hpp"
#include "centrale.hpp"
#include "circuit_primaire.hpp"
#include "circuit_secondaire.hpp"
#include "ouvriers.hpp"
#include "sdl2.hpp"

using namespace std;

PosteDeSecurite::PosteDeSecurite()
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
  affichageOuvriers(fenetre,ouvriers); // Affiche les effectifs humains à notre disposition
  affichageActivite(fenetre,centrale); // Affiche le signalement de divers niveaux de contaminations
  affichageOrdinateur(fenetre,centrale); // Affiche l'état courant de la centrale et des alentours
  affichageCommandes(fenetre,centrale);  // Affiche les commandes disponibles pour effectuer des actions

  if(m_schemaCentrale == true)
  {
    affichageSchemaCentrale(fenetre, centrale);
  }

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

void PosteDeSecurite::affichageOuvriers(sdl2::window& fenetre,Ouvriers& ouvriers) const // Affiche les effectifs humains à notre disposition
{
  int ouvriersDispo = ouvriers.getNombreOuvriersDispo();
  int ouvriersEnIntervention = ouvriers.nombreEnIntervention()
  //int ouvriersBlesses = ouvriers.nombreBlesses();

  string sOuvriersDispo(to_string(ouvriersDispo));
  string sOuvriersEnIntervention(to_string(ouvriersEnIntervention));
  //string sOuvriersBlesses(to_string(ouvriersBlesses));


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


  fenetre<<texteOuvriersDispo<<texteOuvriersEnIntervention;//<<texteOuvriersBlesses

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



  fenetre << texte << texteTab << texteEspace << texteB1 << texteP1 << texteO << texte1 << texte2 << texteB2 << texteP2 << texteI << texteR << texteG << texteC;

}


bool PosteDeSecurite::majCommandes(sdl2::window& fenetre, int touche, Centrale& centrale, Ouvriers& ouvriers)
{
      switch (touche)
      {
        case 9 :  // tab
          m_schemaCentrale = true;
          break;

        case 32 : // Espace
          sortie = true;
          break;

        case 112 :  // p
          evacuationPopulation(fenetre, centrale);
          break;

        case 98 :  // b
          bilanOuvriers(fenetre, centrale, ouvriers); //Cette commande affiche les différents organes où sont potentiellement réalisable des interventions humaines
          break;

        case 111 :  // o comme olivier
          interventionOuvriers(fenetre, centrale, ouvriers);
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
              majEvacuation();
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

void PosteDeSecurite::bilanOuvriers(sdl2::window& fenetre, Centrale& centrale,Ouvriers& ouvriers)
{

}

void PosteDeSecurite::interventionOuvriers(sdl2::window& fenetre, Centrale& centrale,Ouvriers& ouvriers)
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
             //J'attends les autres fonctions les kheys
              case 49 : //1
              ouvriers.envoyerOuvriers(pompe primaire,centrale);
              break;

              case 50 :  //2
              ouvriers.envoyerOuvriers(pompe secondaire,centrale);
              break;

              case 99 : //c
              ouvriers.envoyerOuvriers(condenseur,centrale);
              break;

              case 103 : //g
              ouvriers.envoyerOuvriers(generateur de vapeur,centrale);;
              break;

              case 98 : //b
              ouvriers.envoyerOuvriers(injecteur Bore,centrale);
              break;

              case 105 : //i
              ouvriers.envoyerOuvriers(circuit primaire,centrale);
              break;

              case 114 : //r
              ouvriers.envoyerOuvriers(circuit secondaire,centrale);
              break;

              case 112 : //p
              ouvriers.envoyerOuvriers(pressuriseur,centrale);
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
