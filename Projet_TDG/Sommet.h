#ifndef SOMMET_H_INCLUDED
#define SOMMET_H_INCLUDED

#include <string>
#include <vector>

class Sommet_g
{
friend class Graphe_g;

public :
    std::string m_nom;

    std::vector <int> m_en_lien;

    int m_groupe;
    int m_groupe_F;
    bool m_marque_p;
    bool m_marque_m;
    bool m_marque;

public :
    Sommet_g();
    Sommet_g(std::string nom);
    ~Sommet_g();

    void Setgroupe(int val){ m_groupe = val; }
    void Setgroupe_F(int val){ m_groupe_F = val; }
    void Setmarque_p(bool val){ m_marque_p = val; }
    void Setmarque_m(bool val){ m_marque_m = val; }
    void Setmarque(bool val){ m_marque = val; }
    void Addenlien(int val){ m_en_lien.push_back(val); }

    int Getgroupe() { return m_groupe; }
    bool Getmarque_p() { return m_marque_p; }
    bool Getmarque_m() { return m_marque_m; }
    bool Getmarque() { return m_marque; }
};

#endif // SOMMET_H_INCLUDED
