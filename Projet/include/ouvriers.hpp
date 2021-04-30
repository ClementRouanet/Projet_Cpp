#ifndef OUVRIERS_HPP_
#define OUVRIERS_HPP_


class Ouvriers
{
public:
  Ouvriers(); // Constructeur

  void guerison();  // 40% de chance que l'ouvrier guérisse
  void blessure();  // Simule la blessure d'un ouvrier

  ~Ouvriers();  // Destructeur

private:
  int m_nbOuvriers;
  std::vector<bool,m_nbOuvriers> m_malade;
  std::vector<bool,m_nbOuvriers> m_chantier;
};

#endif
