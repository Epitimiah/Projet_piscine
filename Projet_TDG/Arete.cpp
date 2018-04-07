#include "Arete.h"

Arete::Arete()
{   }

Arete::Arete(int depart, int arrive, int poids, bool active) : m_sommet_d(depart), m_sommet_a(arrive), m_poids(poids), m_active(active)
{   }

Arete::~Arete()
{   }
