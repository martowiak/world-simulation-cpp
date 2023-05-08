#pragma once
#include "Plant.h"
class Guarana :
    public Plant
{
public:

    //constructor
    Guarana(int x, int y, World* world);

    void Collision(Organism* attacker) override;
};

