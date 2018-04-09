#include "Sommet.h"

Sommet_g::Sommet_g() : m_groupe(0), m_groupe_F(0),m_marque_p(false),m_marque_m(false), m_marque(false)
{   }

Sommet_g::Sommet_g(std::string nom) : m_nom(nom), m_groupe(0), m_groupe_F(0),m_marque_p(false),m_marque_m(false), m_marque(false)
{   }

Sommet_g::~Sommet_g()
{   }
