#ifndef ARETE_H_INCLUDED
#define ARETE_H_INCLUDED

class Arete_g
{
friend class Graphe_g;

private :
    int m_sommet_d;
    int m_sommet_a;
    int m_poids;
public :
    Arete_g();
    Arete_g(int depart, int arrive, int poids=1);
    ~Arete_g();

    int Getsomd() { return m_sommet_d; }
    int Getsoma() { return m_sommet_a; }

    void Setsomd( int val ){ m_sommet_d = val; }
    void Setsoma( int val ){ m_sommet_a = val; }
};


#endif // ARETE_H_INCLUDED
