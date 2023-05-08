#pragma once
#include "Plant.h"
class SowThistle :
    public Plant
{
public:

    //constructor
    SowThistle(int x, int y, World* world);

    void Action() override;
};

