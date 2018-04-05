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
    std::string data1, data2, data3, data4, data5;
    int ent1, ent2, ent3;
    int forder;
    std::ifstream file(namefile, std::ios::in);
    ///Le if verifie si le fichier a pu être ouvert.
    if(file)
    {
        file >> forder;
        m_ordre = forder;
        getline(file, data1);

        ///Boucle for récuperant chaques données.
        for(int i = 0; i < m_ordre; i++)
        {
            getline(file, data1);
            getline(file, data5);
            getline(file, data2);
            ent1 = atoi(data2.c_str());
            getline(file, data3);
            ent2 = atoi(data3.c_str());
            getline(file, data4);
            ent3 = atoi(data4.c_str());
            nbaretes.push(ent1);
            m_sommet.push_back(Sommet(data1, data5, ent1, ent2, ent3));
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
                ent1 = atoi(data1.c_str());
                getline(file, data2);
                ent2 = atoi(data2.c_str());
                getline(file, data3);
                ent3 = atoi(data3.c_str());
                m_arete.push_back(Arete(ent1, ent2, ent3));
            }
            nbaretes.pop();
        }
        file.close();
        done = true;

    }

    else
    {
        std::cout << "Le fichier " << namefile << " n'est pas utilisable." << std::endl;
        done = false;
    }
    return done;
}

int Graphe::SaveFile(std::string namefile)
{
    bool done = false;
    std::string data1, data2, data3, data4;
    int ent1, ent2, ent3, ent4;
    int gorder;
    std::ofstream file(namefile, std::ios::trunc);
    ///Le if verifie si le fichier a pu être ouvert.
    if(file)
    {
        gorder = m_sommet.size();
        file << gorder << std::endl;
        for(auto elem : m_sommet)
        {
            file << elem.m_nom << std::endl << elem.m_nom_image << std::endl <<elem.m_nbr_arete << std::endl << elem.m_pos_x << std::endl << elem.m_pos_y << std::endl;
        }
        for(auto elem : m_arete)
        {
            file << elem.m_sommet_d << std::endl << elem.m_sommet_a << std::endl << elem.m_poids << std::endl;
        }
        done = true;
        file.close();
        std::cout << "Save done." << std::endl;
    }
    else
    {
        std::cout << "Le fichier " << namefile << " n'est pas utilisable." << std::endl;
    done = false;
    }
}

void Graphe::DisplayChaine()
{
    std::cout << std::endl << "Voici comment les influenceurs tirent les ficeles entre eux." << std::endl << std::endl;
    ///Ici je parcours le vecteur d'arete du graph et j'affiche le nom des influenceurs ainsi que de leurs influencés
    for(auto elem : m_arete)
    {
        std::cout << elem.m_sommet_d << " de position : " << m_sommet[elem.m_sommet_d-1].m_pos_x << " " << m_sommet[elem.m_sommet_d-1].m_pos_y << " est un sommet oriente vers : "<< std::endl;
        std::cout << elem.m_sommet_a << " de position : " << m_sommet[elem.m_sommet_a-1].m_pos_x << " " << m_sommet[elem.m_sommet_a-1].m_pos_y << std::endl;
        std::cout << " Cette liaison est de poids : " << elem.m_poids << std::endl << std::endl;
    }
}
