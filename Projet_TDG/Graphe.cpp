#include "Graphe.h"

Graphe::Graphe()
{
}

Graphe::Graphe(std::vector <Arete> arete, std::vector <Sommet> sommet)
    : m_arete(arete), m_sommet(sommet)
{
}

Graphe::~Graphe()
{
}

/// Ici le constructeur se contente de préparer un cadre d'accueil des
/// éléments qui seront ensuite ajoutés lors de la mise ne place du Graphe
GraphInterface::GraphInterface(int x, int y, int w, int h)
{
    m_top_box.set_dim(1000,740);
    m_top_box.set_gravity_xy(grman::GravityX::Right, grman::GravityY::Up);

    m_top_box.add_child(m_tool_box);
    m_tool_box.set_dim(80,720);
    m_tool_box.set_gravity_xy(grman::GravityX::Left, grman::GravityY::Up);
    m_tool_box.set_bg_color(BLANCBLEU);

    m_top_box.add_child(m_main_box);
    m_main_box.set_dim(908,720);
    m_main_box.set_gravity_xy(grman::GravityX::Right, grman::GravityY::Up);
    m_main_box.set_bg_color(BLANCJAUNE);
}

/// La méthode update à appeler dans la boucle de jeu pour les graphes avec interface
void Graphe::update()
{
    if (!m_interface)
        return;

    for (auto &elt : m_sommet)
        elt.second.pre_update();

    for (auto &elt : m_arete)
        elt.second.pre_update();

    m_interface->m_top_box.update();

    for (auto &elt : m_sommet)
        elt.second.post_update();

    for (auto &elt : m_arete)
        elt.second.post_update();

}



