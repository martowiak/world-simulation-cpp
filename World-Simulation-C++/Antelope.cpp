#include "Antelope.h"

Antelope::Antelope(int x, int y, World* world) : Animal("Antelope", 'a', 4, 4, 0, x, y, world)
{
}

void Antelope::Action()
{
	int* possibleX = new int[4];
	int* possibleY = new int[4];
	int numberOfPossibilities = 0;

	GeneratePossibleMoves(2, possibleX, possibleY, &numberOfPossibilities); //generate possible moves of legth 2
	this->Movement(possibleX, possibleY, &numberOfPossibilities);
}

void Antelope::Collision(Organism* attacker)
{
	int* possibleX = new int[4];
	int* possibleY = new int[4];
	int numberOfPossibilities = 0;

	world->GenerateEmptyCells(possibleX, possibleY, &numberOfPossibilities, this->GetX(), this->GetY());

	if (numberOfPossibilities != 0 && rand() % 100 > 50) {//it has 50% chance to escape from fight if there is a possiblity
		this->Escape(numberOfPossibilities, possibleX, possibleY);
		attacker->Draw();
	}
	else {
		Animal::Collision(attacker);
	}
}
