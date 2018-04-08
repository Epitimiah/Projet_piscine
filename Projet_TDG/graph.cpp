#include "graph.h"


/***************************************************
                    SOMMET
****************************************************/

/// Le constructeur met en place les �l�ments de l'interface
SommetInterface::SommetInterface(int idx, int x, int y, std::string pic_name, int pic_idx)
{
    // La boite englobante
    m_top_box.set_pos(x, y);
    m_top_box.set_dim(130, 100);
    m_top_box.set_moveable();

    // Le slider de r�glage de valeur
    m_top_box.add_child( m_slider_value );
    m_slider_value.set_range(0.0 , 100.0); // Valeurs arbitraires, � adapter...
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
    /** Ici on load la bitmap de chaque sommet � sa cr�ation. */
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

/// Gestion du Vertex avant l'appel � l'interface
void Sommet::pre_update()
{
    if (!m_interface)
        return;

    /// Copier la valeur locale de la donn�e m_value vers le slider associ�
    m_interface->m_slider_value.set_value(m_value);

    /// Copier la valeur locale de la donn�e m_value vers le label sous le slider
    m_interface->m_label_value.set_message( std::to_string( (int)m_value) );
}


/// Gestion du sommet apr�s l'appel � l'interface
void Sommet::post_update()
{
    if (!m_interface)
        return;

    /// Reprendre la valeur du slider dans la donn�e m_value locale
    m_value = m_interface->m_slider_value.get_value();
}



/***************************************************
                    ARETE
****************************************************/

/// Le constructeur met en place les �l�ments de l'interface
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

    // Une boite pour englober les widgets de r�glage associ�s
    m_top_edge.add_child(m_box_edge);
    m_box_edge.set_dim(24,60);
    m_box_edge.set_bg_color(BLANCBLEU);

    // Le slider de r�glage de valeur
    m_box_edge.add_child( m_slider_weight );
    m_slider_weight.set_range(0.0 , 100.0); // Valeurs arbitraires, � adapter...
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


/// Gestion du Edge avant l'appel � l'interface
void Arete::pre_update()
{
    if (!m_interface)
        return;

    /// Copier la valeur locale de la donn�e m_weight vers le slider associ�
    m_interface->m_slider_weight.set_value(m_poids);

    /// Copier la valeur locale de la donn�e m_weight vers le label sous le slider
    m_interface->m_label_weight.set_message( std::to_string( (int)m_poids ) );
}

/// Gestion du Edge apr�s l'appel � l'interface
void Arete::post_update()
{
    if (!m_interface)
        return;

    /// Reprendre la valeur du slider dans la donn�e m_weight locale
    m_poids = m_interface->m_slider_weight.get_value();
}



/***************************************************
                    GRAPHE
****************************************************/

/// Ici le constructeur se contente de pr�parer un cadre d'accueil des
/// �l�ments qui seront ensuite ajout�s lors de la mise ne place du Graphe
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


Graphe::~Graphe()
{
}

void Graphe::LoadFile()
{
    std::ifstream fichier("graphe.txt");
        int nbAretes = 0, nbSommets = 0, x = 0, y = 0, sommet_depart = 0, sommet_arrivee = 0;
        double valeur = 0, poids = 0;
        int n = 0;
        std::string nom;

    m_interface = std::make_shared<GrapheInterface> (50, 0, 750, 600);
    if(fichier.is_open())
    {

        fichier >> nbAretes;
        fichier >> nbSommets;

        //Boucle pour charger les sommets
        for(int i = 0 ; i < nbSommets ; i++)
        {
            fichier >> nom;
            fichier >> valeur;
            fichier >> x;
            fichier >> y;
            add_interfaced_sommet(i, valeur, x, y, nom, 1);
        }

        //Boucle pour charger les aretes
        for(int j = 0 ; j < nbAretes ; j ++)
        {
            fichier >> sommet_depart;
            fichier >> sommet_arrivee;
            fichier >> poids;
            fichier >> n;
            add_interfaced_arete(j, sommet_depart, sommet_arrivee, poids,n);
        }

    }
    else
    {
        std::cerr << "Probleme de chargement de fichier" << std::endl;
    }
}


void Graphe::SaveFile()
{
    std::ofstream fichiersave("graphesave.txt", std::ios::out);

    fichiersave << m_aretes.size() << std::endl;
    fichiersave << m_sommets.size() << std::endl;

    for(auto &elem : m_sommets)
    {
        fichiersave << elem.second.m_interface->m_img.get_pic_name() << " ";
        fichiersave << elem.second.m_value << " ";
        fichiersave << elem.second.m_interface->m_top_box.get_frame().pos.x << " ";
        fichiersave << elem.second.m_interface->m_top_box.get_frame().pos.y << " ";
        fichiersave << std::endl;
    }
    //Cela remet toutes les aretes � 0 et je n'arrive pas � savoir pourquoi
    for(auto &elem : m_aretes)
    {

        fichiersave << elem.second.m_sommet_d << " ";
        fichiersave << elem.second.m_sommet_a << " ";
        fichiersave << elem.second.m_poids << " ";
        fichiersave << std::endl;
    }
    fichiersave.close();
}

//Coef 5 � mettre � chacun des differents animaux mais en mettre un diff�rent
void Graphe::reguPopulation()
{
    for(int i = 0; i < m_aretes.size() ; i++)
    {
        std::cout << m_aretes[i].m_poids << "<-" << m_aretes[i].m_sommet_d << std::endl;

    }
    /*for(auto &elem : m_sommets)
    {
         elem.second.m_value = elem.second.m_value + 5 * elem.second.m_value * (1-elem.second.m_value/4);

    }*/
}

/// La m�thode update � appeler dans la boucle de jeu pour les graphes avec interface
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

/// Aide � l'ajout de sommets interfac�s
void Graphe::add_interfaced_sommet(int idx, double value, int x, int y, std::string pic_name, int pic_idx )
{
    if ( m_sommets.find(idx)!=m_sommets.end() )
    {
        std::cerr << "Error adding vertex at idx=" << idx << " already used..." << std::endl;
        throw "Error adding vertex";
    }
    // Cr�ation d'une interface de sommet
    SommetInterface *vi = new SommetInterface(idx, x, y, pic_name, pic_idx);
    // Ajout de la top box de l'interface de sommet
    m_interface->m_main_box.add_child(vi->m_top_box);
    // On peut ajouter directement des vertices dans la map avec la notation crochet :
    m_sommets[idx] = Sommet(value, vi);
}

/// Aide � l'ajout d'arcs interfac�s
void Graphe::add_interfaced_arete(int idx, int id_vert1, int id_vert2, double poids, int n)
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

    /// OOOPS ! Prendre en compte l'arc ajout� dans la topologie du graphe !
    m_aretes[idx].m_sommet_d = id_vert1;
    m_aretes[idx].m_sommet_a = id_vert2;

    m_sommets[id_vert1].m_out.push_back(idx);
    m_sommets[id_vert2].m_in.push_back(idx);


}

void Graphe::delete_edge(int indice)
{

        ///Ecrire l'arete dans mon fichier cimetiere
/// r�f�rence vers le Edge � enlever
        Arete &remed=m_aretes.at(indice);
/// test : on a bien des �l�ments interfac�s
        if (m_interface && remed.m_interface)
        {
            m_interface->m_main_box.remove_child( remed.m_interface->m_top_edge);
            /// Il reste encore � virer l'arc supprim� de la liste des entrants et sortants des 2 sommets to et from !
            /// References sur les listes de edges des sommets from et to
            std::vector<int> &vefrom = m_sommets[remed.m_sommet_d].m_out;
            std::vector<int> &veto = m_sommets[remed.m_sommet_a].m_in;
            vefrom.erase( std::remove( vefrom.begin(), vefrom.end(),indice ), vefrom.end() );
            veto.erase( std::remove(veto.begin(),veto.end(),indice ), veto.end() );

/// Le Edge ne n�cessite pas non plus de delete car on n'a pas fait de new (s�mantique par valeur)
/// Il suffit donc de supprimer l'entr�e de la map pour supprimer � la fois l'Edge et le EdgeInterface
/// mais malheureusement ceci n'enlevait pas automatiquement l'interface top_edge en tant que child de main_box !
            m_aretes.erase(indice);

///// Tester la coh�rence : nombre d'arc entrants et sortants des sommets 1 et 2
//            std::cout << m_vertices[remed.m_from].m_in.size() << " " << m_vertices[remed.m_from].m_out.size() << std::endl;
//            std::cout << m_vertices[remed.m_to].m_in.size() << " " << m_vertices[remed.m_to].m_out.size() << std::endl;
//            std::cout << m_edges.size() << std::endl;

        }

}

void Graphe::delete_sommet(int indice)
{
    std::vector<int> a;
    Sommet &remed=m_sommets.at(indice);
    m_interface->m_main_box.remove_child( remed.m_interface->m_top_box);
    for(auto elem : m_aretes)
    {
        if(elem.second.m_sommet_a == indice || elem.second.m_sommet_d == indice)
        {
                a.push_back(elem.first);
        }
    }
    int taille = a.size();
    for(int i = 0;i<taille; i++)
    {
        delete_edge(a[i]);
    }

    m_sommets.erase(indice);
}
