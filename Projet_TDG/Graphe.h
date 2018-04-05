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
    //Constructeur par defaut
    Graphe();
    //Constructeur surchargé
    Graphe(std::vector <Arete> arete, std::vector <Sommet> sommet);
    //Destructeur
    ~Graphe();

    //Getters et setters
    std::vector <Arete> getArete() { return m_arete; }
    void setArete(std::vector <Arete> arete) { m_arete = arete; }

    std::vector <Sommet> getSommet() { return m_sommet; }
    void setSommet(std::vector <Sommet> sommet) { m_sommet = sommet; }
};


#endif // GRAPHE_H_INCLUDED
