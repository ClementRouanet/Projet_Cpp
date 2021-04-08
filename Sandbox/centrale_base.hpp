#ifndef _NUCLEARALERT_CENTRALE_BASE_HPP_
#define _NUCLEARALERT_CENTRALE_BASE_HPP_

class centrale_base
{
public:
  /**
  * @brief      Production en MW actuelle de la centrale
  *
  * virtual dans ce cadre sert surtout à définir une interface
  * (c'est à dire ce qu'on peut faire avec un objet de type centrale
  * sans pour autant dire comment on le fait...)
  *
  * @return     { description_of_the_return_value }
  */
  virtual double lire_production() const = 0;

};

#endif
