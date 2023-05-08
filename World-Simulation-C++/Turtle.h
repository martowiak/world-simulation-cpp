#pragma once
#include "Animal.h"
class Turtle :
    public Animal
{
public:
    //constructor
    Turtle(int x, int y, World* world);
    void Action() override;
};

