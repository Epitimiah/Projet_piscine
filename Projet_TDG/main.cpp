/* Sources : Code fourni par M.Fercoq ainsi que ceux sur son site : http://www.ece.fr/~fercoq/allegro/ */

#include <iostream>

#include "grman/grman.h"

int main()
{
    allegro_init();
    install_keyboard();
    install_mouse();

    set_color_depth(desktop_color_depth());
    if (set_gfx_mode(GFX_AUTODETECT_WINDOWED,800,600,0,0)!=0)
    {
        allegro_message("prb gfx mode");
        allegro_exit();
        exit(EXIT_FAILURE);
    }
    //Boucle de jeu pour allegro
    //Pour fermer le programme il suffit d'appuyer sur la touche "échap"
    while ( !key[KEY_ESC] )
    {

    }
    return 0;


}
END_OF_MAIN();
