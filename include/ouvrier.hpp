#ifndef OUVRIER_HPP_
#define OUVRIER_HPP_


class Ouvrier
{
public:
  Ouvriers(); // Constructeur

  void guerison();  // 40% de chance que l'ouvrier guérisse
  void blessure();  // Simule la blessure d'un ouvrier

  ~Ouvriers();  // Destructeur

private:
  bool m_malade;
  bool m_chantier;
};

#endif
