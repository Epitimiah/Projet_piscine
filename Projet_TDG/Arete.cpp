#include "Arete.h"

Arete::Arete()
{
}

Arete::Arete(Sommet depart, Sommet arrive, int poids)
    : m_sommet_d(depart), m_sommet_a(arrive), m_poids(poids)
{
}

Arete::~Arete()
{
}
