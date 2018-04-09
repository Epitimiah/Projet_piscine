#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

/**************************************************************
    Ici sont proposées 3 classes fondamentales
            Vertex (=Sommet)
            Edge (=Arête ou Arc)
            Graph (=Graphe)

    Les arêtes et les sommets et le graphe qu'ils constituent
    "travaillent" étroitement ensemble : pour cette raison les
    Vertex et Edge se déclarent amis (friend) de Graph pour que
    ce dernier puisse librement accéder aux membres (y compris
    protected ou private) de Vertex et Edge.

    Ces Classes peuvent êtres complétées. Il est également possible
    de les dériver mais il est malheureusement assez difficile
    de dériver le "triplet" des 3 classes en maintenant des relations
    cohérentes ( rechercher "c++ class covariance" et "c++ parallel inheritance"
    pour commencer .. ). Il est donc sans doute préférable, si possible,
    de "customiser" ces classes de base directement, sans héritage.

    Le modèle proposé permet de représenter un graphe orienté éventuellement
    pondéré, les arcs portent une ou des informations supplémentaire(s).
    Les relations/navigations Arcs -> Sommets et Sommets -> Arcs se font
    dans les 2 sens et utilisent des INDICES et NON PAS DES ADRESSES (pointeurs)
    de telle sorte que la topologie du graphe puisse être assez facilement
    lue et écrite en fichier, et bénéficie d'une bonne lisibilité en cas de bugs...

    Chaque arc possède 2 attributs principaux (en plus de son éventuelle pondération)
        -> m_from (indice du sommet de départ de l'arc )
        -> m_to (indice du sommet d'arrivée de l'arc )

    Chaque sommet possède 2 liste d'arcs (en plus de ses attributs "internes", marquages...)
        -> m_in (liste des indices des arcs arrivant au sommet : accès aux prédécesseurs)
        -> m_out (liste des indices des arcs partant du sommet : accès aux successeurs)

    Cependant le problème des indices (par rapport aux pointeurs) et qu'en cas
    de destruction d'une entité (un arc et/ou un sommet sont enlevés du graphe) alors :

    - Soit il faut reprendre toute la numérotation pour "boucher le trou"
      (par exemple on a supprimé le sommet n°4, le sommet n°5 devient le 4, 6 devient 5 etc...)
      ce qui pose des problèmes de stabilité et de cohérence, et une difficulté à ré-introduire
      le(s) même(s) élément supprimé (au même indice)

    - Soit on admet que la numérotation des sommets et arcs n'est pas contigue, càd qu'il
      peut y avoir des "trous" : sommets 0 1 5 7 8, pas de sommets 2 ni 3 ni 4 ni 6. La numérotation
      est stable mais on ne peut plus utiliser un simple vecteur pour ranger la liste de tous
      les arcs et tous les sommets aux indices correspondants, on peut utiliser une map
      qui associe un objet arc ou sommet à des indices arbitraires (pas forcément contigus)

    C'est cette 2ème approche qui est proposée ici : dans la classe graphe vous trouverez
        -> map<int, Edge>   m_edges
        -> map<int, Vertex> m_vertices    (le pluriel de vertex est vertices)

    Il faudra être attentif au fait que par rapport à un simple vecteur, le parcours des éléments
    ne pourra PAS se faire avec un simple for (int i=0; i<m_edges.size(); ++i) ...m_edges[i]...
    et que les parcours à itérateur ne donneront pas directement des Edge ou des Vertex
    mais des pairs, l'objet d'intérêt se trouvant dans "second" ("first" contenant l'indice)
                for (auto &it = m_edges.begin(); it!=m_edges.end(); ++it) ...it->second...
    ou bien     for (auto &e : m_edges) ...e.second...

    Il n'est pas obligatoire d'utiliser ces classes pour le projet, vous pouvez faire les votres

    Au niveau de l'interface, on dissocie une classe interface associée à chaque classe fondamentale
    de telle sorte qu'il soit possible de travailler avec des graphes non représentés à l'écran
    Imaginons par exemple qu'on doive générer 1000 permutations de graphes pour tester des
    combinaisons, on ne souhaite pas représenter graphiquement ces 1000 graphes, et les
    interfaces pèsent lourd en ressource, avec cette organisation on est libre de réserver ou
    pas une interface de présentation associée aux datas (découplage données/interface)

***********************************************************************************************/

#include <iostream>
#include <sstream>

#include <vector>
#include <map>
#include <string>
#include <memory>

#include <cstdlib>
#include <fstream>
#include <stack>
#include <stdlib.h>

#include "grman/grman.h"

/***************************************************
                    VERTEX
****************************************************/

class SommetInterface
{
    // Les (methodes des) classes amies pourront accéder
    // directement aux attributs (y compris privés)
    friend class Sommet;
    friend class AreteInterface;
    friend class Graphe;

    private :

        /// Les widgets de l'interface. N'oubliez pas qu'il ne suffit pas de déclarer
        /// ici un widget pour qu'il apparaisse, il faut aussi le mettre en place et
        /// le paramétrer ( voir l'implémentation du constructeur dans le .cpp )

        // La boite qui contient toute l'interface d'un sommet
        grman::WidgetBox m_top_box;

        // Un slider de visualisation/modification de la valeur du sommet
        grman::WidgetVSlider m_slider_value;

        // Un label de visualisation de la valeur du sommet
        grman::WidgetText m_label_value;

        // Une image de "remplissage"
        grman::WidgetImage m_img;

        // Un label indiquant l'index du sommet
        grman::WidgetText m_label_idx;

        // Une boite pour le label précédent
        grman::WidgetText m_box_label_idx;

    public :

        // Le constructeur met en place les éléments de l'interface
        // voir l'implémentation dans le .cpp
        SommetInterface(int idx, int x, int y, std::string pic_name="", int pic_idx=0);
};


class Sommet
{
    // Les (methodes des) classes amies pourront accéder
    // directement aux attributs (y compris privés)
    friend class Graphe;
    friend class SommetInterface;
    friend class Arete;
    friend class AreteInterface;

    private :
        std::string m_nom;
        std::string m_nom_image;
        BITMAP * m_image;
        int m_nbr_arete;
        int m_pos_x;
        int m_pos_y;

        /// liste des indices des arcs arrivant au sommet : accès aux prédécesseurs
        std::vector<int> m_in;

        /// liste des indices des arcs partant du sommet : accès aux successeurs
        std::vector<int> m_out;

        /// un exemple de donnée associée à l'arc, on peut en ajouter d'autres...
        double m_value;

        /// le POINTEUR sur l'interface associée, nullptr -> pas d'interface
        std::shared_ptr<SommetInterface> m_interface = nullptr;

        // Docu shared_ptr : https://msdn.microsoft.com/fr-fr/library/hh279669.aspx
        // La ligne précédente est en gros équivalent à la ligne suivante :
        // VertexInterface * m_interface = nullptr;


    public:
        //Constructeur par defaut
        Sommet();
        //Constructeurs surchagés
        Sommet(std::string nom);
        Sommet(std::string nom, std::string nom_image, int nombre_arete, int position_x = 0, int position_y = 0);
        /// Les constructeurs sont à compléter selon vos besoin...
        /// Ici on ne donne qu'un seul constructeur qui peut utiliser une interface
        Sommet(double value, SommetInterface *interface=nullptr):
            m_value(value), m_interface(interface) {  }

        //Destructeur
        ~Sommet();

        //Getters et Setters
        std::string getNom() { return m_nom; }
        void setNom(std::string nom) { m_nom = nom; }

        BITMAP* getImage() { return m_image; }
        void setImage(BITMAP* image) { m_image = image; }

        int getNb_arete() { return m_nbr_arete; }
        void setNb_arete(int nombre_arete) { m_nbr_arete = nombre_arete; }

        int getPos_x() { return m_pos_x; }
        void setPos_x(int position_x) { m_pos_x = position_x; }

        int getPos_y() { return m_pos_y; }
        void setPos_y(int position_y) { m_pos_y = position_y; }

        //Methodes
        /// Vertex étant géré par Graph ce sera la méthode update de graph qui appellera
        /// le pre_update et post_update de Vertex (pas directement la boucle de jeu)
        /// Voir l'implémentation Graph::update dans le .cpp
        void pre_update();
        void post_update();
};



/***************************************************
                    EDGE
****************************************************/

class AreteInterface
{
    // Les (methodes des) classes amies pourront accéder
    // directement aux attributs (y compris privés)
    friend class Arete;
    friend class Graphe;

    private :

        /// Les widgets de l'interface. N'oubliez pas qu'il ne suffit pas de déclarer
        /// ici un widget pour qu'il apparaisse, il faut aussi le mettre en place et
        /// le paramétrer ( voir l'implémentation du constructeur dans le .cpp )

        // Le WidgetEdge qui "contient" toute l'interface d'un arc
        grman::WidgetEdge m_top_edge;

        // Une boite pour englober les widgets de réglage associés
        grman::WidgetBox m_box_edge;

        // Un slider de visualisation/modification du poids valeur de l'arc
        grman::WidgetVSlider m_slider_weight;

        // Un label de visualisation du poids de l'arc
        grman::WidgetText m_label_weight;

    public :

        // Le constructeur met en place les éléments de l'interface
        // voir l'implémentation dans le .cpp
        AreteInterface(Sommet& depart, Sommet& arrive);
};


class Arete
{
    // Les (methodes des) classes amies pourront accéder
    // directement aux attributs (y compris privés)
    friend class Graphe;
    friend class AreteInterface;

    private :
        //Indice du sommet de depart de l'arete
        int m_sommet_d;
        //Indice du sommet d'arrivée de l'arete
        int m_sommet_a;
        //Indique le poids portés par l'arete
        double m_poids;

        /// le POINTEUR sur l'interface associée, nullptr -> pas d'interface
        std::shared_ptr<AreteInterface> m_interface = nullptr;

    public:
        Arete();

        //Constructeurs surchargés
        Arete(int depart, int arrive, int poids = 0);

        /// Les constructeurs sont à compléter selon vos besoin...
        /// Ici on ne donne qu'un seul constructeur qui peut utiliser une interface
        Arete(double poids, AreteInterface *interface=nullptr) :
            m_poids(poids), m_interface(interface)  {  }

        //Destructeur
        ~Arete();

        //Getters et setters
        int Getsommet_d() { return m_sommet_d; }
        void Setsommet_d(int val) { m_sommet_d = val; }

        int Getsommet_a() { return m_sommet_a; }
        void Setsommet_a(int val) { m_sommet_a = val; }

        //Methodes

        /// Edge étant géré par Graph ce sera la méthode update de graph qui appellera
        /// le pre_update et post_update de Edge (pas directement la boucle de jeu)
        /// Voir l'implémentation Graph::update dans le .cpp
        void pre_update();
        void post_update();
};




/***************************************************
                    GRAPHE
****************************************************/

class GrapheInterface
{
    friend class Graphe;

    private :

        /// Les widgets de l'interface. N'oubliez pas qu'il ne suffit pas de déclarer
        /// ici un widget pour qu'il apparaisse, il faut aussi le mettre en place et
        /// le paramétrer ( voir l'implémentation du constructeur dans le .cpp )

        /// La boite qui contient toute l'interface d'un graphe
        grman::WidgetBox m_top_box;

        /// Dans cette boite seront ajoutés les (interfaces des) sommets et des arcs...
        grman::WidgetBox m_main_box;

        /// Dans cette boite seront ajoutés des boutons de contrôle etc...
        grman::WidgetBox m_tool_box;

        grman::WidgetButton m_ajout;
        grman::WidgetText m_nomAjout;

        grman::WidgetButton m_suppr;
        grman::WidgetText m_nomSuppr;


        // A compléter éventuellement par des widgets de décoration ou
        // d'édition (boutons ajouter/enlever ...)

    public :

        // Le constructeur met en place les éléments de l'interface
        // voir l'implémentation dans le .cpp
        GrapheInterface(int x, int y, int w, int h);
};


class Graphe
{
    private :

        int m_ordre;

        /// La "liste" des arêtes
        std::map<int, Arete> m_aretes;

        /// La liste des sommets
        std::map<int, Sommet> m_sommets;

        /// le POINTEUR sur l'interface associée, nullptr -> pas d'interface
        std::shared_ptr<GrapheInterface> m_interface = nullptr;


    public:
        //Constructeur surcharge

        /// Les constructeurs sont à compléter selon vos besoin...
        /// Ici on ne donne qu'un seul constructeur qui peut utiliser une interface
        Graphe (GrapheInterface *interface=nullptr) :
            m_interface(interface)  {  }

        //Destructeur
        ~Graphe();
        //Methodes

        void add_interfaced_sommet(int idx, double value, int x, int y, std::string pic_name="", int pic_idx=0 );
        void add_interfaced_arete(int idx, int vert1, int vert2, double poids);
        //Fonction qui charge le graphe à partir d'un fichier
        void LoadFile(std::string name);
        //Fonction qui sauvegarde le graphe dans un fichier
        void SaveFile();
        //Fonction pour la dynamique des populations
        void reguPopulation();
        //Fonction qui supprime les aretes
        void delete_arete(int indice);
        //Fonction qui supprime les sommets
        void delete_sommet(int indice);

        //Fonction qui permet d'avoir des boutons à l'ecran pour les differentes fonctions telles que la suppression ou l'ajout
        void toolBarre();
        //Fonction qui permet de faire apparaitre un menu pour choisir entre les 3 grahes
        void menu();

        /// La méthode update à appeler dans la boucle de jeu pour les graphes avec interface
        void update();
};


#endif // GRAPH_H_INCLUDED
