#include "Turtle.h"

Turtle::Turtle(int x, int y, World* world) : Animal("Turtle", 't', 2, 1, 0, x, y, world)
{
}

void Turtle::Action()
{
	int* possibleX = new int[4];
	int* possibleY = new int[4];
	int numberOfPossibilities = 0;

	GeneratePossibleMoves(1, possibleX, possibleY, &numberOfPossibilities);

	if (rand() % 100 > 75) {
		this->Movement(possibleX, possibleY, &numberOfPossibilities);
	}
	else {
		cout << "Turtle stayed at its place" << endl;
	}
}
