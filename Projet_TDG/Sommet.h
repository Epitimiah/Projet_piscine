#ifndef SOMMET_H_INCLUDED
#define SOMMET_H_INCLUDED

#include <allegro.h>
#include <string>

#include <iostream>

class Sommet
{
    friend class Graphe;
private :
    std::string m_nom;
    std::string m_nom_image;
    BITMAP * m_image;
    int m_nbr_arete;
    int m_pos_x;
    int m_pos_y;
public :
    Sommet();
    Sommet(std::string nom);
    Sommet(std::string nom, std::string nom_image, int nombre_arete, int position_x = 0, int position_y = 0);
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

};

#endif // SOMMET_H_INCLUDED
