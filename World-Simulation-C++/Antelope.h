#pragma once
#include "Animal.h"
class Antelope :
    public Animal
{
public:
    //constructor
    Antelope(int x, int y, World* world);
    void Action() override;
    void Collision(Organism* attacker) override;
};

