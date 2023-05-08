#pragma once
#include "Plant.h"
class SosnowskysHogweed :
    public Plant
{
public:

    //constructor
    SosnowskysHogweed(int x, int y, World* world);

    void Collision(Organism* attacker) override;
    void Action() override;
    void CheckNeighbourhood();
};

