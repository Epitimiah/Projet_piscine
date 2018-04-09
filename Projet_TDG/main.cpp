#include "grman/grman.h"
#include <iostream>

#include "graph.h"

int main()
{


    //g.delete_arete(2); ///Vouée à ne plus etre là
    //g.delete_sommet(3); ///Same

    /// Vous gardez la main sur la "boucle de jeu"
    /// ( contrairement à des frameworks plus avancés )
    while ( !key[KEY_ESC] )
    {
        Graphe g;
        g.menu();
        rest(20);

    }

    grman::fermer_allegro();

    return 0;
}
END_OF_MAIN();
