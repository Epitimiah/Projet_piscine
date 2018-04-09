#include "Graphe.h"


Graphe_g::Graphe_g()
{   }

Graphe_g::Graphe_g(std::vector <Arete_g> arete, std::vector <Sommet_g> sommet) : m_arete(arete), m_sommet(sommet)
{   }

Graphe_g::Graphe_g(const Graphe_g& copie) : m_arete(copie.m_arete), m_sommet(copie.m_sommet)
{   }

Graphe_g::~Graphe_g()
{   }

void Graphe_g::Setsuc()
{
    for( auto elem : m_arete )
    {
        m_sommet[elem.m_sommet_d].Addenlien(elem.m_sommet_a);
        m_sommet[elem.m_sommet_a].Addenlien(elem.m_sommet_d);
    }
}

void Graphe_g::Enlever_arrete(int idx)
{
    m_sommet[m_arete[idx].m_sommet_d].m_en_lien.erase(find(m_sommet[m_arete[idx].m_sommet_d].m_en_lien.begin(),m_sommet[m_arete[idx].m_sommet_d].m_en_lien.end(),m_arete[idx].m_sommet_a));
    m_sommet[m_arete[idx].m_sommet_a].m_en_lien.erase(find(m_sommet[m_arete[idx].m_sommet_a].m_en_lien.begin(),m_sommet[m_arete[idx].m_sommet_a].m_en_lien.end(),m_arete[idx].m_sommet_d));
    m_arete.erase(m_arete.begin() + idx);

}

void Graphe_g::Reinit_marque()
{
    for (unsigned int i=0 ; i<m_sommet.size(); i++)
    {
        m_sommet[i].Setmarque_m(false);
        m_sommet[i].Setmarque_p(false);
        m_sommet[i].Setmarque(false);
    }
}

void Graphe_g::DFS(int idx, int groupe)
{
    m_sommet[idx].Setmarque(true);
    m_sommet[idx].Setgroupe(groupe);
    for (auto elem : m_sommet[idx].m_en_lien)
    {
        if(m_sommet[elem].m_marque == false) DFS(elem, groupe);
    }
}

void Graphe_g::F_Conex(int idx, int groupe)
{
    m_sommet[idx].Setmarque_m(true);
    m_sommet[idx].Setmarque_p(true);
    std::cout << "cc" << std::endl;

    for(unsigned int i=0; i<m_arete.size(); i++)
    {
        for( auto elem : m_arete )
        {
            if( m_sommet[elem.m_sommet_d].m_marque_p == true )m_sommet[elem.m_sommet_a].Setmarque_p(true);
            if( m_sommet[elem.m_sommet_a].m_marque_m == true )m_sommet[elem.m_sommet_d].Setmarque_m(true);
        }
    }

    for(unsigned int i=0 ; i<m_sommet.size(); i++)
    {
        if( m_sommet[i].m_marque_p == true && m_sommet[i].m_marque_m == true)
        {
            m_sommet[i].m_groupe_F=groupe;
            m_sommet[i].m_marque=true;
        }
        m_sommet[i].m_marque_p = false;
        m_sommet[i].m_marque_m = false;
    }
}

int Graphe_g::Composantes_connex()
{
    Reinit_marque();
    int groupe=0;
    for (unsigned int i=0; i<m_sommet.size(); i++)
    {
        if( m_sommet[i].m_marque==false )
        {
            groupe++;
            DFS(i,groupe);
        }
    }
    return groupe;
}

int Graphe_g::Composantes_F_connex()
{
    int groupe=0;
    for (unsigned int i=0; i<m_sommet.size(); i++)
    {
        if( m_sommet[i].m_marque==false )
        {
            groupe++;
            F_Conex(i,groupe);
        }
    }
    Reinit_marque();
    return groupe;
}

std::vector<int> Graphe_g::Combinaison_arete(int K)
{
    std::vector<int> retour;
    std::string bitmask(K, 1);
    bitmask.resize(m_arete.size(), 0);

    do {
        for (unsigned int i = 0; i < m_arete.size(); ++i)
        {
            if (bitmask[i]) retour.push_back(i);
        }
    } while (std::prev_permutation(bitmask.begin(), bitmask.end()));

    return retour;
}

bool Graphe_g::Est_connex(std::vector <int> Arete_a_enlever)
{
    Reinit_marque();
    Graphe_g copie(*this);
    int plus_grand=Arete_a_enlever[0];
    int a_suprimer=0;
    unsigned int i=0;
    while( Arete_a_enlever.size()>0 )
    {
        a_suprimer=0;
        plus_grand=Arete_a_enlever[0];
        for (i=0; i<Arete_a_enlever.size(); i++)
        {
            if (Arete_a_enlever[i]>plus_grand)
            {
                plus_grand=Arete_a_enlever[i];
                a_suprimer=i;
            }
        }
        copie.Enlever_arrete(plus_grand);
        Arete_a_enlever.erase(Arete_a_enlever.begin()+a_suprimer);
    }
    std::cout << "ARETE : ";
    for( auto elem : copie.m_arete ) std::cout << elem.m_sommet_d << " : " << elem.m_sommet_a << "    ";
    std::cout << "SOMMET : ";
    for( auto elem : copie.m_sommet ) std::cout << elem.m_en_lien.size() << " ";
    std::cout << std::endl;
    if (copie.Composantes_connex()==1)return true;
    return false;
}

int Graphe_g::K_arete_Conex(int limite)
{
    std::vector <int> comb;
    std::vector <int> sous_comb;
    std::vector <int> retour;
    int j=0;
    Reinit_marque();
    if(Composantes_connex()!=1)return 0;
    Reinit_marque();
    for(int i=1; i<=limite; i++)
    {
        comb=Combinaison_arete(i);
        while(comb.size()>0)
        {
            sous_comb.clear();
            for(j=0; j<i; j++)
            {
                sous_comb.push_back(*comb.begin());
                comb.erase(comb.begin());
            }
            if(!Est_connex(sous_comb))return i;
        }
    }
    return 10000000;
}
