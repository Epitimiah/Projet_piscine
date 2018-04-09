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
    m_slider_value.set_range(0.0, 100.0);  // Valeurs arbitraires, à adapter...
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

Sommet_g Sommet::to_Sommet_g()
{
    Sommet_g retour(m_nom);
    return retour;
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
        std::cerr << "Error creating AreteInterface between vertices having no interface" << std::endl;
        throw "Bad AreteInterface instanciation";
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
    m_slider_weight.set_range(0.0, 100.0);  // Valeurs arbitraires, à adapter...
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



Arete_g Arete::to_Arete_g()
{
    Arete_g retour(m_sommet_d, m_sommet_a, m_poids);
    return retour;
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


Graphe::~Graphe()
{
}

void Graphe::LoadFile(std::string name)
{
    std::ifstream fichier(name);
    //std::ifstream fichier("graphe.txt"); ///A utiliser si on ne veut pas passer par le menu
    //Declaration des variables
    int nbAretes = 0, nbSommets = 0, x = 0, y = 0, sommet_depart = 0, sommet_arrivee = 0;
    double valeur = 0, poids = 0;
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
            add_interfaced_arete(j, sommet_depart, sommet_arrivee, poids);
        }
    }
    else
    {
        std::cerr << "Probleme de chargement de fichier" << std::endl;
    }
}

//Fonction qui ecrit dans un fichier les donnees du graphe
void Graphe::SaveFile()
{
    std::ofstream fichiersave("graphesave.txt", std::ios::out);

    //Sauvegarde le nombre d'aretes
    fichiersave << m_aretes.size() << std::endl;
    //Sauvegarde le nombre de sommets
    fichiersave << m_sommets.size() << std::endl;

    //Boucle pour la sauvegarde des elements des sommets
    for(auto &elem : m_sommets)
    {
        //Sauvegarde le nom des images
        fichiersave << elem.second.m_interface->m_img.get_pic_name() << " ";
        //Sauvegarde de la valeur (poids)
        fichiersave << elem.second.m_value << " ";
        //Sauvegarde de la position de x
        fichiersave << elem.second.m_interface->m_top_box.get_frame().pos.x << " ";
        //Sauvegarde de la position de y
        fichiersave << elem.second.m_interface->m_top_box.get_frame().pos.y << " ";
        fichiersave << std::endl;
    }

    //Boucle pour la sauvegarde des elements des aretes
    for(auto &elem : m_aretes)
    {
        //Sauvegarde sommet de depart
        fichiersave << elem.second.m_sommet_d << " ";
        //Sauvegarde sommet d'arrivee
        fichiersave << elem.second.m_sommet_a << " ";
        //Sauvegarde du poids
        fichiersave << elem.second.m_poids << " ";
        fichiersave << std::endl;
    }
    fichiersave.close();
}

void Graphe::reguPopulation()
{
    for(auto &elem : m_sommets)
    {
        elem.second.m_value = elem.second.m_value + 5 * elem.second.m_value * (1-elem.second.m_value/4);

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

        std::cout << to_Graphe_g().K_arete_Conex(5)<<std::endl;
    /*//Ajoute un
    if(buttonAJout)*/


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

    /// OOOPS ! Prendre en compte l'arc ajouté dans la topologie du graphe !
    m_aretes[idx].m_sommet_d = id_vert1;
    m_aretes[idx].m_sommet_a = id_vert2;

    m_sommets[id_vert1].m_out.push_back(idx);
    m_sommets[id_vert2].m_in.push_back(idx);
}

void Graphe::delete_arete(int indice)
{

    ///Ecrire l'arete dans mon fichier cimetiere
/// référence vers le Edge à enlever
    Arete &remed=m_aretes.at(indice);
/// test : on a bien des éléments interfacés
    if (m_interface && remed.m_interface)
    {
        m_interface->m_main_box.remove_child( remed.m_interface->m_top_edge);
        /// Il reste encore à virer l'arc supprimé de la liste des entrants et sortants des 2 sommets to et from !
        /// References sur les listes de edges des sommets from et to
        std::vector<int> &vefrom = m_sommets[remed.m_sommet_d].m_out;
        std::vector<int> &veto = m_sommets[remed.m_sommet_a].m_in;
        vefrom.erase( std::remove( vefrom.begin(), vefrom.end(),indice ), vefrom.end() );
        veto.erase( std::remove(veto.begin(),veto.end(),indice ), veto.end() );

/// Le Edge ne nécessite pas non plus de delete car on n'a pas fait de new (sémantique par valeur)
/// Il suffit donc de supprimer l'entrée de la map pour supprimer à la fois l'Edge et le EdgeInterface
/// mais malheureusement ceci n'enlevait pas automatiquement l'interface top_edge en tant que child de main_box !
        m_aretes.erase(indice);

///// Tester la cohérence : nombre d'arc entrants et sortants des sommets 1 et 2
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
    for(int i = 0; i<taille; i++)
    {
        delete_arete(a[i]);
    }

    m_sommets.erase(indice);
}

void Graphe::toolBarre()
{
    //rectfill
}


void Graphe::menu()
{
    //On initialise allegro et tout ses elements
    grman::init();

    /// Le nom du répertoire où se trouvent les images à charger
    grman::set_pictures_path("pics");

    //Declaration des variables et BITMAP
    std::string name = "";
    int x = 270;
    int y = 170;
    int espace_x = 200;
    int espace_y_case = 50;
    int espace_y_entre_case = 30;
    int texte_x_espace = 10;
    int texte_y_espace = 10;

    BITMAP* buffer;
    buffer = create_bitmap(800,600);

    //Fonciton pour recuperer notre graphe
    while(name == "" &&  !key[KEY_ESC] )
    {
        //Case pour choisir le graphe voulu
        rectfill(buffer, x, y,  x + espace_x, y + espace_y_case, makecol(255,0,0));
        rectfill(buffer, x, y + espace_y_case + espace_y_entre_case,  x + espace_x, y + espace_y_case*2 + espace_y_entre_case, makecol(255,0,0));
        rectfill(buffer, x, y + espace_y_case*2 + espace_y_entre_case*2,  x + espace_x, y + espace_y_case*3 + espace_y_entre_case*2, makecol(255,0,0));

        //texte
        textprintf_ex(buffer, font, x+ texte_x_espace, y + texte_y_espace, makecol(255,255,255), -1, "Graphe 1");
        textprintf_ex(buffer, font, x+ texte_x_espace, y + texte_y_espace + espace_y_case + espace_y_entre_case, makecol(255,255,255), -1, "Graphe 2");
        textprintf_ex(buffer, font, x+ texte_x_espace, y + texte_y_espace + (espace_y_case + espace_y_entre_case)*2, makecol(255,255,255), -1, "Graphe 3");

        //Boucles pour savoir où l'utilisateur appuie et ainsi charger le graphe correspondant
        if(mouse_b&1)
        {
            if(mouse_x > x && mouse_x < x + espace_x)
            {
                if(mouse_y > y && mouse_y < y + espace_y_case)
                {
                    name = "graphe.txt";
                }

                if(mouse_y > y + 80 && mouse_y < y + 130)
                {
                    name = "graphe2.txt";
                }

                if(mouse_y > y + 160 && mouse_y < y + 210)
                {
                    name = "graphe3.txt";
                }
            }
        }
        blit(buffer, screen, 0, 0, 0, 0,  SCREEN_W, SCREEN_H);

        //grman::mettre_a_jour();
        clear(buffer);
        rest(20);
    }
    //On charge le fichier du graphe choisi
    LoadFile(name);
    //On affiche tous les boutons nécessaire
    ///toolBarre();
    //On sauvegarde le graphe dans un autre fichier particulier à la sauvegarde
    SaveFile();

    while ( !key[KEY_ESC] )
    {
        /// Il faut appeler les méthodes d'update des objets qui comportent des widgets
        update();

        /// Mise à jour générale (clavier/souris/buffer etc...)
        grman::mettre_a_jour();
    }

}

Graphe_g Graphe::to_Graphe_g()
{
    std::vector <Sommet_g> sommet;
    std::vector <Arete_g> arete;

    for(auto elem : m_sommets) sommet.push_back(elem.second.to_Sommet_g());
    for(auto elem : m_aretes) arete.push_back(elem.second.to_Arete_g());

    Graphe_g retour (arete, sommet);
    retour.Setsuc();
    retour.Reinit_marque();

    return retour;
}

