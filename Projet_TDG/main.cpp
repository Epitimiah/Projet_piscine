#include "grman/grman.h"
#include <iostream>

#include "graph.h"

/* Parfois il faut faire add files et ajouter "Sommet.h/.cpp" "Arete.h/.cpp" et "Graphe.h/.cpp"
car elles sont inclues dans le code mais n'apparaissent souvent pas lors de la 1re ouverture du code
Nous nous sommes servi du code de M.Fercoq */

int main()
{
    //Boucle de jeu
    while ( !key[KEY_ESC] )
    {
        //On declare un graphe
        Graphe g;
        //On appelle la fonctione menu pour faire charger les fichers de graphe
        g.menu();
        //Un rest pour rendre l'affichage plus propre et fluide
        rest(20);
    }

    grman::fermer_allegro();

    return 0;
}
END_OF_MAIN();
