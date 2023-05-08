#include "Fox.h"

Fox::Fox(int x, int y, World* world) : Animal("Fox", 'f', 3, 7, 0, x, y, world)
{
}

void Fox::GenerateFoxPossibleMoves(int* possibleX, int* possibleY, int* numberOfPossibilities)
{
	if (pos_y - 1 > 0) //if organism is not in the first row it can move up
	{	
		if (world->GetCell(pos_x, pos_y - 1) == nullptr || world->GetCell(pos_x, pos_y - 1) != nullptr && world->GetCell(pos_x, pos_y - 1)->GetStrength() <= this->GetStrength()) {
			possibleX[*numberOfPossibilities] = pos_x;
			possibleY[*numberOfPossibilities] = pos_y - 1;
			(*numberOfPossibilities)++;
		}
	}
	if (pos_y + 1 < world->GetSizeY() + 1) //if organism is not in the last row it can move down
	{
		if (world->GetCell(pos_x, pos_y + 1) == nullptr || world->GetCell(pos_x, pos_y + 1) != nullptr && world->GetCell(pos_x, pos_y + 1)->GetStrength() <= this->GetStrength()) {
			possibleX[*numberOfPossibilities] = pos_x;
			possibleY[*numberOfPossibilities] = pos_y + 1;
			(*numberOfPossibilities)++;
		}
	}
	if (pos_x - 1 > 0) //if organism is not in the first column it can move left
	{
		if (world->GetCell(pos_x - 1, pos_y) == nullptr || world->GetCell(pos_x - 1, pos_y) != nullptr && world->GetCell(pos_x - 1, pos_y)->GetStrength() <= this->GetStrength()) {
			possibleX[*numberOfPossibilities] = pos_x - 1;
			possibleY[*numberOfPossibilities] = pos_y;
			(*numberOfPossibilities)++;
		}
	}
	if (pos_x + 1 < world->GetSizeX() + 1) //if organism is not in the last column it can move right
	{
		if (world->GetCell(pos_x + 1, pos_y) == nullptr || world->GetCell(pos_x + 1, pos_y) != nullptr && world->GetCell(pos_x + 1, pos_y)->GetStrength() <= this->GetStrength()) {
			possibleX[*numberOfPossibilities] = pos_x + 1;
			possibleY[*numberOfPossibilities] = pos_y;
			(*numberOfPossibilities)++;
		}
	}
}

void Fox::Action()
{
	int* possibleX = new int[4];
	int* possibleY = new int[4];
	int numberOfPossibilities = 0;

	GenerateFoxPossibleMoves(possibleX, possibleY, &numberOfPossibilities);

	this->Movement(possibleX, possibleY, &numberOfPossibilities);
}

