#include <chrono>
#include <thread>
#include <vector>

#include "niveaux.hpp"
#include "catastrophe.hpp"

using namespace std;

/* Met a jour toutes les vriables de la centrale */
void miseAJour(Centrale& centrale, PosteDeSecurite& posteDeSecurite)
{
  centrale.majPressionEnceinte(); // Met à jour la Pression subit par l'enceinte de Confinement
  centrale.majRadioactiviteEnceinte(); // Met à jour la radioactivité de l'enceinte de confinement

  centrale.majEtatCentrale(); // Met à jour l'état général de la centrale
  centrale.majProductionCentrale(); // Met à jour la production générale de la centrale
  centrale.madProductionTotale();  //Met à jour la production totale de la centrale

  centrale.majTempPressuriseurActuel();  // Met à jour la température du pressuriseur actuel
  centrale.majPressionEau(); // Met à jour la pression de l'eau
  centrale.majDebitEauPrim(); // Met à jour le débit de l'eau
  centrale.majInertietemperaturePrim(); // Met à jour l'inertie température eau circuit
  centrale.majTemperatureEau(); // Met à jour la température de l'eau dans le circuit
  centrale.majRadioactivitePrim();  // Met à jour la radioactivité du circuit

  centrale.majTemperatureVapeur();  // Met à jour la température de la vapeur
  centrale.majPressionVapeur(); // Met à jour la pression exercée par la vapeur
  centrale.majDebitEauSec(); // Met à jour le débit de l'eau
  centrale.majDebitCondenseur();  // Met à jour le débit au niveau du condenseur
  centrale.majDiffChaleurCondenseur();  // Met à jour la différence de chaleur entre l'entrée et la sortie du condenseur
  centrale.majInertieTemperatureSec(); // Met à jour l'inertie température eau circuit
  centrale.majRadioactivite();  // Met à jour la radioactivité du circuit

  centrale.majPropGrAct();  // Met à jour la proportion des barres de graphite hors de l'eau demandé
  centrale.majTauxBoreAct();  // Met à jour le taux de borre demandé dans l'eau du cirucit
  centrale.majRadPiscine(); // Met à jour la radiation de la piscine

  posteDeSecurite.majOuvriers(centrale);  // Met à jour les différentes fonctions des ouvriers
}


/* Niveau 1 du jeu */
int niveau1(sdl2::window& fenetre, Centrale& centrale, SalleDeControle& salleDeControle, PosteDeSecurite& posteDeSecurite)
{
  salleDeControle.niveau(1);  // Donne le niveau de jeu à la salle de contrôle pour le dispatching

  int nbTour = 0; // Initialisation du nombre de tours du jeu
  vector<int> sortie = {0, 0}; // Premier : changement poste/salle, second : fin session

  bool iskey_down = false;  // Vaut faux si la touche n'est pas enfoncée, vrai sinon
  sdl2::event_queue queue;

  while (sortie[1] == 0) // Tant qu'on ne clique pas sur la croix ou qu'on n'arrete pas le jeu (touche 'S')
  {
    // Boucle salle de contrôle
    while (sortie[0] == 0 && sortie[1] == 0)  // Tant qu'on arrete pas le jeu ('croix' ou 'S') et qu'on n'appuie pas sur 'Espace'
    {
      auto start = chrono::system_clock::now(); // Prend l'heure qu'il est actuellement (au début de la boucle)

      salleDeControle.majAffichage(fenetre, centrale);  // Affiche la fenetre et les textes de la salle de contrôle

      auto events = queue.pull_events();
      for ( const auto& e : events) // On regarde chaque évènements(touche, clic, ...)
      {
        if (e->kind_of_event() == sdl2::event::quit) // Si on clique sur la croix pour fermer la fenetre
          sortie[1] = 1;

        // Si l'évènement et de type 'clavier' et qu'il s'agit d'une touche enfoncée ou relevée
        if ((e->kind_of_event() == sdl2::event::key_down) || (e->kind_of_event() == sdl2::event::key_up))
        {
          auto& key_ev = dynamic_cast<sdl2::event_keyboard&>(*e);

          if ((e->kind_of_event() == sdl2::event::key_down) &&  (iskey_down == false)) // Si touche enfoncée et non relachée
          {
            sortie = salleDeControle.majCommandes(fenetre, key_ev.code(), centrale);  // Actionne les fonctionnalités des touches de la salle de contrôle
            iskey_down = true;
          }
          if (key_ev.type_of_event() == sdl2::event::key_up)  // Si touche relachée
            iskey_down = false;
        }
      }
      miseAJour(centrale, posteDeSecurite); // Met à jour toutes les variables de la centrale
      nbTour += 1;  // Incrémentation du nombre de tour

      auto end = chrono::system_clock::now(); // Prend l'heure qu'il est actuellement (à la fin de la boucle)
      chrono::duration<double> secondesEcoulees = end - start;  // Différence pour avoir le temps d'exécution de la boucle while en secondes
      int tps = 1000 - floor(secondesEcoulees.count()*1000);  // Conversion du temps en millisecondes

      if (secondesEcoulees.count() < 1) // Si l'exécution de la boucle a duré moins d'une seconde
        this_thread::sleep_for(chrono::milliseconds(tps));  // Alors on attend pour qu'une itération de la boucle while dure 1 seconde
    }
    sortie[0] = 0;  // On remet la touche 'Espace' à zéro pour pouvoir rentrer dans le poste de sécurité

    // Boucle poste de securite
    while (sortie[0] == 0 && sortie[1] == 0)  // Tant qu'on arrete pas le jeu ('croix') et qu'on n'appuie pas sur 'Espace'
    {
      auto start = chrono::system_clock::now(); // Prend l'heure qu'il est actuellement (au début de la boucle)

      posteDeSecurite.majAffichage(fenetre, centrale);  // Affiche la fenetre et les textes du poste de sécurité

      auto events = queue.pull_events();
      for ( const auto& e : events) // On regarde chaque évènements(touche, clic, ...)
      {
        if (e->kind_of_event() == sdl2::event::quit) // Si on clique sur la croix pour fermer la fenetre
          sortie[1] = 1;

        // Si l'évènement et de type 'clavier' et qu'il s'agit d'une touche enfoncée ou relevée
        if ((e->kind_of_event() == sdl2::event::key_down) || (e->kind_of_event() == sdl2::event::key_up))
        {
          auto& key_ev = dynamic_cast<sdl2::event_keyboard&>(*e);

          if ((e->kind_of_event() == sdl2::event::key_down) &&  (iskey_down == false))  // Si touche enfoncée et non relachée
          {
            sortie[0] = posteDeSecurite.majCommandes(fenetre, key_ev.code(), centrale);  // Actionne les fonctionnalités des touches du poste de sécurité
            iskey_down = true;
          }
          if (key_ev.type_of_event() == sdl2::event::key_up)  // Si touche relachée
            iskey_down = false;
        }
      }
      miseAJour(centrale, posteDeSecurite); // Met à jour toutes les variables de la centrale
      nbTour += 1;  // Incrémentation du nombre de tour

      auto end = chrono::system_clock::now(); // Prend l'heure qu'il est actuellement (à la fin de la boucle)
      chrono::duration<double> secondesEcoulees = end - start;  // Différence pour avoir le temps d'exécution de la boucle while en secondes
      int tps = 1000 - floor(secondesEcoulees.count()*1000);  // Conversion du temps en millisecondes

      if (secondesEcoulees.count() < 1) // Si l'exécution de la boucle a duré moins d'une seconde
        this_thread::sleep_for(chrono::milliseconds(tps));  // Alors on attend pour qu'une itération de la boucle while dure 1 seconde
    }

    sortie[0] = 0;  // On remet la touche 'Espace' à zéro pour pouvoir rentrer dans la salle de contrôle
  }

  return nbTour;  // On renvoie le nombre de tour du jeu
}


/* Niveau 2 du jeu */
int niveau2(sdl2::window& fenetre, Centrale& centrale, SalleDeControle& salleDeControle, PosteDeSecurite& posteDeSecurite)
{
  salleDeControle.niveau(2);  // Donne le niveau de jeu à la salle de contrôle pour le dispatching

  int nbTour = 0; // Initialisation du nombre de tours du jeu
  vector<int> sortie = {0, 0}; // Premier : changement poste/salle, second : fin session
  bool finDispatching = false;  // Vaut faux si c'est la fin du dispatching (score à 0 ou production nulle), vrai sinon

  bool iskey_down = false;  // Vaut faux si la touche n'est pas enfoncée, vrai sinon
  sdl2::event_queue queue;

  while (sortie[1] == 0 && not finDispatching) // Tant qu'on ne clique pas sur la croix ou qu'on n'arrete pas le jeu (touche 'S') ou non fin dispatching
  {
    // Boucle salle de commande
    while (sortie[0] == 0 && sortie[1] == 0 && not finDispatching)  // Tant qu'on arrete pas le jeu ('croix' ou 'S') et qu'on n'appuie pas sur 'Espace' ou non dispatching
    {
      auto start = chrono::system_clock::now(); // Prend l'heure qu'il est actuellement (au début de la boucle)

      salleDeControle.majAffichage(fenetre, centrale);  // Affiche la fenetre et les textes de la salle de contrôle

      auto events = queue.pull_events();
      for ( const auto& e : events) // On regarde chaque évènements(touche, clic, ...)
      {
        if (e->kind_of_event() == sdl2::event::quit) // Si on clique sur la croix pour fermer la fenetre
          sortie[1] = true;

        // Si l'évènement et de type 'clavier' et qu'il s'agit d'une touche enfoncée ou relevée
        if ((e->kind_of_event() == sdl2::event::key_down) || (e->kind_of_event() == sdl2::event::key_up))
        {
          auto& key_ev = dynamic_cast<sdl2::event_keyboard&>(*e);

          if ((e->kind_of_event() == sdl2::event::key_down) &&  (iskey_down == false))  // Si touche enfoncée et non relachée
          {
            sortie = salleDeControle.majCommandes(fenetre, key_ev.code(), centrale);  // Actionne les fonctionnalités des touches de la salle de contrôle
            iskey_down = true;
          }
          if (key_ev.type_of_event() == sdl2::event::key_up)  // Si touche relachée
            iskey_down = false;
        }
      }
      miseAJour(centrale, posteDeSecurite); // Met à jour toutes les variables de la centrale
      finDispatching = salleDeControle.majdispatching(centrale); // Met à jour le dispatching national
      nbTour += 1;  // Incrémentation du nombre de tour

      auto end = chrono::system_clock::now(); // Prend l'heure qu'il est actuellement (à la fin de la boucle)
      chrono::duration<double> secondesEcoulees = end - start;  // Différence pour avoir le temps d'exécution de la boucle while en secondes
      int tps = 1000 - floor(secondesEcoulees.count()*1000);  // Conversion du temps en millisecondes

      if (secondesEcoulees.count() < 1) // Si l'exécution de la boucle a duré moins d'une seconde
        this_thread::sleep_for(chrono::milliseconds(tps));  // Alors on attend pour qu'une itération de la boucle while dure 1 seconde
    }
    sortie[0] = 0;  // On remet la touche 'Espace' à zéro pour pouvoir rentrer dans le poste de sécurité

    // Boucle poste de securite
    while (sortie[0] == 0 && sortie[1] == 0 && not finDispatching)  // Tant qu'on arrete pas le jeu ('croix') et qu'on n'appuie pas sur 'Espace' ou non dispatching
    {
      auto start = chrono::system_clock::now(); // Prend l'heure qu'il est actuellement (au début de la boucle)

      posteDeSecurite.majAffichage(fenetre, centrale);  // Affiche la fenetre et les textes du poste de sécurité

      auto events = queue.pull_events();
      for ( const auto& e : events) // On regarde chaque évènements(touche, clic, ...)
      {
        if (e->kind_of_event() == sdl2::event::quit) // Si on clique sur la croix pour fermer la fenetre
          sortie[1] = 1;

        // Si l'évènement et de type 'clavier' et qu'il s'agit d'une touche enfoncée ou relevée
        if ((e->kind_of_event() == sdl2::event::key_down) || (e->kind_of_event() == sdl2::event::key_up))
        {
          auto& key_ev = dynamic_cast<sdl2::event_keyboard&>(*e);

          if ((e->kind_of_event() == sdl2::event::key_down) &&  (iskey_down == false))  // Si touche enfoncée et non relachée
          {
            sortie[0] = posteDeSecurite.majCommandes(fenetre, key_ev.code(), centrale);  // Actionne les fonctionnalités des touches du poste de sécurité
            iskey_down = true;
          }
          if (key_ev.type_of_event() == sdl2::event::key_up)  // Si touche relachée
            iskey_down = false;
        }
      }
      miseAJour(centrale, posteDeSecurite); // Met à jour toutes les variables de la centrale
      finDispatching = salleDeControle.majdispatching(centrale); // Met à jour le dispatching national
      nbTour += 1;  // Incrémentation du nombre de tour

      auto end = chrono::system_clock::now(); // Prend l'heure qu'il est actuellement (à la fin de la boucle)
      chrono::duration<double> secondesEcoulees = end - start;  // Différence pour avoir le temps d'exécution de la boucle while en secondes
      int tps = 1000 - floor(secondesEcoulees.count()*1000);  // Conversion du temps en millisecondes

      if (secondesEcoulees.count() < 1) // Si l'exécution de la boucle a duré moins d'une seconde
        this_thread::sleep_for(chrono::milliseconds(tps));  // Alors on attend pour qu'une itération de la boucle while dure 1 seconde
    }
    sortie[0] = 0;  // On remet la touche 'Espace' à zéro pour pouvoir rentrer dans la salle de contrôle
  }

  return nbTour;  // On renvoie le nombre de tour du jeu
}


/* Niveau 3 du jeu */
int niveau3(sdl2::window& fenetre, Centrale& centrale, SalleDeControle& salleDeControle, PosteDeSecurite& posteDeSecurite)
{
  salleDeControle.niveau(3);  // Donne le niveau de jeu à la salle de contrôle pour le dispatching

  int nbTour = 0, tourCatastrophe = 0; // Initialisation du nombre de tours du jeu et du nombre de tours des catastrophes
  bool catastrophePossible = false; // Vaut vrai si une catastrophe est possible (production >= 900)
  vector<int> sortie = {0, 0}; // Premier : changement, second : fin session
  bool finDispatching = false;  // Vaut faux si c'est la fin du dispatching (score à 0 ou production nulle), vrai sinon

  bool iskey_down = false;  // Vaut faux si la touche n'est pas enfoncée, vrai sinon
  sdl2::event_queue queue;

  while (sortie[1] == 0 && not finDispatching) // Tant qu'on ne clique pas sur la croix ou qu'on n'arrete pas le jeu (touche 'S') ou non fin dispatching
  {
    // Boucle salle de commande
    while (sortie[0] == 0 && sortie[1] == 0 && not finDispatching)  // Tant qu'on arrete pas le jeu ('croix' ou 'S') et qu'on n'appuie pas sur 'Espace' ou non dispatching
    {
      auto start = chrono::system_clock::now(); // Prend l'heure qu'il est actuellement (au début de la boucle)

      salleDeControle.majAffichage(fenetre, centrale);  // Affiche la fenetre et les textes de la salle de contrôle

      auto events = queue.pull_events();
      for ( const auto& e : events) // On regarde chaque évènements(touche, clic, ...)
      {
        if (e->kind_of_event() == sdl2::event::quit) // Si on clique sur la croix pour fermer la fenetre
          sortie[1] = true;

        // Si l'évènement et de type 'clavier' et qu'il s'agit d'une touche enfoncée ou relevée
        if ((e->kind_of_event() == sdl2::event::key_down) || (e->kind_of_event() == sdl2::event::key_up))
        {
          auto& key_ev = dynamic_cast<sdl2::event_keyboard&>(*e);

          if ((e->kind_of_event() == sdl2::event::key_down) &&  (iskey_down == false))  // Si touche enfoncée et non relachée
          {
            sortie = salleDeControle.majCommandes(fenetre, key_ev.code(), centrale);  // Actionne les fonctionnalités des touches de la salle de contrôle
            iskey_down = true;
          }
          if (key_ev.type_of_event() == sdl2::event::key_up)  // Si touche relachée
            iskey_down = false;
        }
      }
      miseAJour(centrale, posteDeSecurite); // Met à jour toutes les variables de la centrale
      finDispatching = salleDeControle.majdispatching(centrale); // Met à jour le dispatching national

      if(centrale.productionCentrale() >= 900) // Si la production de la centrale est >= à 900 → catastrophes possibles
        catastrophePossible = true;

      if(catastrophePossible == true) // Si catastrophes possibles
      {
        if(tourCatastrophe%10 == 0) // Une catastrophe peut se produire tous les 10 tours
          catastrophe(centrale);  // Appelle la fonction qui produit les catastrophes

        tourCatastrophe +=1;  // Incrémentation du nombre de tour de catastrophe
      }

      nbTour += 1;  // Incrémentation du nombre de tour

      auto end = chrono::system_clock::now(); // Prend l'heure qu'il est actuellement (à la fin de la boucle)
      chrono::duration<double> secondesEcoulees = end - start;  // Différence pour avoir le temps d'exécution de la boucle while en secondes
      int tps = 1000 - floor(secondesEcoulees.count()*1000);  // Conversion du temps en millisecondes

      if (secondesEcoulees.count() < 1) // Si l'exécution de la boucle a duré moins d'une seconde
        this_thread::sleep_for(chrono::milliseconds(tps));  // Alors on attend pour qu'une itération de la boucle while dure 1 seconde
    }
    sortie[0] = 0;  // On remet la touche 'Espace' à zéro pour pouvoir rentrer dans le poste de sécurité

    // Boucle poste de securite
    while (sortie[0] == 0 && sortie[1] == 0 && not finDispatching)  // Tant qu'on arrete pas le jeu ('croix') et qu'on n'appuie pas sur 'Espace' ou non dispatching
    {
      auto start = chrono::system_clock::now(); // Prend l'heure qu'il est actuellement (au début de la boucle)

      posteDeSecurite.majAffichage(fenetre, centrale);  // Affiche la fenetre et les textes du poste de sécurité

      auto events = queue.pull_events();
      for ( const auto& e : events) // On regarde chaque évènements(touche, clic, ...)
      {
        if (e->kind_of_event() == sdl2::event::quit) // Si on clique sur la croix pour fermer la fenetre
          sortie[1] = 1;

        // Si l'évènement et de type 'clavier' et qu'il s'agit d'une touche enfoncée ou relevée
        if ((e->kind_of_event() == sdl2::event::key_down) || (e->kind_of_event() == sdl2::event::key_up))
        {
          auto& key_ev = dynamic_cast<sdl2::event_keyboard&>(*e);

          if ((e->kind_of_event() == sdl2::event::key_down) &&  (iskey_down == false))  // Si touche enfoncée et non relachée
          {
            sortie[0] = posteDeSecurite.majCommandes(fenetre, key_ev.code(), centrale);  // Actionne les fonctionnalités des touches du poste de sécurité
            iskey_down = true;
          }
          if (key_ev.type_of_event() == sdl2::event::key_up)  // Si touche relachée
            iskey_down = false;
        }
      }
      miseAJour(centrale, posteDeSecurite); // Met à jour toutes les variables de la centrale
      finDispatching = salleDeControle.majdispatching(centrale); // Met à jour le dispatching national

      if(centrale.productionCentrale() >= 900) // Si la production de la centrale est >= à 900 → catastrophes possibles
        catastrophePossible = true;

      if(catastrophePossible == true) // Si catastrophes possibles
      {
        if(tourCatastrophe%10 == 0) // Une catastrophe peut se produire tous les 10 tours
          catastrophe(centrale);  // Appelle la fonction qui produit les catastrophes

        tourCatastrophe +=1;  // Incrémentation du nombre de tour de catastrophe
      }

      nbTour += 1;  // Incrémentation du nombre de tour

      auto end = chrono::system_clock::now(); // Prend l'heure qu'il est actuellement (à la fin de la boucle)
      chrono::duration<double> secondesEcoulees = end - start;  // Différence pour avoir le temps d'exécution de la boucle while en secondes
      int tps = 1000 - floor(secondesEcoulees.count()*1000);  // Conversion du temps en millisecondes

      if (secondesEcoulees.count() < 1) // Si l'exécution de la boucle a duré moins d'une seconde
        this_thread::sleep_for(chrono::milliseconds(tps));  // Alors on attend pour qu'une itération de la boucle while dure 1 seconde
    }
    sortie[0] = 0;  // On remet la touche 'Espace' à zéro pour pouvoir rentrer dans la salle de contrôle
  }

  return nbTour;  // On renvoie le nombre de tour du jeu
}


/* Menu du jeu : choix niveau */
int menu(sdl2::window& fenetre)
{
  int position = 0; // Initialisation de la position de la flèche (1ère position devant niveau 1)

  auto [wph, hph] = fenetre.dimensions(); // Donne les dimensions de la fentere graphique
  double coordx = 0.65*wph; // Coordonnée des abscisses de la flèche
  vector<double> coordy = {0.36*hph, 0.46*hph, 0.56*hph, 0.66*hph}; // Coordonnées des ordonnées de la flèche {niveau1, niveau2, niveau3, quitter}

  sdl2::image image("image/Menu.jpg", fenetre); // Initialisation de l'image de font du menu
  sdl2::image fleche("image/Fleche.jpg", fenetre);  // Initialisation de la flèche qui se déplace
  image.stretch({wph,hph}); // Taille de l'image de font du menu
  fleche.stretch({30,40});  // Taille de la flèche

  bool quitter = false;  // Vaut vrai si la touche entrée a été pressée ou que la croix a été cliqué, faux sinon
  bool iskey_down = false;  // Vaut faux si la touche n'est pas enfoncée, vrai sinon
  sdl2::event_queue queue;

  while(not quitter)  // Tant qu'on ne clique pa sur la croix ou qu'on n'appuie pas sur 'Entrée'
  {
    fleche.at(coordx, coordy[position]);  // Emplacement de la flèche sur l'image de font
    fenetre << image << fleche << sdl2::flush;  // Affiche l'image de font et la flèche

    auto events = queue.pull_events();
    for ( const auto& e : events) // On regarde chaque évènements(touche, clic, ...)
    {
      if (e->kind_of_event() == sdl2::event::quit) // Si on clique sur la croix pour fermer la fenetre
      {
        quitter = true;
        position = -1;  // Position vaut -1 pour ne pas correspondre à un niveau dans la fonction principale et donc ferner le jeu
      }

      // Si l'évènement et de type 'clavier' et qu'il s'agit d'une touche enfoncée ou relevée
      if ((e->kind_of_event() == sdl2::event::key_down) || (e->kind_of_event() == sdl2::event::key_up))
      {
        auto& key_ev = dynamic_cast<sdl2::event_keyboard&>(*e);

        if ((e->kind_of_event() == sdl2::event::key_down) &&  (iskey_down == false))  // Si touche enfoncée et non relachée
        {
          if(key_ev.code() == sdl2::event_keyboard::up)  // Si la touche enfoncée est la flèche du haut
          {
            if(position > 0)  // Si la flèche n'est pas tout en haut (devant niveau 1)
              position -= 1;
          }

          if(key_ev.code() == sdl2::event_keyboard::down)  // Si la touche enfoncée est la flèche du haut
          {
            if(position < 3)  // Si la flèche n'est pas tout en bas (devant quitter)
              position += 1;
          }

          if(key_ev.code() == 13)  // Si la touche enfoncée est 'Entrée'
            quitter = true;

          iskey_down = true;
        }
        if (key_ev.type_of_event() == sdl2::event::key_up)  // Si touche relachée
          iskey_down = false;
      }
    }
  }

  return position + 1;  // Renvoie la position +1 car on a commencé à 0 (pour correspondre aux case du tableau coordy)
}


/* Affiche les états des différents organes de la centrales lors du bilan */
void affichageEtats(sdl2::window& fenetre, Centrale& centrale)
{
  auto [wph, hph] = fenetre.dimensions(); // Donne les dimensions de la fenetre
  sdl2::font fonte_texte("./data/Simpson.ttf",27);  // Initialisation de la fonte des textes

  // Récuperation des valeurs des états des différents organes
  double etatCentrale = centrale.etatCentrale();
  double etatReacteur = (centrale.etatCuve() + centrale.etatPiscine()  + centrale.etatBarresGr() + centrale.etatCanaux() + centrale.etatInjBore())/5;
  double etatCircuitPrim = (centrale.etatCircuitPrim() + centrale.etatPompePrim() + centrale.etatPressuriseur() + centrale.etatResistancePressuriseur() + centrale.etatEchangeurChaleur())/5;
  double etatCircuitSec = (centrale.etatCircuitSec() + centrale.etatPompeSec() + centrale.etatGenerateurVapeur() + centrale.etatCondenseur())/4;

  // Conversion des états de type double en string pour pouvoir les afficher
  string sEtatCentrale (to_string(etatCentrale));
  string sEtatReacteur (to_string(etatReacteur));
  string sEtatCircuitPrim (to_string(etatCircuitPrim));
  string sEtatCircuitSec (to_string(etatCircuitSec));

  // Suppression des décimales des string car la conversion d'un double en string, donne un string avec 8 décimales
  sEtatCentrale.erase(4,5);
  sEtatReacteur.erase(4,5);
  sEtatCircuitPrim.erase(4,5);
  sEtatCircuitSec.erase(4,5);

  // Initialisation des différents textes
  sdl2::texte texteEtatCentrale("ETAT  DE  LA  CENTRALE  :  " + sEtatCentrale, fonte_texte, fenetre, {255,244,0,0});
  sdl2::texte texteEtatReacteur("ETAT  DU  REACTEUR  :  " + sEtatReacteur, fonte_texte, fenetre, {255,244,0,0});
  sdl2::texte texteEtatCircuitPrim("ETAT  DU  CIRCUIT  PRIMAIRE  :  " + sEtatCircuitPrim, fonte_texte, fenetre, {255,244,0,0});
  sdl2::texte texteEtatCircuitSec("ETAT  DU  CIRCUIT  SECONDAIRE  :  " + sEtatCircuitSec, fonte_texte, fenetre, {255,244,0,0});

  // Emplacement des différents textes
  texteEtatCentrale.at(0.28*wph,0.36*hph);
  texteEtatReacteur.at(0.28*wph,0.44*hph);
  texteEtatCircuitPrim.at(0.28*wph,0.52*hph);
  texteEtatCircuitSec.at(0.28*wph,0.6*hph);

  // Affiche les textes sur la fenetre
  fenetre << texteEtatCentrale << texteEtatReacteur << texteEtatCircuitPrim << texteEtatCircuitSec;

  // Affiche un message en fonction de l'état de la centrale
  if(etatCentrale > 0.8)
  {
    sdl2::texte texteEtat("LA  CENTRALE  EST  EN  BON  ETAT  !", fonte_texte, fenetre, {210,200,0,0});
    texteEtat.at(0.3*wph, 0.68*hph);
    fenetre << texteEtat;
  }

  if(etatCentrale<=0.8 && etatCentrale>0.5)
  {
    sdl2::texte texteEtat("LA CENTRALE EST ASSEZ ENDOMMAGEE !", fonte_texte, fenetre, {210,200,0,0});
    texteEtat.at(0.3*wph, 0.68*hph);
    fenetre << texteEtat;
  }

  if(etatCentrale<=0.5 && etatCentrale>0.2)
  {
    sdl2::texte texteEtat("LA  CENTRALE  EST  PRESQUE  DETRUITE  !", fonte_texte, fenetre, {210,200,0,0});
    texteEtat.at(0.3*wph, 0.68*hph);
    fenetre << texteEtat;
  }

  if(etatCentrale <= 0.2)
  {
    sdl2::texte texteEtat("LA  CENTRALE  EST  DETRUITE  !", fonte_texte, fenetre, {210,200,0,0});
    texteEtat.at(0.3*wph, 0.68*hph);
    fenetre << texteEtat;
  }
}


/* Affiche la production totale et moyenne de la centrales lors du bilan */
void affichageProduction(sdl2::window& fenetre, Centrale& centrale, int nbTour)
{
  auto [wph, hph] = fenetre.dimensions(); // Donne les dimensions de la fenetre
  sdl2::font fonte_texte("./data/Simpson.ttf",26);  // Initialisation de la fonte des textes

  // Récuperation des valeurs des production
  int productionTot = centrale.productionTotale();
  int productionMoy = productionTot/nbTour;

  // Conversion des états de type int en string pour pouvoir les afficher
  string sProductionTot (to_string(productionTot));
  string sProductionMoy (to_string(productionMoy));

  // Initialisation des différents textes
  sdl2::texte texteProductionTot("PRODUCTION  TOTALE  ELECTRICITE  :  " + sProductionTot + "  MW", fonte_texte, fenetre, {255,244,0,0});
  sdl2::texte texteProductionMoy("PRODUCTION  MOYENNE  ELECTRICITE  :  " + sProductionMoy + "  MW", fonte_texte, fenetre, {255,244,0,0});

  // Emplacement des différents textes
  texteProductionTot.at(0.25*wph,0.44*hph);
  texteProductionMoy.at(0.25*wph,0.52*hph);

  fenetre << texteProductionTot << texteProductionMoy;  // Affiche les textes sur la fenetre

  // Affiche un message en fonction de la production de la centrale
  if(productionMoy < 300)
  {
    sdl2::texte texteProduction("PRODUCTION  FAIBLE !", fonte_texte, fenetre, {210,200,0,0});
    texteProduction.at(0.3*wph,0.6*hph);
    fenetre << texteProduction;
  }

  if(productionMoy>=300  && productionMoy<900)
  {
    sdl2::texte texteProduction("PrRODUCTION  PEU  RENTABLE !", fonte_texte, fenetre, {210,200,0,0});
    texteProduction.at(0.3*wph,0.6*hph);
    fenetre << texteProduction;
  }

  if(productionMoy>=900  && productionMoy<1200)
  {
    sdl2::texte texteProduction("PRODUCTION  CORRECTE !", fonte_texte, fenetre, {210,200,0,0});
    texteProduction.at(0.3*wph,0.6*hph);
    fenetre << texteProduction;
  }

  if(productionMoy>=1200  && productionMoy<1400)
  {
    sdl2::texte texteProduction("PRODUCTION  EXCELLENTE !", fonte_texte, fenetre, {210,200,0,0});
    texteProduction.at(0.3*wph,0.6*hph);
    fenetre << texteProduction;
  }

  if(productionMoy >= 1400)
  {
    sdl2::texte texteProduction("PRODUCTION HORS NORME !", fonte_texte, fenetre, {210,200,0,0});
    texteProduction.at(0.3*wph,0.6*hph);
    fenetre << texteProduction;
  }
}


/* Affiche la radioactivite de la centrales et de ces alentours lors du bilan */
void affichageRadioactivite(sdl2::window& fenetre, Centrale& centrale)
{
  auto [wph, hph] = fenetre.dimensions(); // Donne les dimensions de la fenetre
  sdl2::font fonte_texte("./data/Simpson.ttf",23);  // Initialisation de la fonte des textes

  // Récuperation des valeurs des radiations de la centrale et de ces alentours
  int radioactiviteEnceinte = centrale.radioactiviteEnceinte();
  int radioactivitePrim = centrale.radioactivitePrim();
  int radioactiviteSec = centrale.radioactiviteSec();
  int radioactiviteEau = centrale.radioactiviteEau();
  int contamination = centrale.contamination();
  int radioactiviteAir = centrale.radioactiviteAir();

  // Conversion des états de type int en string pour pouvoir les afficher
  string sRadioactiviteEnceinte (to_string(radioactiviteEnceinte));
  string sRadioactivitePrim (to_string(radioactivitePrim));
  string sRadioactiviteSec (to_string(radioactiviteSec));
  string sRadioactiviteEau (to_string(radioactiviteEau));
  string sRadioactiviteAir (to_string(radioactiviteAir));
  string sContamination (to_string(contamination));

  // Initialisation des différents textes
  sdl2::texte texteRadioactiviteEnceinte("RADIOACTIVITE  ENCEINTE  :  " + sRadioactiviteEnceinte + "  rem/h", fonte_texte, fenetre, {255,244,0,0});
  sdl2::texte texteRadioactivitePrim("RADIOACTIVITE  CIRCUIT  PRIMAIRE  :  " + sRadioactivitePrim + "  becquerel", fonte_texte, fenetre, {255,244,0,0});
  sdl2::texte texteRadioactiviteSec("RADIOACTIVITE  CIRCUIT  SECONDAIRE  :  " + sRadioactiviteSec + "  becquerel", fonte_texte, fenetre, {255,244,0,0});

  sdl2::texte texteRadioactiviteEau("RADIOACTIVITE  EAU  AUTOUR  CENTRALE  :  " + sRadioactiviteEau + "  rem/h", fonte_texte, fenetre, {255,244,0,0});
  sdl2::texte texteRadioactiviteAir("RADIOACTIVITE  AIR  AUTOUR  CENTRALE  :  " + sRadioactiviteAir + "  rem/h", fonte_texte, fenetre, {255,244,0,0});
  sdl2::texte texteContamination("CONTAMINATION  POPULATION  :  " + sContamination, fonte_texte, fenetre, {255,244,0,0});

  // Emplacement des différents textes
  texteRadioactiviteEnceinte.at(0.25*wph,0.34*hph);
  texteRadioactivitePrim.at(0.25*wph,0.41*hph);
  texteRadioactiviteSec.at(0.25*wph,0.48*hph);
  texteRadioactiviteEau.at(0.25*wph,0.55*hph);
  texteRadioactiviteAir.at(0.25*wph,0.62*hph);
  texteContamination.at(0.25*wph,0.69*hph);

  // Affiche les textes sur la fenetre
  fenetre << texteRadioactiviteEnceinte << texteRadioactivitePrim << texteRadioactiviteSec << texteRadioactiviteEau << texteRadioactiviteAir << texteContamination;
}


/* Affiche le score du dispatching national lors du bilan */
void affichageScore(sdl2::window& fenetre, SalleDeControle& salleDeControle)
{
  auto [wph, hph] = fenetre.dimensions(); // Donne les dimensions de la fenetre
  sdl2::font fonte_texte("./data/Simpson.ttf",27);  // Initialisation de la fonte des textes

  // Récuperation des valeurs du score du dispatching
  int score = salleDeControle.scoreDispatching();

  // Conversion des états de type int en string pour pouvoir les afficher
  string sScore (to_string(score));

  // Initialisation, emplacement et affiche du texte sur la fenetre
  sdl2::texte texteScoreDispatching("SCORE  DU  DISPATCHING  NATIONAL  :  " + sScore, fonte_texte, fenetre, {255,244,0,0});
  texteScoreDispatching.at(0.25*wph,0.47*hph);
  fenetre << texteScoreDispatching;

  // Affiche un message en fonction du score du dispatching
  if(score > 8)
  {
    sdl2::texte texteScore("PERFORMANCES  CORRECTES !", fonte_texte, fenetre, {210,200,0,0});
    texteScore.at(0.27*wph,0.55*hph);
    fenetre << texteScore;
  }

  if(score<=8 && score>5)
  {
    sdl2::texte texteScore("PERFORMANCES  MOYENNES !", fonte_texte, fenetre, {210,200,0,0});
    texteScore.at(0.27*wph,0.55*hph);
    fenetre << texteScore;
  }

  if(score <= 5)
  {
    sdl2::texte texteScore("PERFORMANCES  DECEVANTE !", fonte_texte, fenetre, {210,200,0,0});
    texteScore.at(0.27*wph,0.55*hph);
    fenetre << texteScore;
  }
}

/* Bilan du jeu */
void bilan(sdl2::window& fenetre, Centrale& centrale, SalleDeControle& salleDeControle, int niveau, int nbTour)
{
  auto [wph, hph] = fenetre.dimensions(); // Donne les dimensions de la fenetre
  sdl2::image image("image/Bilan.jpg", fenetre); // Initialisation de l'image de font du bilan
  image.stretch({wph,hph}); // Taille de l'image de font du bilan

  sdl2::image poster("image/poster.jpg", fenetre); // Initialisation du poster 'Nuclear Power'
  poster.stretch({3*wph/20,3*hph/20}); // Taille de l'image de font du bilan
  poster.at(0.02*wph,0.15*hph); // Emplacement de l'image

  sdl2::image telecommandeHaut("image/telecommande_haut.jpg", fenetre); // Initialisation de l'image de la télécommande avec flèche du haut
  telecommandeHaut.stretch({3*wph/20,3*hph/20}); // Taille de l'image de la télécommande avec flèche du haut
  telecommandeHaut.at(0.85*wph,0.6*hph); // Emplacement de l'image

  sdl2::image telecommandeBas("image/telecommande_bas.jpg", fenetre); // Initialisation de l'image de la télécommande avec flèche du bas
  telecommandeBas.stretch({3*wph/20,3*hph/20}); // Taille de l'image de font de la télécommande avec flèche du bas
  telecommandeBas.at(0.85*wph,0.6*hph); // Emplacement de l'image

  sdl2::image telecommande("image/telecommande.jpg", fenetre); // Initialisation de l'image de la télécommande avec flèche du haut/bas
  telecommande.stretch({3*wph/20,3*hph/20}); // Taille de l'image de font de la télécommande avec flèche du haut/bas
  telecommande.at(0.85*wph,0.6*hph); // Emplacement de l'image

  int fenetreActuelle = 1;  //Initialisation de la fenetre actuelle sur la première position (affichage des états)

  bool quitter = false;  // Vaut vrai si la touche entrée a été pressée ou que la croix a été cliqué, faux sinon
  bool iskey_down = false;  // Vaut faux si la touche n'est pas enfoncée, vrai sinon
  sdl2::event_queue queue;

  while (not quitter)  // Tant qu'on ne clique pa sur la croix ou qu'on n'appuie pas sur 'Entrée'
  {
  fenetre << image << poster; // Affichage de l'image de font et du poster

    switch(fenetreActuelle) // Fenetre sur laquelle on se situe (en focntion des touches flèche haut/bas)
    {
      case 1 :  // 1ère fenetre
        affichageEtats(fenetre, centrale);  // Affichage des états de la centrale
        fenetre << telecommandeBas; // Affichage de la télécommande avec flèche du bas
        break;  // Sors de la boucle 'switch'

      case 2 :  // 2ème fenetre
        affichageProduction(fenetre,centrale, nbTour);  // Affichage de la production
        fenetre << telecommande;  // Affichage de la télécomande avec flèche du haut/bas
        break;  // Sors de la boucle

      case 3 :  // 3ème fenetre
        affichageRadioactivite(fenetre, centrale);  //Affichage de la radioactivite
        if(niveau == 1)
          fenetre << telecommandeHaut;  // Affichage de la télécomande avec flèche du haut
        else
          fenetre << telecommande;   // Affichage de la télécomande avec flèche du haut/bas
        break;

      case 4 :  // 4ème fenetre
        affichageScore(fenetre, salleDeControle); // Affichage du score du dispatching
        fenetre << telecommandeHaut;  // Affichage de la télécomande avec flèche du haut
        break;  // Sors de la boucle
    }

    fenetre << sdl2::flush; // Met à jour la fenetre graphique

    auto events = queue.pull_events();
    for ( const auto& e : events) // On regarde chaque évènements(touche, clic, ...)
    {
      if (e->kind_of_event() == sdl2::event::quit) // Si on clique sur la croix pour fermer la fenetre
        quitter = true;

      // Si l'évènement et de type 'clavier' et qu'il s'agit d'une touche enfoncée ou relevée
      if ((e->kind_of_event() == sdl2::event::key_down) || (e->kind_of_event() == sdl2::event::key_up))
      {
        auto& key_ev = dynamic_cast<sdl2::event_keyboard&>(*e);

        if ((e->kind_of_event() == sdl2::event::key_down) &&  (iskey_down == false))  // Si touche enfoncée et non relachée
        {
          if(key_ev.code() == 13)  // Si la touche enfoncée est 'Entrée'
            quitter = true;

          if(key_ev.code() == sdl2::event_keyboard::up)  // Si la touche enfoncée est la flèche du haut
          {
            if(fenetreActuelle > 1) // Si on ne se trouve pas sur la première fenetre (etats de la centrale)
              fenetreActuelle -= 1;
          }

          if(key_ev.code() == sdl2::event_keyboard::down)  // Si la touche enfoncée est la flèche du bas
          {
            if(niveau == 1)
            {
              if(fenetreActuelle < 3) // Si on ne se trouve pas sur la troisieme fenetre (radioactivite de la centrale)
                fenetreActuelle += 1;
            }
            else
            {
              if(fenetreActuelle < 4) // Si on ne se trouve pas sur la quatrieme fenetre (score du dispatching)
                fenetreActuelle += 1;
            }
          }

          iskey_down = true;
        }
        if (key_ev.type_of_event() == sdl2::event::key_up)  // Si touche relachée
          iskey_down = false;
      }
    }
  }
}

/* Fonction principale du jeu entier */
void jeu()
{
  // Taille de la fenetre graphique
  int x = 1400;
  int y = 750;

  sdl2::window fenetre("Nuclear Alert", {x,y}); // Initialisation de la fenetre graphique

  // Initialisation des différents organes de la centrale
  Centrale centrale;
  SalleDeControle salleDeControle;
  PosteDeSecurite posteDeSecurite;

  int niveau = menu(fenetre); // Choix du niveau de jeu (1,2,3 et 0:quitter)
  int nbTour = 1; // Initialisation du nombre de tour du jeu

  if(niveau == 1)
  {
    nbTour = niveau1(fenetre,centrale,salleDeControle,posteDeSecurite); // Niveau 1
    bilan(fenetre,centrale,salleDeControle,niveau,nbTour);  // Bilan du jeu
  }

  if(niveau == 2)
  {
    nbTour = niveau2(fenetre,centrale,salleDeControle,posteDeSecurite);// Niveau 2
    bilan(fenetre,centrale,salleDeControle,niveau,nbTour);  // Bilan du jeu
  }

  if(niveau == 3)
  {
    nbTour = niveau3(fenetre,centrale,salleDeControle,posteDeSecurite);// Niveau 3
    bilan(fenetre,centrale,salleDeControle,niveau,nbTour);  // Bilan du jeu
  }
}
