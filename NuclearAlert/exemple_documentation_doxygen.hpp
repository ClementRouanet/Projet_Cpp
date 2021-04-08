#ifndef _PROJET_POMPE_HPP_
#define _PROJET_POMPE_HPP_
// Initialiser la documentation doxygen : 
// 
// doxygen -g
// 
// Puis éditer le Doxyfile pour modifier ce que on a envie de modifier (très bien documenté)
// 
// Ensuite taper simplement :
// 
// doxygen
// 
// pour créer la documentation. Un répertoire html et latex doivent être créés.
// Pour le latex, il y a un Makefile qui permet de générer le pdf.
// Pour le html, on peut le lire simplement avec un navigateur web.


/**
 * @brief      Cette classe décrit une pompe du circuit primaire ou secondaire.
 *
 * La pompe est caractérisée par son rendement et son état. Le rendement peut être
 * limité par l'état de la pompe. 
 */
class pompe
{
  public:
    /**
     * @brief      Constructeur par défaut
     *
     * L'état initial de la pompe vaut 1. et son rendement est à zéro.
     */
    pompe();

    /**
     * @brief      Permet d'ajuster le rendement de la pompe
     *
     *  Ma formule mathématique : \f$x_{i} = \frac{i+1}{2}\f$
     *
     *  Et voici un lien sur un attribut :
     *
     *  voir #rendement
     *
     * @param[in]  valeur_demandee  La valeur demandée
     *
     * @return     La valeur effective obtenue (qui dépend de l'état de la pompe)
     */
    double ajuster_rendement(double valeur_demandee);

    /**
     * @brief      Gets the state.
     *
     * @return     The state.
     */
    double get_state() const;

  protected:
    /** Rendement de la pompe */
    double rendement;

    /** Etat de la pompe */
    double etat;
};

#endif