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
    std::string nom, nom_image, nb_arete_c, f_pos_x, f_pos_y, f_actif;
    int e_arete_c, e_pos_x, e_pos_y, e_actif;
    std::string forder;
    bool actif = false;
    std::ifstream file(namefile, std::ios::in);
    ///Le if verifie si le fichier a pu être ouvert.
    if(file)
    {
        file >> forder;
        m_ordre = atoi(forder.c_str());
        //std::cout << m_ordre << std::endl;
        getline(file, nom);

        ///Boucle for récuperant chaques données.
        for(int i = 0; i < m_ordre; i++)
        {
            getline(file, nom);
            getline(file, nom_image);
            getline(file, nb_arete_c);
            e_arete_c = atoi(nb_arete_c.c_str());
            getline(file, f_pos_x);
            e_pos_x = atoi(f_pos_x.c_str());
            getline(file, f_pos_y);
            e_pos_y = atoi(f_pos_y.c_str());
            getline(file, f_actif);
            e_actif = atoi(f_actif.c_str());
            nbaretes.push(e_arete_c);
            if(e_actif == 1)
            {
                actif = true;
                m_sommet.push_back(Sommet(nom, nom_image, e_arete_c, e_pos_x, e_pos_y, actif));
                actif = false;
            }
            else
            {
                m_sommet.push_back(Sommet(nom, nom_image, e_arete_c, e_pos_x, e_pos_y, actif));
            }
            std::cout << nbaretes.top() << std::endl;

        }
        std::string num_s_1, num_s_2, f_poids, f_active;
        int e_som_1, e_som_2, e_poids, e_active;
        ///Boucle for créant les aretes.
        for(int k = 0; k < m_ordre; k++)
        {
            for(int j = 0; j < nbaretes.top() ; j++)
            {
                getline(file, num_s_1);
                e_som_1 = atoi(num_s_1.c_str());
                getline(file, num_s_2);
                e_som_2 = atoi(num_s_2.c_str());
                getline(file, f_poids);
                e_poids = atoi(f_poids.c_str());
                getline(file, f_active);
                e_active = atoi(f_active.c_str());
                if(e_active == 1)
                {
                    actif = true;
                    m_arete.push_back(Arete(e_som_1, e_som_2, e_poids, actif));
                    actif = false;
                }
                else
                {
                    m_arete.push_back(Arete(e_som_1, e_som_2, e_poids, actif));
                }
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
            if(elem.m_actif)
            {
                file << "1" << std::endl;
            }
            else
            {
                file << "0" << std::endl;
            }
        }
        for(auto elem : m_arete)
        {
            file << elem.m_sommet_d << std::endl << elem.m_sommet_a << std::endl << elem.m_poids << std::endl;
            if(elem.m_active)
            {
                file << "1" << std::endl;
            }
            else
            {
                file << "0" << std::endl;
            }
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
    std::cout << std::endl << "Voici comment les sommet interagissent entre eux." << std::endl << std::endl;
    ///Ici je parcours le vecteur d'arete du graph et j'affiche le nom des sommet
    for(auto elem : m_arete)
    {
        std::cout << elem.m_sommet_d << " de position : " << m_sommet[elem.m_sommet_d-1].m_pos_x << " " << m_sommet[elem.m_sommet_d-1].m_pos_y;
        if(m_sommet[elem.m_sommet_d-1].m_actif)
            std::cout << " est actif ";
        else
            std::cout << " n'est pas actif ";
        std::cout << " et est un sommet oriente vers : "<< std::endl;
        std::cout << elem.m_sommet_a << " de position : " << m_sommet[elem.m_sommet_a-1].m_pos_x << " " << m_sommet[elem.m_sommet_a-1].m_pos_y;
        if(m_sommet[elem.m_sommet_a-1].m_actif)
            std::cout << " est actif " << std::endl;
        else
            std::cout << " n'est pas actif " << std::endl;
        std::cout << "Cette liaison est de poids : " << elem.m_poids << std::endl << std::endl;
    }
}




void Graphe::AddSommet(Sommet added_sommet)
{
    added_sommet.Setactif(true);
}

void Graphe::SuppSommet(Sommet supressed_sommet)
{
    supressed_sommet.Setactif(false);
}

void Graphe::AddArete(Arete added_arete)
{
    added_arete.Setactive(true);
}

void Graphe::SuppArete(Arete supressed_arete)
{
    supressed_arete.Setactive(false);
}

