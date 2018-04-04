#include "Graphe.h"

Graphe::Graphe()
{   }

Graphe::Graphe(std::vector <Arete> arete, std::vector <Sommet> sommet) : m_arete(arete), m_sommet(sommet)
{   }

Graphe::~Graphe()
{   }

int Graphe::LoadFile(std::string namefile)
{
    bool done = false;
    std::stack<int> nbaretes;
    std::string data1, data2, data3, data4;
    int ent1, ent2, ent3, ent4;
    int forder;
    std::ifstream file(namefile, std::ios::in);
    ///Le if verifie si le fichier a pu �tre ouvert.
    if(file)
    {
        file >> forder;
        m_ordre = forder;
        getline(file, data1);

        ///Boucle for r�cuperant chaque influenceur.
        for(int i = 0; i < m_ordre; i++)
        {
            getline(file, data1);
            getline(file, data2);
            ent1 = atoi(data2.c_str());
            getline(file, data3);
            ent2 = atoi(data3.c_str());
            getline(file, data4);
            ent3 = atoi(data4.c_str());
            nbaretes.push(ent1);
            m_sommet.push_back(Sommet(data1, ent1, ent2, ent3));
        }

        ///Boucle for cr�ant les aretes.
        for(int k = 0; k < m_ordre; k++)
        {
            for(int j = 0; j < nbaretes.top() ; j++)
            {
                getline(file, data1);
                getline(file, data2);
                getline(file, data3);
                ent4 = atoi(data3.c_str());
                m_arete.push_back(Arete(Sommet(data1), Sommet(data2), ent4));
            }
            nbaretes.pop();
        }
        done = true;
        file.close();
    }
    else
    {
        std::cout << "Le fichier " << namefile << " n'est pas utilisable." << std::endl;
        done = false;
    }
    return done;
}
