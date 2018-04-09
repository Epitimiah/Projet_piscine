#include "grman/grman.h"
#include <iostream>

#include "graph.h"

int main()
{
    /// A appeler en 1er avant d'instancier des objets graphiques etc...
    //grman::init();

    /// Le nom du répertoire où se trouvent les images à charger
    //grman::set_pictures_path("pics");

    Graphe g;
    //g.LoadFile("graphe.txt");

    g.delete_arete(2); ///Vouée à ne plus etre là
    g.delete_sommet(3); ///Same
    //g.SaveFile();

    /// Vous gardez la main sur la "boucle de jeu"
    /// ( contrairement à des frameworks plus avancés )
    while ( !key[KEY_ESC] )
    {
        g.menu();
    }

    grman::fermer_allegro();

    return 0;
}
END_OF_MAIN();


