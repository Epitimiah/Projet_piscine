#ifndef ARETE_H_INCLUDED
#define ARETE_H_INCLUDED

#include "Sommet.h"

class EdgeInterface
{
    // Les (methodes des) classes amies pourront accéder
    // directement aux attributs (y compris privés)
    friend class Arete;
    friend class Graphe;

    private :

        /// Les widgets de l'interface. N'oubliez pas qu'il ne suffit pas de déclarer
        /// ici un widget pour qu'il apparaisse, il faut aussi le mettre en place et
        /// le paramétrer ( voir l'implémentation du constructeur dans le .cpp )

        // Le WidgetEdge qui "contient" toute l'interface d'un arc
        grman::WidgetEdge m_top_edge;

        // Une boite pour englober les widgets de réglage associés
        grman::WidgetBox m_box_edge;

        // Un slider de visualisation/modification du poids valeur de l'arc
        grman::WidgetVSlider m_slider_weight;

        // Un label de visualisation du poids de l'arc
        grman::WidgetText m_label_weight;

    public :

        // Le constructeur met en place les éléments de l'interface
        // voir l'implémentation dans le .cpp
        EdgeInterface(Sommet& sommet_d, Sommet& sommet_a);
};

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
    /// Ici on ne donne qu'un seul constructeur qui peut utiliser une interface
    Arete (double poids=0, EdgeInterface *interface=nullptr)
    : m_poids(poids), m_interface(interface)  {  }
    //Destructeur
    ~Arete();

    //Getters et Setters
    Sommet getSommet_d() { return m_sommet_d; }
    void setSommet_d(Sommet depart) { m_sommet_d = depart; }

    Sommet getSommet_a() { return m_sommet_a; }
    void setSommet_a(Sommet arrive) { m_sommet_a = arrive; }

    int getPoids() { return m_poids; }
    void setPoids(int poids) { m_poids = poids; }

    //Methodes

    /// Edge étant géré par Graph ce sera la méthode update de graph qui appellera
    /// le pre_update et post_update de Edge (pas directement la boucle de jeu)
    /// Voir l'implémentation Graph::update dans le .cpp
    void pre_update();
    void post_update();
};


#endif // ARETE_H_INCLUDED
