#include "Sommet.h"

Sommet::Sommet()
{   }

Sommet::Sommet(std::string nom) : m_nom(nom)
{   }

Sommet::Sommet(std::string nom, int nombre_arete, int position_x, int position_y) : m_nom(nom), m_nbr_arete(nombre_arete), m_pos_x(position_x), m_pos_y(position_y)
{   }

Sommet::~Sommet()
{   }
