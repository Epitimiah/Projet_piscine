#ifndef GRAPHE_H_INCLUDED
#define GRAPHE_H_INCLUDED

#include <iostream>
#include <algorithm>

#include "Arete.h"
#include "Sommet.h"

class Graphe_g
{
public :
    std::vector <Arete_g> m_arete;
    std::vector <Sommet_g> m_sommet;
public :
    Graphe_g();
    Graphe_g(std::vector <Arete_g> arete, std::vector <Sommet_g> sommet);
    Graphe_g(const Graphe_g& copie);
    ~Graphe_g();



    void Setsuc();
    void Reinit_marque();

    void Enlever_sommet();
    void Enlever_arrete(int idx);

    void DFS(int idx, int groupe);
    std::vector <int> Composantes_connex();
    void F_Conex(int idx, int groupe);
    std::vector <int> Composantes_F_connex();
    bool Est_connex(std::vector <int> Arete_a_enlever);
    std::vector<int> Combinaison_arete(int nbr);
    int K_arete_Conex(int limite);
};

#endif // GRAPHE_H_INCLUDED
