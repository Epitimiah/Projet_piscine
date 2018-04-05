#include "Sommet.h"

Sommet::Sommet()
{   }

Sommet::Sommet(std::string nom) : m_nom(nom)
{   }

Sommet::Sommet(std::string nom, std::string nom_image, int nombre_arete, int position_x, int position_y) : m_nom(nom), m_nom_image(nom_image), m_nbr_arete(nombre_arete), m_pos_x(position_x), m_pos_y(position_y)
{
    m_image = load_bitmap(m_nom_image.c_str(), NULL);
        if (m_image)
        {
            std::cout << "Loaded " << m_nom_image << std::endl;
        }
        else
        {
                std::cout << "COULD NOT LOAD " << m_nom_image << std::endl;
        }
}

Sommet::~Sommet()
{   }
