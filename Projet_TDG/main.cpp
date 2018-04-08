#include "grman/grman.h"
#include <iostream>

#include "graph.h"

int main()
{
    /// A appeler en 1er avant d'instancier des objets graphiques etc...
    grman::init();

    /// Le nom du répertoire où se trouvent les images à charger
    grman::set_pictures_path("pics");

    /// Un exemple de graphe
    Graphe g;
    bool done1 = false;
    bool done2 = false;
    std::string NameFile;
    Graphe * test;
    test = new Graphe;

    /// Ici nous demandons le nom du fichier texte à ouvrir.
    std::cout << "Veuillez nous indiquez le nom du fichier a ouvrir : " << std::endl;
    std::cin >> NameFile;
    done1 = test->LoadFile(NameFile);
    while (done1 == false)
    {
        std::cout << "Veuillez nous indiquez le nom du fichier a ouvrir : " << std::endl;
        std::cin >> NameFile;
        done1 = test->LoadFile(NameFile);
    }

    test->DisplayChaine();

    std::cout << "Veuillez nous indiquez le nom du fichier a sauvegarder : " << std::endl;
    std::cin >> NameFile;
    done2 = test->SaveFile(NameFile);
    while (done2 == false)
    {
        std::cout << "Veuillez nous indiquez le nom du fichier a sauvegarder : " << std::endl;
        std::cin >> NameFile;
        done2 = test->SaveFile(NameFile);
    }


    /// Vous gardez la main sur la "boucle de jeu"
    /// ( contrairement à des frameworks plus avancés )
    while ( !key[KEY_ESC] )
    {
        /// Il faut appeler les méthodes d'update des objets qui comportent des widgets
        g.update();

        /// Mise à jour générale (clavier/souris/buffer etc...)
        grman::mettre_a_jour();
    }

    delete test;
    grman::fermer_allegro();

    return 0;
}
END_OF_MAIN();


