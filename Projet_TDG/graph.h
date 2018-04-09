#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

/**************************************************************
    Ici sont propos�es 3 classes fondamentales
            Vertex (=Sommet)
            Edge (=Ar�te ou Arc)
            Graph (=Graphe)

    Les ar�tes et les sommets et le graphe qu'ils constituent
    "travaillent" �troitement ensemble : pour cette raison les
    Vertex et Edge se d�clarent amis (friend) de Graph pour que
    ce dernier puisse librement acc�der aux membres (y compris
    protected ou private) de Vertex et Edge.

    Ces Classes peuvent �tres compl�t�es. Il est �galement possible
    de les d�river mais il est malheureusement assez difficile
    de d�river le "triplet" des 3 classes en maintenant des relations
    coh�rentes ( rechercher "c++ class covariance" et "c++ parallel inheritance"
    pour commencer .. ). Il est donc sans doute pr�f�rable, si possible,
    de "customiser" ces classes de base directement, sans h�ritage.

    Le mod�le propos� permet de repr�senter un graphe orient� �ventuellement
    pond�r�, les arcs portent une ou des informations suppl�mentaire(s).
    Les relations/navigations Arcs -> Sommets et Sommets -> Arcs se font
    dans les 2 sens et utilisent des INDICES et NON PAS DES ADRESSES (pointeurs)
    de telle sorte que la topologie du graphe puisse �tre assez facilement
    lue et �crite en fichier, et b�n�ficie d'une bonne lisibilit� en cas de bugs...

    Chaque arc poss�de 2 attributs principaux (en plus de son �ventuelle pond�ration)
        -> m_from (indice du sommet de d�part de l'arc )
        -> m_to (indice du sommet d'arriv�e de l'arc )

    Chaque sommet poss�de 2 liste d'arcs (en plus de ses attributs "internes", marquages...)
        -> m_in (liste des indices des arcs arrivant au sommet : acc�s aux pr�d�cesseurs)
        -> m_out (liste des indices des arcs partant du sommet : acc�s aux successeurs)

    Cependant le probl�me des indices (par rapport aux pointeurs) et qu'en cas
    de destruction d'une entit� (un arc et/ou un sommet sont enlev�s du graphe) alors :

    - Soit il faut reprendre toute la num�rotation pour "boucher le trou"
      (par exemple on a supprim� le sommet n�4, le sommet n�5 devient le 4, 6 devient 5 etc...)
      ce qui pose des probl�mes de stabilit� et de coh�rence, et une difficult� � r�-introduire
      le(s) m�me(s) �l�ment supprim� (au m�me indice)

    - Soit on admet que la num�rotation des sommets et arcs n'est pas contigue, c�d qu'il
      peut y avoir des "trous" : sommets 0 1 5 7 8, pas de sommets 2 ni 3 ni 4 ni 6. La num�rotation
      est stable mais on ne peut plus utiliser un simple vecteur pour ranger la liste de tous
      les arcs et tous les sommets aux indices correspondants, on peut utiliser une map
      qui associe un objet arc ou sommet � des indices arbitraires (pas forc�ment contigus)

    C'est cette 2�me approche qui est propos�e ici : dans la classe graphe vous trouverez
        -> map<int, Edge>   m_edges
        -> map<int, Vertex> m_vertices    (le pluriel de vertex est vertices)

    Il faudra �tre attentif au fait que par rapport � un simple vecteur, le parcours des �l�ments
    ne pourra PAS se faire avec un simple for (int i=0; i<m_edges.size(); ++i) ...m_edges[i]...
    et que les parcours � it�rateur ne donneront pas directement des Edge ou des Vertex
    mais des pairs, l'objet d'int�r�t se trouvant dans "second" ("first" contenant l'indice)
                for (auto &it = m_edges.begin(); it!=m_edges.end(); ++it) ...it->second...
    ou bien     for (auto &e : m_edges) ...e.second...

    Il n'est pas obligatoire d'utiliser ces classes pour le projet, vous pouvez faire les votres

    Au niveau de l'interface, on dissocie une classe interface associ�e � chaque classe fondamentale
    de telle sorte qu'il soit possible de travailler avec des graphes non repr�sent�s � l'�cran
    Imaginons par exemple qu'on doive g�n�rer 1000 permutations de graphes pour tester des
    combinaisons, on ne souhaite pas repr�senter graphiquement ces 1000 graphes, et les
    interfaces p�sent lourd en ressource, avec cette organisation on est libre de r�server ou
    pas une interface de pr�sentation associ�e aux datas (d�couplage donn�es/interface)

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
    // Les (methodes des) classes amies pourront acc�der
    // directement aux attributs (y compris priv�s)
    friend class Sommet;
    friend class AreteInterface;
    friend class Graphe;

    private :

        /// Les widgets de l'interface. N'oubliez pas qu'il ne suffit pas de d�clarer
        /// ici un widget pour qu'il apparaisse, il faut aussi le mettre en place et
        /// le param�trer ( voir l'impl�mentation du constructeur dans le .cpp )

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

        // Une boite pour le label pr�c�dent
        grman::WidgetText m_box_label_idx;

    public :

        // Le constructeur met en place les �l�ments de l'interface
        // voir l'impl�mentation dans le .cpp
        SommetInterface(int idx, int x, int y, std::string pic_name="", int pic_idx=0);
};


class Sommet
{
    // Les (methodes des) classes amies pourront acc�der
    // directement aux attributs (y compris priv�s)
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

        /// liste des indices des arcs arrivant au sommet : acc�s aux pr�d�cesseurs
        std::vector<int> m_in;

        /// liste des indices des arcs partant du sommet : acc�s aux successeurs
        std::vector<int> m_out;

        /// un exemple de donn�e associ�e � l'arc, on peut en ajouter d'autres...
        double m_value;

        /// le POINTEUR sur l'interface associ�e, nullptr -> pas d'interface
        std::shared_ptr<SommetInterface> m_interface = nullptr;

        // Docu shared_ptr : https://msdn.microsoft.com/fr-fr/library/hh279669.aspx
        // La ligne pr�c�dente est en gros �quivalent � la ligne suivante :
        // VertexInterface * m_interface = nullptr;


    public:
        //Constructeur par defaut
        Sommet();
        //Constructeurs surchag�s
        Sommet(std::string nom);
        Sommet(std::string nom, std::string nom_image, int nombre_arete, int position_x = 0, int position_y = 0);
        /// Les constructeurs sont � compl�ter selon vos besoin...
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
        /// Vertex �tant g�r� par Graph ce sera la m�thode update de graph qui appellera
        /// le pre_update et post_update de Vertex (pas directement la boucle de jeu)
        /// Voir l'impl�mentation Graph::update dans le .cpp
        void pre_update();
        void post_update();
};



/***************************************************
                    EDGE
****************************************************/

class AreteInterface
{
    // Les (methodes des) classes amies pourront acc�der
    // directement aux attributs (y compris priv�s)
    friend class Arete;
    friend class Graphe;

    private :

        /// Les widgets de l'interface. N'oubliez pas qu'il ne suffit pas de d�clarer
        /// ici un widget pour qu'il apparaisse, il faut aussi le mettre en place et
        /// le param�trer ( voir l'impl�mentation du constructeur dans le .cpp )

        // Le WidgetEdge qui "contient" toute l'interface d'un arc
        grman::WidgetEdge m_top_edge;

        // Une boite pour englober les widgets de r�glage associ�s
        grman::WidgetBox m_box_edge;

        // Un slider de visualisation/modification du poids valeur de l'arc
        grman::WidgetVSlider m_slider_weight;

        // Un label de visualisation du poids de l'arc
        grman::WidgetText m_label_weight;

    public :

        // Le constructeur met en place les �l�ments de l'interface
        // voir l'impl�mentation dans le .cpp
        AreteInterface(Sommet& depart, Sommet& arrive);
};


class Arete
{
    // Les (methodes des) classes amies pourront acc�der
    // directement aux attributs (y compris priv�s)
    friend class Graphe;
    friend class AreteInterface;

    private :
        //Indice du sommet de depart de l'arete
        int m_sommet_d;
        //Indice du sommet d'arriv�e de l'arete
        int m_sommet_a;
        //Indique le poids port�s par l'arete
        double m_poids;

        /// le POINTEUR sur l'interface associ�e, nullptr -> pas d'interface
        std::shared_ptr<AreteInterface> m_interface = nullptr;

    public:
        Arete();

        //Constructeurs surcharg�s
        Arete(int depart, int arrive, int poids = 0);

        /// Les constructeurs sont � compl�ter selon vos besoin...
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

        /// Edge �tant g�r� par Graph ce sera la m�thode update de graph qui appellera
        /// le pre_update et post_update de Edge (pas directement la boucle de jeu)
        /// Voir l'impl�mentation Graph::update dans le .cpp
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

        /// Les widgets de l'interface. N'oubliez pas qu'il ne suffit pas de d�clarer
        /// ici un widget pour qu'il apparaisse, il faut aussi le mettre en place et
        /// le param�trer ( voir l'impl�mentation du constructeur dans le .cpp )

        /// La boite qui contient toute l'interface d'un graphe
        grman::WidgetBox m_top_box;

        /// Dans cette boite seront ajout�s les (interfaces des) sommets et des arcs...
        grman::WidgetBox m_main_box;

        /// Dans cette boite seront ajout�s des boutons de contr�le etc...
        grman::WidgetBox m_tool_box;

        grman::WidgetButton m_ajout;
        grman::WidgetText m_nomAjout;

        grman::WidgetButton m_suppr;
        grman::WidgetText m_nomSuppr;


        // A compl�ter �ventuellement par des widgets de d�coration ou
        // d'�dition (boutons ajouter/enlever ...)

    public :

        // Le constructeur met en place les �l�ments de l'interface
        // voir l'impl�mentation dans le .cpp
        GrapheInterface(int x, int y, int w, int h);
};


class Graphe
{
    private :

        int m_ordre;

        /// La "liste" des ar�tes
        std::map<int, Arete> m_aretes;

        /// La liste des sommets
        std::map<int, Sommet> m_sommets;

        /// le POINTEUR sur l'interface associ�e, nullptr -> pas d'interface
        std::shared_ptr<GrapheInterface> m_interface = nullptr;


    public:
        //Constructeur surcharge

        /// Les constructeurs sont � compl�ter selon vos besoin...
        /// Ici on ne donne qu'un seul constructeur qui peut utiliser une interface
        Graphe (GrapheInterface *interface=nullptr) :
            m_interface(interface)  {  }

        //Destructeur
        ~Graphe();
        //Methodes

        void add_interfaced_sommet(int idx, double value, int x, int y, std::string pic_name="", int pic_idx=0 );
        void add_interfaced_arete(int idx, int vert1, int vert2, double poids);
        //Fonction qui charge le graphe � partir d'un fichier
        void LoadFile(std::string name);
        //Fonction qui sauvegarde le graphe dans un fichier
        void SaveFile();
        //Fonction pour la dynamique des populations
        void reguPopulation();
        //Fonction qui supprime les aretes
        void delete_arete(int indice);
        //Fonction qui supprime les sommets
        void delete_sommet(int indice);

        //Fonction qui permet d'avoir des boutons � l'ecran pour les differentes fonctions telles que la suppression ou l'ajout
        void toolBarre();
        //Fonction qui permet de faire apparaitre un menu pour choisir entre les 3 grahes
        void menu();

        /// La m�thode update � appeler dans la boucle de jeu pour les graphes avec interface
        void update();
};


#endif // GRAPH_H_INCLUDED
