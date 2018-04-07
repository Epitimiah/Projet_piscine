#ifndef SOMMET_H_INCLUDED
#define SOMMET_H_INCLUDED

#include <allegro.h>
#include <string>
#include <iostream>
#include "GraphMan.h"
#include "widget.h"

class VertexInterface
{
    // Les (methodes des) classes amies pourront accéder
    // directement aux attributs (y compris privés)
    friend class Arete;
    friend class EdgeInterface;
    friend class Graphe;

    private :

        /// Les widgets de l'interface. N'oubliez pas qu'il ne suffit pas de déclarer
        /// ici un widget pour qu'il apparaisse, il faut aussi le mettre en place et
        /// le paramétrer ( voir l'implémentation du constructeur dans le .cpp )

        // La boite qui contient toute l'interface d'un sommet
        grman::WidgetBox m_top_box;

        // Un slider de visualisation/modification de la valeur du sommet
        grman::WidgetVSlider m_slider_value;

        // Un label de visualisation de la valeur du sommet
        grman::WidgetText m_label_value;

        // Une image de "remplissage"
        grman::WidgetImage m_img;

        // Un label indiquant l'index du sommet
        grman::WidgetText m_label_idx;

        // Une boite pour le label précédent
        grman::WidgetText m_box_label_idx;

    public :

        // Le constructeur met en place les éléments de l'interface
        // voir l'implémentation dans le .cpp
        VertexInterface(int idx, int x, int y, std::string pic_name="", int pic_idx=0);
};

class Sommet
{
    friend class Graphe;
    friend class VertexInterface;
    friend class Arete;
    friend class EdgeInterface;

private :
    std::string m_nom;
    BITMAP * m_image;
    int m_nbr_arete;
    int m_pos_x;
    int m_pos_y;

    /// un exemple de donnée associée à l'arc, on peut en ajouter d'autres...
    double m_value;
    /// le POINTEUR sur l'interface associée, nullptr -> pas d'interface
    std::shared_ptr<VertexInterface> m_interface = nullptr;


public :
    //Constructeur par defaut
    Sommet();
    //Constructeur surcharge
    Sommet(std::string nom, int nombre_arete, int position_x=0, int position_y=0);
    /// Ici on ne donne qu'un constructeur qui peut utiliser une interface
    Sommet(double value=0, VertexInterface *interface=nullptr)
        : m_value(value), m_interface(interface)  {  }
    //Destructeur
    ~Sommet();

    //Getters et Setters
    std::string getNom() { return m_nom; }
    void setNom(std::string nom) { m_nom = nom; }

    BITMAP* getImage() { return m_image; }
    void setImage(BITMAP* image) { m_image = image; }

    int getNb_arete() { return m_nbr_arete; }
    void setNb_arete(int nombre_arete) { m_nbr_arete = nombre_arete; }

    int getPos_x() { return m_pos_x; }
    void setPos_x(int position_x) { m_pos_x = position_x; }

    int getPos_y() { return m_pos_y; }
    void setPos_y(int position_y) { m_pos_y = position_y; }

    //Methodes

    /// Vertex étant géré par Graph ce sera la méthode update de graph qui appellera
    /// le pre_update et post_update de Vertex (pas directement la boucle de jeu)
    /// Voir l'implémentation Graph::update dans le .cpp
    void pre_update();
    void post_update();
};

#endif // SOMMET_H_INCLUDED
