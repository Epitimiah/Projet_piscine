#ifndef SOMMET_H_INCLUDED
#define SOMMET_H_INCLUDED

#include <allegro.h>
#include <string>

class Sommet
{
private :
    std::string m_nom;
    BITMAP * m_image;
    int m_nbr_arete;
    int m_pos_x;
    int m_pos_y;
public :
    Sommet();
    Sommet(std::string nom);
    Sommet(std::string nom, int nombre_arete, int position_x=0, int position_y=0);
    ~Sommet();
};

#endif // SOMMET_H_INCLUDED
