#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <stdlib.h>


#include "Graphe.h"

using namespace std;

int main()
{
    allegro_init();
    bool done = false;
    std::string NameFile;
    Graphe * test;
    test = new Graphe;
    /// Ici nous demandons le nom du fichier texte à ouvrir.
    std::cout << "Veuillez nous indiquez le nom du fichier a ouvrir : " << std::endl;
    std::cin >> NameFile;
    done = test->LoadFile(NameFile);
    while (done == false)
    {
        std::cout << "Veuillez nous indiquez le nom du fichier a ouvrir : " << std::endl;
        std::cin >> NameFile;
        done = test->LoadFile(NameFile);
    }

    cout << "Hello world!" << endl;
    delete test;
    return 0;
}
END_OF_MAIN();
