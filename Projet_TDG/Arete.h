#ifndef ARETE_H_INCLUDED
#define ARETE_H_INCLUDED

#include "Sommet.h"

class Arete
{
    friend class Graphe;
private :
    int m_sommet_d;
    int m_sommet_a;
    int m_poids;
public :
    Arete();
    Arete(int depart, int arrive, int poids = 0);
    ~Arete();

    int Getsommet_d() { return m_sommet_d; }
    void Setsommet_d(int val) { m_sommet_d = val; }
    int Getsommet_a() { return m_sommet_a; }
    void Setsommet_a(int val) { m_sommet_a = val; }
};


#endif // ARETE_H_INCLUDED
