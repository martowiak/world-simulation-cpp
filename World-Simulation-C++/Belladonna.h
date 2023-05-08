#pragma once
#include "Plant.h"
class Belladonna :
    public Plant
{
public:

    //constructor
    Belladonna(int x, int y, World* world);

    void Collision(Organism* attacker) override;
};

