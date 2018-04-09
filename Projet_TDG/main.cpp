#include "grman/grman.h"
#include <iostream>

#include "graph.h"

int main()
{
    Graphe g;

    //g.delete_arete(2); ///Vouée à ne plus etre là
    //g.delete_sommet(3); ///Same

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


