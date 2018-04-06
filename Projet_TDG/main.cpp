/* Sources : Code fourni par M.Fercoq ainsi que ceux sur son site : http://www.ece.fr/~fercoq/allegro/
 Utilisation de sprites Pokémon & Zelda pour les bitmap */

#include <iostream>

#include "GraphMan.h"

//Programme permettant de charger et de verifier l'exsitence d'une bitmap avant son utilisation
BITMAP * load_bitmap_check(char *nomImage)
{
    BITMAP *bmp;
    bmp = load_bitmap(nomImage,NULL);
    //Boucle qui affiche un message d'erreur sur l'ecran d'allegro si l'image n'existe pas ou dont le lien est erroné
    if (!bmp)
    {
        allegro_message("pas pu trouver %s",nomImage);
        exit(EXIT_FAILURE);
    }
    return bmp;
}



int main()
{
    BITMAP *page;
    BITMAP *fond;
    BITMAP *collision;

    grman::init();

    page = create_bitmap(SCREEN_W, SCREEN_H);


    fond = load_bitmap_check("pics/fond.bmp");
    collision = load_bitmap_check("pics/fond_colli.bmp");

    //Boucle de jeu pour allegro
    //Pour fermer le programme il suffit d'appuyer sur la touche "échap"
    while ( !key[KEY_ESC] )
    {
        clear(page);

        blit(fond, page, 0, 0, 0, 0, SCREEN_W, SCREEN_H);




        blit(page, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);

        /// Mise à jour générale (clavier/souris/buffer etc...)
        grman::mettre_a_jour();
    }
    grman::fermer_allegro();

    return 0;
}
END_OF_MAIN();
