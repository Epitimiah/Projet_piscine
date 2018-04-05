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
    ///Le if verifie si le fichier a pu être ouvert.
    if(file)
    {
        file >> forder;
        m_ordre = forder;
        getline(file, data1);

        ///Boucle for récuperant chaque influenceur.
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
            for(auto elem : m_sommet)
            {
                std::cout << elem.getPos_x() << " " << elem.m_pos_y << std::endl;
            }
        }

        ///Boucle for créant les aretes.
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

/**int Graphe::SaveFile(std::string namefile)
{
    bool done = false;
    std::string data1, data2, data3, data4;
    int ent1, ent2, ent3, ent4;
    int forder;
    std::ifstream file(namefile, std::ios::in);
    ///Le if verifie si le fichier a pu être ouvert.
    if(file)
    {

    }
}*/

void Graphe::DisplayChaine()
{
    std::cout << std::endl << "Voici comment les influenceurs tirent les ficeles entre eux." << std::endl << std::endl;
    ///Ici je parcours le vecteur d'arete du graph et j'affiche le nom des influenceurs ainsi que de leurs influencés
    for(auto elem : m_arete)
    {
        std::cout << elem.m_sommet_a.m_nom << " de position : " << elem.m_sommet_a.getPos_x() << " " << elem.m_sommet_a.getPos_y() << " est le pantin de :" << std::endl;
        std::cout << elem.m_sommet_d.m_nom << " de position : " << elem.m_sommet_d.getPos_x() << " " << elem.m_sommet_d.getPos_y() << std::endl;
        std::cout << " Cette liaison est de poids : " << elem.m_poids << std::endl;
    }
    for(auto elem : m_arete)
    {
        std::cout << elem.m_sommet_a.m_pos_x << std::endl;
    }
}
