#include "grman/grman.h"
#include <iostream>

#include "graph.h"

int main()
{
    Graphe g;

    //g.delete_arete(2); ///Vou�e � ne plus etre l�
    //g.delete_sommet(3); ///Same

    /// Vous gardez la main sur la "boucle de jeu"
    /// ( contrairement � des frameworks plus avanc�s )
    while ( !key[KEY_ESC] )
    {
        g.menu();
    }

    grman::fermer_allegro();

    return 0;
}
END_OF_MAIN();


