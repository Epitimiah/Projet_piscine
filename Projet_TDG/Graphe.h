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
    int SaveFile(std::string namefile);
    void DisplayChaine();
    void AddArete(Arete added_arete);
    void AddSommet(Sommet added_sommet);
    void SuppArete(Arete supressed_arete);
    void SuppSommet(Sommet supressed_sommet);
};


#endif // GRAPHE_H_INCLUDED
