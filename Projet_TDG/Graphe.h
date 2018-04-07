#ifndef GRAPHE_H_INCLUDED
#define GRAPHE_H_INCLUDED

#include "Arete.h"

#include <vector>


class GraphInterface
{
    friend class Graphe;

    private :

        /// Les widgets de l'interface. N'oubliez pas qu'il ne suffit pas de d�clarer
        /// ici un widget pour qu'il apparaisse, il faut aussi le mettre en place et
        /// le param�trer ( voir l'impl�mentation du constructeur dans le .cpp )

        /// La boite qui contient toute l'interface d'un graphe
        grman::WidgetBox m_top_box;

        /// Dans cette boite seront ajout�s les (interfaces des) sommets et des arcs...
        grman::WidgetBox m_main_box;

        /// Dans cette boite seront ajout�s des boutons de contr�le etc...
        grman::WidgetBox m_tool_box;


        // A compl�ter �ventuellement par des widgets de d�coration ou
        // d'�dition (boutons ajouter/enlever ...)

    public :

        // Le constructeur met en place les �l�ments de l'interface
        // voir l'impl�mentation dans le .cpp
        GraphInterface(int x, int y, int w, int h);
};

class Graphe
{
private :
    std::vector <Arete> m_arete;
    std::vector <Sommet> m_sommet;

    /// le POINTEUR sur l'interface associ�e, nullptr -> pas d'interface
    std::shared_ptr <GraphInterface> m_interface = nullptr;

public :
    //Constructeur par defaut
    Graphe();
    //Constructeur surcharg�
    Graphe(std::vector <Arete> arete, std::vector <Sommet> sommet);
    /// Ici on ne donne qu'un seul constructeur qui peut utiliser une interface
    Graphe(GraphInterface *interface=nullptr)
        : m_interface(interface)  {  }
    //Destructeur
    ~Graphe();

    //Getters et setters
    std::vector <Arete> getArete() { return m_arete; }
    void setArete(std::vector <Arete> arete) { m_arete = arete; }

    std::vector <Sommet> getSommet() { return m_sommet; }
    void setSommet(std::vector <Sommet> sommet) { m_sommet = sommet; }

    /// La m�thode update � appeler dans la boucle de jeu pour les graphes avec interface
    void update();
};



#endif // GRAPHE_H_INCLUDED
