#ifndef ARETE_H_INCLUDED
#define ARETE_H_INCLUDED

#include "Sommet.h"

class Arete
{
private :
    Sommet m_sommet_d;
    Sommet m_sommet_a;
    int m_poids;

public :
    //Constructeur par defaut
    Arete();
    //Constructeur surcharge
    Arete(Sommet depart, Sommet arrive, int poids=1);
    //Destructeur
    ~Arete();

    //Getters et Setters
    Sommet getSommet_d() { return m_sommet_d; }
    void setSommet_d(Sommet depart) { m_sommet_d = depart; }

    Sommet getSommet_a() { return m_sommet_a; }
    void setSommet_a(Sommet arrive) { m_sommet_a = arrive; }

    int getPoids() { return m_poids; }
    void setPoids(int poids) { m_poids = poids; }
};


#endif // ARETE_H_INCLUDED
