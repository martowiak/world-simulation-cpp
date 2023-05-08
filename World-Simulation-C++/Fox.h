#pragma once
#include "Animal.h"
class Fox :
    public Animal
{
public:
    //constructor
    Fox(int x, int y, World* world);
    void GenerateFoxPossibleMoves(int* possibleX, int* possibleY, int* numberOfPossibilities);
    void Action() override;
};

