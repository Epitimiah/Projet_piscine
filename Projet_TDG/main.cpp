#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <stdlib.h>


#include "Graphe.h"

using namespace std;

int main()
{
    allegro_init();
    bool done1 = false;
    bool done2 = false;
    std::string NameFile;
    Graphe * test;
    test = new Graphe;

    /// Ici nous demandons le nom du fichier texte à ouvrir.
    /**std::cout << "Veuillez nous indiquez le nom du fichier a ouvrir : " << std::endl;
    std::cin >> NameFile;
    done1 = test->LoadFile(NameFile);*/
    done1 = test->LoadFile("test.txt");
    while (done1 == false)
    {
        std::cout << "Veuillez nous indiquez le nom du fichier a ouvrir : " << std::endl;
        std::cin >> NameFile;
        done1 = test->LoadFile(NameFile);
    }

    cout << "Hello world!" << endl;

    test->DisplayChaine();

    /**std::cout << "Veuillez nous indiquez le nom du fichier a sauvegarder : " << std::endl;
    std::cin >> NameFile;
    done2 = test->SaveFile(NameFile);
    while (done2 == false)
    {
        std::cout << "Veuillez nous indiquez le nom du fichier a sauvegarder : " << std::endl;
        std::cin >> NameFile;
        done2 = test->SaveFile(NameFile);
    }*/

    delete test;
    return 0;
}
END_OF_MAIN();
