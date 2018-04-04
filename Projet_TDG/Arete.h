#ifndef ARETE_H_INCLUDED
#define ARETE_H_INCLUDED

class Arete
{
private :
    int m_sommet_d;
    int m_sommet_a;
    int m_poids;
public :
    Arete();
    Arete(int depart, int arrive, int poids=1);
    ~Arete();
};


#endif // ARETE_H_INCLUDED
