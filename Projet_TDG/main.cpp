#include "grman/grman.h"
#include <iostream>

#include "graph.h"

int main()
{


    //g.delete_arete(2); ///Vou�e � ne plus etre l�
    //g.delete_sommet(3); ///Same

    /// Vous gardez la main sur la "boucle de jeu"
    /// ( contrairement � des frameworks plus avanc�s )
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
