#ifndef CATASTROPHE_HPP_
#define CATASTROPHE_HPP_

#include "centrale.hpp"

void catastrophe1(Centrale& centrale); // Pour une raison inexplicable, le circuit primaire vient d'être très gravement endommagé. Les dégâts s'étendent jusqu'au pressuriseur. L'échangeur est légèrement touché. La piscine est fissurée. État d'alerte maximal.

void catastrophe2(Centrale& centrale); // La cuve et la piscine viennent de se dégrader subitement. Les barres, les canaux et le circuit primaire sont également touchés. Le générateur est fissuré mais l'échangeur est intact. La situation est très alarmante.

void catastrophe3(Centrale& centrale); // Une fuite vient d'endommager gravement le système producteur de vapeur. L'ensemble primaire est peu touché mais le secondaire et l'enceinte ont été dégradés. Situation dangereuse, contamination possible.

void catastrophe4(Centrale& centrale); // Un avion vient de percuter l'enceinte de confinement. Elle est partiellement détruite. L'ensemble primaire est gravement touché. Des projections ont endommagé le circuit secondaire et surtout le condenseur.

void catastrophe5(Centrale& centrale); // Un tremblement de terre d'une violence exceptionnelle a frappé la région. La centrale est touchée. Les dégâts sont multiples et impossibles à localiser. La situation est catastrophique.

void catastrophe(Centrale& centrale); // Simule une catastrophe aléatoirement entre les 5 catastrophes précédentes


#endif
