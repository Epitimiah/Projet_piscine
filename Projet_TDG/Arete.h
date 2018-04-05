#ifndef ARETE_H_INCLUDED
#define ARETE_H_INCLUDED

#include "Sommet.h"

class Arete
{
    friend class Graphe;
private :
    Sommet m_sommet_d;
    Sommet m_sommet_a;
    int m_poids;
public :
    Arete();
    Arete(Sommet depart, Sommet arrive, int poids);
    ~Arete();

    Sommet Getsommet_d() { return m_sommet_d; }
    void Setsommet_d(Sommet val) { m_sommet_d = val; }
    Sommet Getsommet_a() { return m_sommet_a; }
    void Setsommet_a(Sommet val) { m_sommet_a = val; }
};


#endif // ARETE_H_INCLUDED
