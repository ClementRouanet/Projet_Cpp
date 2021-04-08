# Nuclear Alert

## Introduction

Le but de ce projet est de simuler de manière assez fidèle le fonctionnement d'un centre de
production nucléaire (malgrés quelques entorses avec la réalité).

Le joueur aura le choix entre trois options :

    1. Être libre de faire ce qui lui plaît dans la salle de contrôle;
    2. Se Soumettre à des ordres provenent d'un centre directeur : "Le Dispatching National";
    3. Être en face d'un accident (cinq types dont un aléatoire) et arriver à empêcher l'accident nucléaire.

Dans tous les cas, le joueur aura à sa disposition :

    - Une console qui regroupe toutes les commandes de la salle de contrôle;
    - Un poste sécurité radioprotection permettant de vérifier par le détail l'état de la centrale (et
        éventuellement intervenir)
    - un schéma de la centrale où clignotent les organes les plus touchés

Des systèmes de sécurité renseigneront l'utilisateur sur les risques et dégâts potentiels résultant de
certaines manoeuvres. Celui-ci restera malgrè tout responsable des décisions à prendre. Une session se
terminera toujours par un bilan destiné à évaluer l'ampleur des dégats (matériels et humains) et noter
le joueur en conséquence.

## Fonctionnement d'une centrale nucléaire

![Schéma d'une centrale nucléaire](schéma_centrale.png)

Une tranche de centrale nucléaire se compose d'une enceinte de confinement (Bâtiment réacteur sur le schéma)
abritant l'ensemble du circuit primaire et protégeant l'extérieur (à la façon d'une cocotte-minute
en cas de surpression). La cuve du réacteur, abritée dans une piscine contient l'uranium (le combustible).
Une réaction nucléaire s'y produit, contrôlée par deux paramètres :

    - les barres de contrôle, glissant dans des canaux, la freinent lorsqu'elles sont abaissées dans 
      le réacteur;
    - Le taux d'acide borique qui la freine lorsqu'il est élevé.

Ladite réaction nucléaire produit de l'énergie calorifique servant à chauffer l'eau sous pression du
circuit primaire. Ce circuit est mis sous pression grâce au pressuriseur afin d'éviter que l'eau ne
se transforme en vapeur, même à 300° celcius. La circulation est assurée par une pompe.

L'eau chaude du circuit primaire va alors passer dans l'échangeur de chaleur où elle va chauffer l'eau
d'un deuxième circuit : le circuit secondaire.

Cette eau se transforme en vapeur dans le générateur de vapeur. Cette vapeur entraîne à son tour une
turbine, puis un alternateur produit l'énergie électrique; c'est la production (chiffrée en MW, jusqu'à
1400 MW). La vapeur passe ensuite dans un condensateur où elle se condense de nouveau en eau (car refroidie par de l'eau provenant du fleuve) pour retourner au générateur et ainsi de suite (bouclage). Une pompe
sert bien entendu à la circulation de l'eau du circuit secondaire.

### La salle de contrôle

La salle de contrôle met à votre disposition toutes les commandes et les données physiques (températures, pressions, débits, radioactivités, etc.) qui vous seront utiles.

Figurent aussi les cadres réservés aux ordres du dispatching et aux avertissements--sécurité qui se compose d'un message donnant l'état d'une partie de la centrale :

    - Dégradation possible
    - Risque important de dégradation
    - Dégradation très importante

l'organe concerné :

    - Circuit primaire
    - Circuit secondaire
    - Pompe du circuit primaire
    - (à continuer)

et la cause de cette dégradation.

Par exemple, vous pouvez avoir comme message :

    Risque important de dégradation du circuit primaire dû à la formation de vapeur (N.B : pression trop faible... )

Les commandes disponibles sont actionnées par des touches précises. Le réglage d'un paramètre s'effectue par les touches fléchées haut et bas (montée, descente). Tous ces
ordres sont soumis évidemment aux états des organes qu'ils concernent :

    - 1 : Fonctionnement de la pompe du circuit primaire
    - 2 : Fonctionnement de la pompe du circuit secondaire
    - B : Action sur les barres de contrôle
    - T : Action sur le taux d'acide borique
    - P : Fonctionnement pressuriseur
    - R : Fonctionnement pompe condenseur
    - U : Autorise en cas d'urgence l'enfoncement rapide des barres dans le réacteur. Cette procédure comporte des risques de dégradation.
    - S (maintenu enfoncé) : demande la fin de la session
    - Tab : Affiche le schéma de la centrale
    - Espace : Passage en poste sécurité radioprotection

**Nota** : *Différence entrée-sortie* désigne la différence de température entre l'entrée et la sortie du condensateur. Ceci permet d'évaleur sont efficacité.

### Le poste sécurité radioprotection

Donne les états de tous les organes de la tranche. La valeur cent correspond à un état intact, zéro à une destruction complète ou à un état entravant gravement le fonctionnement.

Le cadre "Activité" signale entre autres divers niveaux de contamination (piscine, air à l'intérieur de l'enceinte, rejets atmosphériques et aqueux) en becquerels (activité réelle), en rems ou milirems par heure (correspondant à l'influence exercée en une heure sur un être humain).

Le cadre "Ordinateur" donne l'état courant de la centrale et des alentours : E.G.C (Etat général centrale), niveau d'alerte, ouvriers actifs ou non (max. sept), population évacuée/contaminée, etc.

Là encore quelques commandes sont disponibles :

    - Tab : Affiche le schéma de la centrale
    - Espace : Retour à la salle de contrôle
    - P : Demande l'évacuation de la population (celle-ci n'est effective que quelques temps plus tard)
    - B : Bilan de l'activié ouvrière. Cette commande affiche les différents organes où sont potentiellements réalisables des interventions humaines. Pour chacun d'eux peut être affiché :
        o Si l'intervention est possible ou impossible
        o Le nombre possible d'ouvriers pouvant intervenir
        o Le nombre d'ouvriers en train d'intervenir en cours
    Le bilan reste affiché tant que la touche B est enfoncée.
    - O : Intervention ouvriers. Sélectionnez l'organe concerné en appuyant sur la lettre correspondante. Si l'intervention est déjà en cours, vous aurez la possibilité de l'annuler (et de récupérer l'effectif).
    Une intervention d'ouvrier permet de remettre en état un organe défectueux. Elle n'est bien sûr possible que si les conditions (pression, radioactivité, température) le permettent. Si celles-ci deviennent défavorables en cours d'intervention, les ouvriers affectés à la tâche seront signalés blessés et ne pourront rejoindre que petit à petit les effectifs disponibles.

### Quelques remarques

La température du circuit primaire (donc en bout de chaîne, la production électrique) est dans une certaine mesure liée au débit de ce même circuit. En effet, plus l'eau stagne, plus sa température s'élève au contact de l'uranium en fission. Le réglage de la pompe du circuit primaire et de a pression détermine avec précision la production. En fait, le dispatching admet une marge de plus ou moins 10MW (à maintenir pendant que dure le bip-bip). 

Mise en divergence signifie faire démarrer la réaction en chaîne (lever des barres, baisse du taux d'acide borique, fonctionnement des pompes, pressurisation, etc.)
et let production de vapeur dans le générateur. Toute action sur un organe principal du circuit primaire (pressuriseur, barres, bore ) n'entraîne pas, on s'en doute une modification brutale des paramètres. Une certaine inertie (montées ou descentes progressives) rend la simulation réaliste... et le jeu plus ardu.
Donc procédez avec méthode et sans précipitation.

## Le Dispatching

Uniquement disponible au niveau deux du jeu (le niveau un est un mode complètement libre sans incidents extérieurs possibles)

Vous recevez des ordres de l'extérieur, à vous de les suivre les plus fidèlement possible.

Le premier ordre sera toujours la mise en divergence de la centrale (le démarrage du réacteur, etc.)
Dès que la température de la vapeur dépasse 140°C  mise en service (et donc commence à produit électricité),
on recevra des ordres. Attention, si on ne produit plus de vapeur après en avoir produit, on recevra quand même des ordres.

A chaque tour, il y aura 40% de chance qu'on vous demandera de produire pour les besoins nationaux un certain nombre de MW (entre 900 et 1400 MW). Tant que ce but n'est pas atteint, il n'y aura pas d'autre ordres.
On compte alors le nombre de tour avant que le joueur arrive à produire
le nombre de MW demandé (ave une tolérance de 10MW). Au bout de huit tours (un tour = 10 secondes ?), tant que le but n'est pas atteint, on soustrait un point du score du joueur (score = 100 en début de partie). Au bout de seize tours, si le but n'est pas atteint, on à 20% de chance de recevoir un contre ordre qui demande de produire un certain nombre de MW entre 100 et 1400MW. Au bout de cinquante tours, on vous demande d'accélérez la procédure et vous perdez six points au score. Au bout de soixante cinq tours, score diminue de trois points

Si vous atteignez le but et le maintenez pendant quinze tours, l'ordre cessera et vous gagnerez 10 points au score. 

Si la centrale ne produit plus d'électricité pendant six tours, le jeu a 50% de s'arrêter à chaque tour
et on affiche alors le bilan (voir bilan)


## Les catastrophes possibles

Les catastrophes n'interviennent que si on choisit le niveau trois du jeu.

Voici les scénarii possibles pour les catastrophes :

    1. Pour une raison inexplicable, le circuit primaire vient d'être très gravement endommagé. Les dégâts s'étendent jusqu'au préssuriseur. L'échangeur est légèrement touché. La piscine est fissurée. Etat d'alerte maximal.
    Etat circuit primaire : 30%+[0-15], préssuriseur : 65 + [0-15], Pompe circuit primaire : Etat circuit primaire + [0-3], tuyvap (?) -= (10 + [0-15]), piscine = piscine - 18, cuve -= (3+[0-10]), état bore -= (40+[0-25]), état barre d'uranium /= 1.5, resist (?) = pres

    2. La cuve et la piscine viennent de se dégrader subitement. Les barres, les canaux et le circuit primair sont également touchés. Le générateur est fissuré mais l'échangeur est intact. La situration est très alarmante.
    piscine = 50 - [0-15], cuve = 55 - [0-7], ebar -= [20+[0-2]], , état canaux /= 1.5, circuit primaire -= (10+[0-13]), pressuriseur -= 3, resist -= 4, générateur -= (3+[0-10]), état bore -= (8+[0-10])

    3. Une fuite vient d'endommager gravement le système producteur de vapeur. L'ensemble primaire est peu touché mais le secondaire et l'enceinte ont été dégradés. Situation dangereuse, contamination possible.
    gene = 40 + [0-10], tuyvap = 50 + [0-3], prot -= [0-3], cir 2 -= 25 +[0-3]%, econd -= 3, pmp2 -= 4+[0-3],
    ebore = [0-1.].ebore, ebar -= 20 + [0-10]

    4. Un avion vient de percuter l'enceinte de confinement. Elle est partiellement détruite. L'ensemble primaire est gravement touché. Des projections ont endommagé le circuit secondaire et surtout le condenseur.
    prot /= 2.5, pisc /= 1.5, cuve -= 20, gene -= 14 + [0-3], tuyvap -=3+[0-12], cir1 -= 20+[0-15],
    ebar /= 1.2, pmp1 = [0-1.]pmp1, pmp2 /= 1.3, cir2 -= 8+[0-10], econd= econd/2 - [0-14], 
    ebore = ebore/1.4 - [0-10]

    5. Un tremblement de terre d'une violence exceptionnelle a frappé la région. La centrale est touchée. Les dégâts sont multiples et impossibles à localiser. La situation est catastrophique. 
    prot /= 2.6, econde /= 2.6, pisc -= 30+[0-30], cuve = 20+[0-30], gene = 10+[0-10], pmp1/= 1.6,
    cir1 -= 20+[0-8]. Chance 50% cir2/1.4 et pmp2/2. Chance 70% cir1/1.4. Chance 40% ebore/3.2.
    Chance 30% ecan/1.5, ebar/2.4

Gestion des incidents potentiels : Tant que la production est inférieure à 900MW, pas d'incidents possibles
Sinon à chaque tour de jeu (10 secondes), il y a 20% de chance qu'une des cinq catastrophes au dessus arrive.
Quand une catastrophe arrive, 

Remarque : Si la production d'électricité dépasse 1600MW, il s'affichera un message d'alerte disant qu'on est en surproduction. Dans ce cas, le déclenchement automatique permettant de plonger les barres d'uranium dans l'acide borique aura lieu.


## Modélisation numérique

Inertie : Lorsque l'utilisateur demandera par exemple de modifier la quantité de bore, on décrémentera/incrémentera de un la quantité de bore actuelle pour atteindre au bout d'un certain nombre de pas de temps la valeur souhaitée. On fera de même avec les autres quantités.

Nom des variables dans le code basique : 

A l'initialisation :
-------------------
T1  = 25  : Température du circuit primaire (de l'eau en °C)
P1  = 1   : Pression de l'eau dans les canalisation circuit primaire (en bar)
BAR = 0   : % des barres plongés dans le circuit d'eau
TPRES = 25 : Régime en % du pressuriseur (à atteindre)
RAD1 = 200 : Radioactivité circuit primaire (en becquerel)
ZVAPRESS = -1 : Pression de la vapeur d'eau dans le circuit secondaire (en bar)
TVAP = -1 : Température de la vapeur d'eau dans le circuit secondaire 
DEB1 = 0 : Débit pompe circuit primaire
DEB2 = 0 : Débit pompe circuit secondaire
FP1  = 0 : Fonctionnement de la pompe primaire (à 0%, à 100%, etc.)
FP2  = 0 : Fonctionnement de la pompe secondaire (à 0%, à 100%, etc.)
ZENCPRES = 1 : pression subit par l'enceinte du réacteur
ZRADINT = 0.00002 : Radioactivité de l'enceinte de confinement en rem/h ou en mrem/h
RAD2 = 0 : Radioactivité circuit secondaire (en becquerel)
BORE=47 : % d'acide borique à atteindre (destiné à freiner les neutrons pour ralentir la réaction nucléaire)
DEBREF = 0 : Débit du condensateur
RADPISC = 0 : Radioactivité de la piscine (en becquerel)
ZAIRRAD = 0 : Radioactivité atmosphérique (en rem/h ou en mrem/h)
ZREFRAD = 0 : Radioactivité aquatique ( en rem/h ou en mrem/h)
MW = 0 : production électrique obtenue
DES = 0 : Différence de température entre l'entrée et la sortie du condensateur
FPR = 0 : % de fonctionnement de la pompe du condensateur
DISP = 145 : Nombre d'ouvriers disponibles
OCC = 0 : Nombre d'ouvriers actifs
BLES = 0 : Nombre d'ouvriers blessés
ZIT2 = 0
ECAN = 100 : Etat des canaux guidant les barres d'uranium
EBAR = 100 : Etat des barres d'uranium
CUVE = 100 : Etat de la cuve contenant les canaux et les barres
PISC = 100 : Etat de la piscine où sont plongés les barres
PMP1 = 100 : Etat de la pompe du circuit primaire
PMP2 = 100 : Etat de la pompe du circuit secondaire
TUYVAP = 100 : Etat de l'échangeur de chaleur
GENE = 100 : Etat du générateur de vapeur
PRES = 100 : Etat du présuriseur
RESIST = 100 : Etat de la résistance du pressuriseur
PROT = 100 : Etat de l'enceinte de confinement
CIR1 = 100 : Etat du circuit primaire
EBORE = 100 : Etat de la production d'acide borique
CIR2 = 100 : Etat du circuit secondaire
ECOND = 100 : Etat du condenseur
ZCENTRALE = 100 : Etat général de la centrale
PNT = 100 : Nombre de points gagnés (score)
ZIT1 = 0
OUV(8) : 8,"PMP1", 8,"PMP2", 20,"COND", 60,"GENE", 5,"BORE", 20,"CIR2", 10,"PRESS", 45, "CIR1" : nombre d'ouvriers par chantier (avec nom du chantier)
BAR2 = BAR   : % barre dans piscine actuel (inertie des commandes)
BORE2 = BORE : % acide borique actuel (inertie commande, on essaie d'atteindre la valeur bore)
TPRES2 = 0 : Régime actuel du présuriseur
F1 = 0 : Espèce de pas de temps glissant (module 20)
EVPOP = 0 : % de la population évacuée
CONTAM = 0 : Contamination de la population par la radioactivité
FD = 0
FD1 = 0 => FD et FD1 deux états pour gérer le dispatching
CD = -1  : COmpteur de tour depuis le dernier ordre (modifie les états pour gérer l'urgence)
BUT = -1 : En dispatching, nombre de MW voulu pour alimenter la population
MPRO = 0  : Moyenne de la production en MW de la centrale (fenetre glissante de six derniers pas de temps)

### Enceinte du réacteur

Si l'enceinte de confinement est abîmée :
Pression subit par l'enceinte  = 1 en état normal
    Si la pression de l'eau est > 8 bar, état de la cuve < 100% et état piscine < 100% 
    ou bien si état cuve < 30% et état piscine < 40% :
         pression subit = pression subit pas de temps avant + (200-cuve-pisc)/2300.
    Si état circuit 1 < 60 et pression eau > 12 bar ou si circuit 1 < 20:
         pression subit += (100-circuit1)/3000
    Si l'état du générateur de vapeur < 90 et pression vapeur d'eau dans générateur > 2:
         pression subit += (100-gene)/2000
    La pression subit ne peut pas dépasser physiquement cinq bar
    Si la pression subit est > 1 :
        Si la état protection confinement est compris entre 50 et 60 :
            pression subit -= ((100-prot)/200).(pression subit)
    Petite chance (moins de 30%) que la pression baisse de 0.13 bar mais ne peut être en dessous
    de un bar.

Inertie des barres :  x = 100 - (100-bar).ebar/100 (= bar si ebar = 100%)
                      si bar2 < x bar2 += 1
                      Si bar2 > x bar2 -= 1


### Calcul circuit primaire

Température du circuit t1= (50-bore2)/50.((bar2/100).645-(deb1/90).140+2P1)+26+zit1
Si tuyvap<50 et bore<25 et bar2<50 alors zit1 += [0:26]
Si tvap < t1 : zit1 += (tvap-t1)/3
sinon zit1 = max(zit1-[0:16],0)
Si t1 < 25 : t1 = 25 + [0:15]
Pression circuit primaire : p1 = max(((tpres2-25)/3.24 + (t1-100)/83.3).(cir1/100+0.1).(tuyvap/100+0.1),1)
Débit circuit primaire : deb1 = cir1/100.cuve/100.fp1/100.90
x = min(1400, mw)
radiation circuit primaire rad1 = 98.(deb1+1)+[0:90]+(50-bore).(x+0.1).0.0654

### Circuit secondaire

Débit = (état circuit secondaire).(état condensateur+10).(état générateur vapeur).(% fonctionnement
pompe circuit) x 0.00000085
Si le débit calculé est < 3, et si la pression de la vapeur > 3, alors :
débit = (état circuit).(état condensateur+10).(état générateur vapeur) x 0.0000013
Le débit ne peut pas dépasser 99 m^3/s

Si |zit2| < 3 alors z = 0 sinon z = zit2
Température vapeur = (état échangeur chaleur).(t1/151.)+26+z
Si (Delta temp. entrée sortie (=des))<= 11 et t1 > 190, zit2 += rnd(11-des) sinon zit2 -= [0:2]

si (fp2<55+[0:15]) et t1 > 200 alors zit2 += [0:t1/100]
sinon si zit2!=0 alors zit2 -= [0:3]. Si zit2 < 0 alors zit2 = 0

Si la température de la vapeur est inférieure à 120°C, on considère qu'il n'y a pas de vapeur

Si il y a de la vapeur, alors la pression exercée par la vapeur est (cir2+10).gene.(fp2/500000+(tvap-135)/100000)
avec une pression minimale de 1 bar et vaut au maximum 99 bar (!). 

La radioactivité dans le circuit secondaire dépend de l'état de l'échangeur de chaleur, et est calculée comme 
le max entre la radioactivité du circuit secondaire au pas de temps précédent et (100-tuyvap)/100.rad1.


### Le condensateur :

Débit condensateur = état condensateur * % fonctionnement pompe condensateur * 0.015
Si il y a création vapeur d'eau : Différence températeur entrée-sortie = débit/7.5

### Traitement production

Si pas de vapeur ou cir2 < 22, MW = 0
Si tvap < 3000 (!) alors mw = max(5.787.(tvap-120)+28.118.(zvappres-1)+P1,0) sinon mw = 30000
Si cir2 < 60 : mw = (cir2/100).mw
Si mw > 1400 et mw < 1412 => mw = 1400 ???

### Sécurité

Signale et gère d'éventuels problèmes sur la centrale (effets cumulatifs !) :

mpro = (5mpro+mw)/6

    - Sur le circuit primaire : Si t1 < 40 : pas de dégradation possible
                                Si 400 < t1 < 420 : Affichage température trop élevé circuit 1
                                Si t1 >= 420 : Affichage risque important dégradation circuit 1 à cause de la température
                                    Si les barres plongées à plus de 20% : dégradation des barres de [0-3]%
                                                                           Affichage dégradation possible des barres
                                    Dégradation circuit 1 de [0-2]%
                                    30% de chance que la pres et la resist de l'enceinte confinement dégrade de [0-2]%
                                Si t1 >= 40p1 : Afficher risque important de dégradation circuit 1/vapeur
                                                circuit1 dégradation de [0-3]%
                                                pres de l'enceinte confinement dégradation de [0-2]%
                                                30% dégradation resist enceinte confinement de [0-2]%
                                Si t1 >= 50°C:
                                    Si état circuit 1 < 50% : 40% chance dégradation échangeur chaleur tuyvap -= [0-4]%
                                                              20% chance dégradation générateur vapeur (gene)
                                    Si état circuit 1 < 58% : 50% dégradation pompe 1 de [0-3]%
                                    Si état présuriseur < 50% : 80% chance enceinte confinement résist dégradation de [0-3]%
                                    Si état circuit 1 < 60% : 40% dégradation cuve [0-2]
                                    Si état circuit 1 < 30% : 30% dégradation cuve [0-3]                
                                    Si état circuit 1 < 20% : 80% degradation piscine [0-6]%, cuve : [0-6]%
                                    Si état circuit 1 < 80% et pression > 10 : 15% dégradation circuit 1 [0-2]%
                                    Si cuve < 70% et bar2 > 22 : 40% dégradation barres [0-3]%
                                    Si cuve < 50% : 50% dégradation canaux [0-5]%
                                    Si échangeur chaleur (tuyvap) < 60% : 30% dégradation circuit 1 [0-1.5]%
                                    Si échangeur chaleur < 60% et pression > 3 : 50% dégradation gene [0-2]%
                                    Si canaux < 60% et bar2 > 40 : 30% états barres dégradation [0-2]%
                                    Si cuve < 50% et circuit 1 < <50% : état bore dégradation [0-2]%

    - Sur le circuit secondaire : Si pas de vapeur, pas de dégradations possibles
                                  Si échangeur chaleur < 70% : Affichage problème échange chaleur entre circuit 1 et 2
                                  Si échangeur chaleur < 40% : Affichage risque important dégradation échangeur/générateur
                                                               25% chance dégradation générateur vapeur [0-3]%
                                  Si température vapeur d'eau >= 310°C, Afficher risque important dégradation circuit 2 à cause de la chaleur
                                                                        25% chance dégradation circuit 2 [0-4]%
                                  Si delta temp. < 11 et temp. vap >= 130 : afficher Dégradation potentiel circuit 2 dû au refroidissement
                                  Si circuit 2 < 50 et temp. vap. > 130 : 30% dégradation circuit 2 [0-1.5]%
                                  Si circuit 2 < 60% : 30% chance dégradation pompe 2 [0-2]%
                                  Si circuit 2 < 40% : 40% chance dégradation générateur vapeur [0-2]%

    - Confinement/autre : Si delta temp.> 19 : Afficher dégradation potentiel condenseur cause delta temp.
                                               40% dégradation condenseur [0-3]%
                          Si pression subit confinement > 2 et < 3.4 alors Afficher dégradation potentiel confinement dû à pression
                                                                           Si protection > 50%, 30% protection dégrader à [0-2]%
                          Si pression subit confinement >= 3.4 et < 4.5 : Afficher Risque important dégradation confinement dû à pression
                                                                         Si protection > 25%, 60% dégradation protection à [0-6]%
                          Si protection confinement = 0 ou pression confinement >= 4.5, alors dégradation totale de l'enceinte (voir explication plus bas), affichage alertes (voir plus bas)

## Traitement de la population autour de la centrale

evpop = 10 . pourcentage population évacuée.

Si evpop = 10, tout le monde est évacué

radiation piscine = (100-cuve).rad1/100+100+[0-45]
zradint = [0-1/55]+0.00002+(100-cir1).rad1/9898+(100-pres)/10
Si pisc < 55 et radpisc > 3000 : zradint = 1.25 zradint
Si prot < 90 zradint /= 1.3
Si prot < 10 zradint /= 1.5
Si prot > 97 zairrad = 0 sinon zairrad = (100-prot)/100.zradint+(100-circ2)/10
Si econd > 90 or rad2 < 2 : zrefrad = (100-econd).rad2/10000
Si evpop!=0 et evpop !=10 : 40% chance evpop += 1
Si evpop!=10 ou zradint>=10 :
    contam = contam - 5.(zairrad>6)-5.(zrefrad>1)-8.(zrefrad>12)-10.(zairrad>12)
    Si zairrad > 12 : contam += 4 + [0-15]
    Si zrefrad > 12 : contam += 5 + [0-20]
    Si zairrad > 20 : contam += 12 + [0-20]

Si contam entre 10 et 600 : Contamination radioactive légère de la population
Si contam entre 600 et 800 : Contamination radioactive importante de la population
Si contam supérieur à 800  : Population gravement contaminée

## Autres formulations mathématiques :

Les états ne peuvent être négatifs. Resist ne peut être supérieur à pres et cuve ne peut pas être plus dégradé que piscine. 
Le régime des pompes ne peuvent être supérieurs à leur état
tpres ne peut pas être plus grand que pres + resist et tpres ne peut pas être plus petit que 25 (seul cas où il peut être plus grand)
zvappres >= 1
La contamination radioactive ne peut pas être plus grande que 30000

Enfin, l'état total de la central est égal à : ecan+2ebar+8cuve+3pisc+pmp1+pmp2+5tuyvap+4gene+press+resist+4prot+8cir1+3cir2+ebore+econd)/44

**NB :** Si l'état de la central est inférieure à 22%, la centrale sera complètement détruite.

Si l'état de la centrale est entre 50 et 60%, on entre dans l'état d'urgence n°1 (DEFCOM 1)

Si l'état de la centrale est entre 30 et 50%, on entre dans l'état d'urgence n+2 (DEFCOM 2)

Si l'état de la centrale est inférieure à 30%, sa destruction devrait être imminente.



## Dégradation total enceinte confinement

Afficher un message d'alerte disant que l'enceinte de confinement est totalement détruite

gene se dégrade de 10 + [0-10]%
Dans ce cas, si gene < 40 : Affiche D.T.I échangeur
                            tuyvap se dégrade de 10 + [0-10]%
80% dégradation circuit primaire : msg D.T.I cir1/Press + cir1 dégradation 10 + [0-10]%
                                                        + press de 10%
                                                        Si press < 90% : 80% resist dégrade [0-10]%
65% dégradation cuve et piscine : msg D.T.I cuve/piscine + piscine dégradation 6+[0-16]%
                                                         + cuve dégradation 5 +[0-10]%

## Tentative d'arrêt d'urgence

Pour éviter une catastrophe nucléaire, il est possible de tenter un arrêt d'urgence (qui consiste à
noyer les barres d'uranium dans l'acide borique afin d'absorber un max de neutron et arrêter la réaction
nucléaire). Evidemment, si certaines parties de la centrale (surtout les canaux et les barres d'uranium)
sont abîmées, la tentative peut échouer :

La probabilité de réussite est  (en %) : cuve.ecan.ebar.0.00007+15
Si la tentative est réussie, les barres commencent à descentre (on met bar à zéro et bar2 à z/2 (?))
Si la tentative échoue, on risque d'abimer une partie du circuit primaire :

    - 80% de chance d'abîmer les canaux entre 5 et 15% de dégradation
    - 30% de chance d'abîmer les barres d'uranium entre 2 et 10% de dégradation
    - 40% de chance d'abîmer la cuve entre 0 et 8%

## Travail des ouvriers

Lorsqu'on demande aux ouvriers d'aller réparer des parties de la centrale, le nombre d'ouvrier est fixé par avance. A savoir :

    - Huit ouvriers pour la pompe du circuit 1
    - Huit ouvriers pour la pompe du circuit 2
    - Vingt ouvriers pour le condenseur
    - Soixante ouvriers pour le générateur de vapeur
    - Cinq ouvriers pour l'injecteur d'acide borique
    - Ving ouvriers pour le circuit 2
    - Dix ouvriers pour le présuriseur
    - Quarante cinq ouvriers pour le circuit 1

Il y a au départ 145 ouvriers de disponibles.

Selon la qualité de l'environneent où ils travaillent, il peuvent tomber malade ou non.
Tous les huit tours de jeu, il y a 40% de chance qu'un ouvrier guérisse et devient disponible.

Si l'état du circuit 1 est < 20%, toute intervention est impossible
Tous les cinq tours, il y a 10% de (mal)chance que les ouvriers travaillant au générateur de vapeur soient blessés (si ils travaillent au générateur, bien entendu)

Si zradint > 12 ou zencpres>3 : les ouvriers travaillant sur la pompe 1, le générateur de vapeur, l'injecteur d'acide borique, le présuriseur ou le circuit 1 ne pourront pas y travailler. Si ils étaient déjà sur le chantier, ils seront tous blessés

Si tvap > 300 ou mw > 1000 : les ouvriers travaillant sur la pompe 2, le condeseur ou le circuit 2 ne pourront pas y travailler. Si ils étaient déjà sur le chantier, ils seront tous blessés.

A chaque tour, il y a 30% que leur intervention n'améliore rien.
Sinon, 

    - Pour les pompes : si état >= 97%, on arrive alors à 100%
                        sinon état += [0-3]%
    - Pour condenseur : Si état >= 98%, on arrive à 100%
                        sinon état += [0-2]%
    - Pour générateur vapeur : Si état < 89%, état += [0-5]% sinon considéré comme réparé (mais pas à 100%)
    - Pour injecteur de bore : Si état < 96%, état += [0-4]% sinon considéré comme réparé (pas forcément 100%)
    - Pour circuit n°2 : Si état < 78%, état += [0-2]% sinon considéré comme réparé
    - Pour circuit n°1 : Si état < 80%, état += [0-2]% sinon considéré comme réparé
    - Pour présuriseur : Si état < 97%, état += [0-3]%, résist = état -[0-4]% sinon tout à 100% (pres et resist)

Lorsqu'un module est considéré comme réparé, les ouvriers sont de nouveau disponibles! 
