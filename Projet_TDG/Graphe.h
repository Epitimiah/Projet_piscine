#ifndef GRAPHE_H_INCLUDED
#define GRAPHE_H_INCLUDED

#include "Arete.h"
#include "Sommet.h"
#include <vector>

class Graphe
{
private :
    std::vector <Arete> m_arete;
    std::vector <Sommet> m_sommet;
public :
    Graphe();
    Graphe(std::vector <Arete> arete, std::vector <Sommet> sommet);
    ~Graphe();
};


#endif // GRAPHE_H_INCLUDED
