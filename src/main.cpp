#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include "PlanetarySystem/PlanetarySystem.h"

int main() {
    PlanetarySpace::InterstellarVec3f* t = new PlanetarySpace::InterstellarVec3f(4, 5, 2);
    std::cout << t->x;
    delete t;
    t = nullptr;
}