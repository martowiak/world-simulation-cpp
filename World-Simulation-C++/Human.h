#pragma once
#include "Animal.h"

class Human :
    public Animal
{

public:
    //constructor
    Human(int x, int y, World* world);

    void Action() override;
    void Collision(Organism* attacker) override;
};

