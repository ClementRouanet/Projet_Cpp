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
 // Affiche l'état de l'enceinte de confinement
void PosteDeSecurite::affichageEnceinteConfinement(sdl2::window& fenetre,Centrale& centrale) const
{
 double EtatEnceinte = centrale.etatEnceinte();
 string sEtatEnceinte(to_string(EtatEnceinte));

 auto [x, y] = fenetre.dimensions();
 //Ajouter la fonte du titre et des textes
 sdl2::font fonte_texte("./data/Lato-Bold.ttf",20);
 sdl2::font fonte_titre("./data/Lato-Bold.ttf",30);

 sdl2::texte titre("Enceinte", fonte_titre, fenetre, {0x00,0x00,0xFF,0x00});
 sdl2::texte texteEnceinte("Etat de l'Enceinte : " + sEtatEnceinte, fonte_texte, fenetre, {0x00,0x00,0x00,0x00});

 //Placement dans le cadran : On change après encore
 titre.at(2*x/5+60, 80);
 texteEnceinte.at(2*x/5-20,140);

 fenetre<<titre<<texteEnceinte;
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
  sdl2::font fonte_titre("./data/Lato-Bold.ttf",30);

  sdl2::texte titre("Condenseur", fonte_titre, fenetre, {0x00,0x00,0xFF,0x00});
  sdl2::texte texteCondenseur("Etat du Condenseur : " + sEtatEnceinte, fonte_texte, fenetre, {0x00,0x00,0x00,0x00});

  //Placement dans le cadran : On change après encore
  titre.at(2*x/5+60, 80);
  texteCondenseur.at(2*x/5-20,140);

  fenetre<<titre<<texteCondenseur;
}

void PosteDeSecurite::affichageOuvriers() const // Affiche les effectifs humains à notre disposition
{

}

void PosteDeSecurite::affichageActivite() const // Affiche le signalement de divers niveaux de contaminations
{

}

void PosteDeSecurite::affichageOrdinateur() const // Affiche l'état courant de la centrale et des alentours
{
  double EtatCentrale = centrale.EtatCentrale();
  string sEtatCentrale(to_string(EtatCentrale));

  auto [x, y] = fenetre.dimensions();
  //Ajouter la fonte du titre et des textes
  sdl2::font fonte_texte("./data/Lato-Bold.ttf",20);
  sdl2::font fonte_titre("./data/Lato-Bold.ttf",30);

  sdl2::texte titre("Centrale", fonte_titre, fenetre, {0x00,0x00,0xFF,0x00});
  sdl2::texte texteCentrale("Etat de la Centrale : " + sEtatCentrale, fonte_texte, fenetre, {0x00,0x00,0x00,0x00});

  //Placement dans le cadran : On change après encore
  titre.at(2*x/5+60, 80);
  texteCentrale.at(2*x/5-20,140);

  fenetre<<titre<<texteCentrale;
}

void PosteDeSecurite::affichageCommandes() const  // Affiche les commandes disponibles pour effectuer des actions
{
  auto [wph, hph] = fenetre.dimensions();

  sdl2::font fonte_texte("./data/Lato-Bold.ttf",20);
  sdl2::font fonte_titre("./data/Lato-Bold.ttf",30);

  sdl2::texte texte("Commandes", fonte_titre, fenetre, {0x00,0x00,0xFF,0x00});
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

bool PosteDeSecurite::majCommandes(sdl2::window& fenetre, int touche, Centrale& centrale)
{
      switch (touche)
      {
        case 9 :  // tab
          affichageSchemaCentrale(fenetre, centrale);
          break;

        case 32 : // Espace
          passagePosteSecurite(fenetre, centrale);
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
      return false;
}

void PosteDeSecurite::evacuationPopulation(sdl2::window& fenetre, Centrale& centrale)
{

}

void PosteDeSecurite::bilanOuvrier(sdl2::window& fenetre, Centrale& centrale)
{

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
              case 13 ://entrer
              quitter = true;
              break;


             //J'attends les autres fonctions les kheys
              case 49 : //1
              quitter = true;
              break;

              case 50 :  //2
              quitter = true;
              break;

              case 99 : //c
              quitter = true;
              break;

              case 103 : //g
              quitter = true;
              break;

              case 98 : //b
              quitter = true;
              break;

              case 105 : //i
              quitter = true;
              break;

              case 114 : //r
              quitter = true;
              break;

              case 112 : //p
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
