#include "grman/grman.h"
#include <iostream>

#include "graph.h"

int main()
{
    /// Vous gardez la main sur la "boucle de jeu"
    /// ( contrairement à des frameworks plus avancés )
    while ( !key[KEY_ESC] )
    {
        //On declare un graphe
        Graphe g;
        //On appelle la fonctione menu pour faire charger les fichers de graphe
        g.menu();
        //Un petit rest pour rendre l'affichage plus propre
        rest(20);
    }

    grman::fermer_allegro();

    return 0;
}
END_OF_MAIN();
