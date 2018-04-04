#ifndef GRAPHE_H_INCLUDED
#define GRAPHE_H_INCLUDED

#include <vector>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <stack>
#include <stdlib.h>

#include "Arete.h"
#include "Sommet.h"

class Graphe
{
private :
    std::vector <Arete> m_arete;
    std::vector <Sommet> m_sommet;
    int m_ordre;
public :
    Graphe();
    Graphe(std::vector <Arete> arete, std::vector <Sommet> sommet);
    ~Graphe();

    int LoadFile(std::string namefile);
};


#endif // GRAPHE_H_INCLUDED
