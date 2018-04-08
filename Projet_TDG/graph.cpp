#include "graph.h"


/***************************************************
                    SOMMET
****************************************************/

/// Le constructeur met en place les éléments de l'interface
SommetInterface::SommetInterface(int idx, int x, int y, std::string pic_name, int pic_idx)
{
    // La boite englobante
    m_top_box.set_pos(x, y);
    m_top_box.set_dim(130, 100);
    m_top_box.set_moveable();

    // Le slider de réglage de valeur
    m_top_box.add_child( m_slider_value );
    m_slider_value.set_range(0.0 , 100.0); // Valeurs arbitraires, à adapter...
    m_slider_value.set_dim(20,80);
    m_slider_value.set_gravity_xy(grman::GravityX::Left, grman::GravityY::Up);

    // Label de visualisation de valeur
    m_top_box.add_child( m_label_value );
    m_label_value.set_gravity_xy(grman::GravityX::Left, grman::GravityY::Down);

    // Une illustration...
    if (pic_name!="")
    {
        m_top_box.add_child( m_img );
        m_img.set_pic_name(pic_name);
        m_img.set_pic_idx(pic_idx);
        m_img.set_gravity_x(grman::GravityX::Right);
    }

    // Label de visualisation d'index du sommet dans une boite
    m_top_box.add_child( m_box_label_idx );
    m_box_label_idx.set_gravity_xy(grman::GravityX::Right, grman::GravityY::Down);
    m_box_label_idx.set_dim(20,12);
    m_box_label_idx.set_bg_color(BLANC);

    m_box_label_idx.add_child( m_label_idx );
    m_label_idx.set_message( std::to_string(idx) );
}

Sommet::Sommet()
{
}

Sommet::Sommet(std::string nom) : m_nom(nom)
{
}

Sommet::Sommet(std::string nom, std::string nom_image, int nombre_arete, int position_x, int position_y) : m_nom(nom), m_nom_image(nom_image), m_nbr_arete(nombre_arete), m_pos_x(position_x), m_pos_y(position_y)
{
    /** Ici on load la bitmap de chaque sommet à sa création. */
    m_image = load_bitmap(m_nom_image.c_str(), NULL);
        if (m_image)
        {
            std::cout << "Loaded " << m_nom_image << std::endl << std::endl;
        }
        else
        {
                std::cout << "COULD NOT LOAD " << m_nom_image << std::endl << std::endl;
        }
}

Sommet::~Sommet()
{
}

/// Gestion du Vertex avant l'appel à l'interface
void Sommet::pre_update()
{
    if (!m_interface)
        return;

    /// Copier la valeur locale de la donnée m_value vers le slider associé
    m_interface->m_slider_value.set_value(m_value);

    /// Copier la valeur locale de la donnée m_value vers le label sous le slider
    m_interface->m_label_value.set_message( std::to_string( (int)m_value) );
}


/// Gestion du sommet après l'appel à l'interface
void Sommet::post_update()
{
    if (!m_interface)
        return;

    /// Reprendre la valeur du slider dans la donnée m_value locale
    m_value = m_interface->m_slider_value.get_value();
}



/***************************************************
                    ARETE
****************************************************/

/// Le constructeur met en place les éléments de l'interface
AreteInterface::AreteInterface(Sommet& depart, Sommet& arrive)
{
    // Le WidgetEdge de l'interface de l'arc
    if ( !(depart.m_interface && arrive.m_interface) )
    {
        std::cerr << "Error creating EdgeInterface between vertices having no interface" << std::endl;
        throw "Bad EdgeInterface instanciation";
    }
    m_top_edge.attach_from(depart.m_interface->m_top_box);
    m_top_edge.attach_to(arrive.m_interface->m_top_box);
    m_top_edge.reset_arrow_with_bullet();

    // Une boite pour englober les widgets de réglage associés
    m_top_edge.add_child(m_box_edge);
    m_box_edge.set_dim(24,60);
    m_box_edge.set_bg_color(BLANCBLEU);

    // Le slider de réglage de valeur
    m_box_edge.add_child( m_slider_weight );
    m_slider_weight.set_range(0.0 , 100.0); // Valeurs arbitraires, à adapter...
    m_slider_weight.set_dim(16,40);
    m_slider_weight.set_gravity_y(grman::GravityY::Up);

    // Label de visualisation de valeur
    m_box_edge.add_child( m_label_weight );
    m_label_weight.set_gravity_y(grman::GravityY::Down);

}

Arete::Arete()
{
}

Arete::Arete(int depart, int arrive, int poids) : m_sommet_d(depart), m_sommet_a(arrive), m_poids(poids)
{
}

Arete::~Arete()
{
}


/// Gestion du Edge avant l'appel à l'interface
void Arete::pre_update()
{
    if (!m_interface)
        return;

    /// Copier la valeur locale de la donnée m_weight vers le slider associé
    m_interface->m_slider_weight.set_value(m_poids);

    /// Copier la valeur locale de la donnée m_weight vers le label sous le slider
    m_interface->m_label_weight.set_message( std::to_string( (int)m_poids ) );
}

/// Gestion du Edge après l'appel à l'interface
void Arete::post_update()
{
    if (!m_interface)
        return;

    /// Reprendre la valeur du slider dans la donnée m_weight locale
    m_poids = m_interface->m_slider_weight.get_value();
}



/***************************************************
                    GRAPHE
****************************************************/

/// Ici le constructeur se contente de préparer un cadre d'accueil des
/// éléments qui seront ensuite ajoutés lors de la mise ne place du Graphe
GrapheInterface::GrapheInterface(int x, int y, int w, int h)
{
    m_top_box.set_dim(1000,740);
    m_top_box.set_gravity_xy(grman::GravityX::Right, grman::GravityY::Up);

    m_top_box.add_child(m_tool_box);
    m_tool_box.set_dim(80,720);
    m_tool_box.set_gravity_xy(grman::GravityX::Left, grman::GravityY::Up);
    m_tool_box.set_bg_color(BLANCBLEU);

    m_top_box.add_child(m_main_box);
    m_main_box.set_dim(908,720);
    m_main_box.set_gravity_xy(grman::GravityX::Right, grman::GravityY::Up);
    m_main_box.set_bg_color(BLANCJAUNE);
}

/*Graphe::Graphe()
{
}*/

Graphe::Graphe(std::vector <Arete> arete, std::vector <Sommet> sommet) : m_arete(arete), m_sommet(sommet)
{
}

Graphe::~Graphe()
{
}

int Graphe::LoadFile(std::string namefile)
{
    bool done = false;
    std::stack<int> nbaretes;
    std::string data1, data2, data3, data4, data5;
    int ent1=0, ent2=0;
    double ent3;
    int forder=0;
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
            //m_sommet.push_back(Sommet(data1, data5, ent1, ent2, ent3));
            add_interfaced_sommet()
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
                //m_arete.push_back(Arete(ent1, ent2, ent3));
                add_interfaced_arete(j, ent1, ent2, ent3);
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

/// La méthode update à appeler dans la boucle de jeu pour les graphes avec interface
void Graphe::update()
{
    if (!m_interface)
        return;

    for (auto &elt : m_sommets)
        elt.second.pre_update();

    for (auto &elt : m_aretes)
        elt.second.pre_update();

    m_interface->m_top_box.update();

    for (auto &elt : m_sommets)
        elt.second.post_update();

    for (auto &elt : m_aretes)
        elt.second.post_update();

}

/// Aide à l'ajout de sommets interfacés
void Graphe::add_interfaced_sommet(int idx, double value, int x, int y, std::string pic_name, int pic_idx )
{
    if ( m_sommets.find(idx)!=m_sommets.end() )
    {
        std::cerr << "Error adding vertex at idx=" << idx << " already used..." << std::endl;
        throw "Error adding vertex";
    }
    // Création d'une interface de sommet
    SommetInterface *vi = new SommetInterface(idx, x, y, pic_name, pic_idx);
    // Ajout de la top box de l'interface de sommet
    m_interface->m_main_box.add_child(vi->m_top_box);
    // On peut ajouter directement des vertices dans la map avec la notation crochet :
    m_sommets[idx] = Sommet(value, vi);
}

/// Aide à l'ajout d'arcs interfacés
void Graphe::add_interfaced_arete(int idx, int id_vert1, int id_vert2, double poids)
{
    if ( m_aretes.find(idx)!=m_aretes.end() )
    {
        std::cerr << "Error adding edge at idx=" << idx << " already used..." << std::endl;
        throw "Error adding edge";
    }

    if ( m_sommets.find(id_vert1)==m_sommets.end() || m_sommets.find(id_vert2)==m_sommets.end() )
    {
        std::cerr << "Error adding edge idx=" << idx << " between vertices " << id_vert1 << " and " << id_vert2 << " not in m_vertices" << std::endl;
        throw "Error adding edge";
    }

    AreteInterface *ei = new AreteInterface(m_sommets[id_vert1], m_sommets[id_vert2]);
    m_interface->m_main_box.add_child(ei->m_top_edge);
    m_aretes[idx] = Arete(poids, ei);
}

