#include "Animal.h"
#include "Organism.h"
#include "Wolf.h"
#include "Sheep.h"
#include "Antelope.h"
#include "Turtle.h"
#include "Fox.h"

Animal::Animal(string name, char symbol, int strength, int initiative, int age, int x, int y, World* world) : Organism(name, symbol, strength, initiative, age, x, y, world) {}

Organism* Animal::CreateOrganism(int x, int y, World* world) //function needed to create a new organism after multiplication to avoid calling this function for all animals
{
	if (typeid(*this) == typeid(Wolf))
	{
		Wolf* animal = new Wolf(x, y, world);
		return animal;
	}
	else if (typeid(*this) == typeid(Sheep))
	{
		Sheep* animal = new Sheep(x, y, world);
		return animal;
	}
	else if (typeid(*this) == typeid(Fox))
	{
		Fox* animal = new Fox(x, y, world);
		return animal;
	}
	else if (typeid(*this) == typeid(Turtle))
	{
		Turtle* animal = new Turtle(x, y, world);
		return animal;
	}
	else if (typeid(*this) == typeid(Antelope))
	{
		Antelope* animal = new Antelope(x, y, world);
		return animal;
	}
}

void Animal::Action() {

	int* possibleX = new int[4];
	int* possibleY = new int[4];
	int numberOfPossibilities = 0;

	GeneratePossibleMoves(1, possibleX, possibleY, &numberOfPossibilities);

	this->Movement(possibleX, possibleY, &numberOfPossibilities);
}

void Animal::Collision(Organism* attacker)
{
	if (this->GetStrength() > attacker->GetStrength()) {

		cout << attacker->GetName() << ": was killed by " << this->GetName() << endl;
		world->DeleteOrganism(attacker);
		this->Draw();
	}
	else if (this->GetStrength() <= attacker->GetStrength()) {

		cout << this->GetName() << ": was killed by " << attacker->GetName() << endl;
		world->DeleteOrganism(this);
		attacker->Draw();
	}
}

bool Animal::IsAnimal()
{
	return true;
}

void Animal::GeneratePossibleMoves(int lengthOfMove, int* possibleX, int* possibleY, int* numberOfPossibilities) {

	if (pos_y - lengthOfMove > 0) //if organism is not in the first row it can move up
	{
		possibleX[*numberOfPossibilities] = pos_x;
		possibleY[*numberOfPossibilities] = pos_y - lengthOfMove;
		(*numberOfPossibilities)++;
	}
	if (pos_y + lengthOfMove < world->GetSizeY() + 1) //if organism is not in the last row it can move down
	{
		possibleX[*numberOfPossibilities] = pos_x;
		possibleY[*numberOfPossibilities] = pos_y + lengthOfMove;
		(*numberOfPossibilities)++;
	}
	if (pos_x - lengthOfMove > 0) //if organism is not in the first column it can move left
	{
		possibleX[*numberOfPossibilities] = pos_x - lengthOfMove;
		possibleY[*numberOfPossibilities] = pos_y;
		(*numberOfPossibilities)++;
	}
	if (pos_x + lengthOfMove < world->GetSizeX() + 1) //if organism is not in the last column it can move right
	{
		possibleX[*numberOfPossibilities] = pos_x + lengthOfMove;
		possibleY[*numberOfPossibilities] = pos_y;
		(*numberOfPossibilities)++;
	}
}

void Animal::Movement(int* possibleX, int* possibleY, int* numberOfPossibilities) {

	if (*numberOfPossibilities != 0)//if there are any possible moves
	{
		int random = rand() % *numberOfPossibilities; //we draw the new random position of the animal

		//if in possible new cell there is not any animal or not an animal of the same species and not a turtle 
		//or strength of this is equal/greater than 5 we can make a move to this cell
		if (world->GetCell(possibleX[random], possibleY[random]) == nullptr || (world->GetCell(possibleX[random], possibleY[random]) != nullptr && world->GetCell(possibleX[random], possibleY[random])->GetSymbol() != this->GetSymbol()) && (world->GetCell(possibleX[random], possibleY[random])->GetSymbol() != 't' || this->GetStrength() >= 5)) {

			world->SetCell(pos_x, pos_y, nullptr); //the animal will no longer be in this cell so we are assigning it to nullptr

			cout << this->GetName() << ": has moved from (" << pos_x << ", " << pos_y << ") to (";

			pos_x = possibleX[random];
			pos_y = possibleY[random];

			cout << pos_x << ", " << pos_y << ")" << endl;

			if (world->GetCell(possibleX[random], possibleY[random]) != nullptr) {//if the new cell is not empty there is a collision

				cout << this->GetName() << ": collides with " << world->GetCell(possibleX[random], possibleY[random])->GetName() << " on (" << possibleX[random] << ", " << possibleY[random] << ")" << endl;
				world->GetCell(possibleX[random], possibleY[random])->Collision(this);

				delete[] possibleX;
				delete[] possibleY;
				return;
			}
		}
		else if (world->GetCell(possibleX[random], possibleY[random])->GetSymbol() == 't' && this->GetStrength() < 5) {
			cout << "Turtle reflected " << this->GetName() << "'s attack" << endl;
		}
		else if (world->GetCell(possibleX[random], possibleY[random]) != nullptr && world->GetCell(possibleX[random], possibleY[random])->GetSymbol() == this->GetSymbol()){

			if (world->GetCell(possibleX[random], possibleY[random])->GetAge() >= this->GetAge()) { //it can multiply with an animal of the same spicies which is the same age or older
				this->Breeding(world->GetCell(possibleX[random], possibleY[random]));
			}
			else {
				cout << this->GetName() << ": can't multiply with younger organism, so it stays" << endl;
			}
		}
	}
	this->Draw();

	delete[] possibleX;
	delete[] possibleY;
}

void Animal::Breeding(Organism* organism)
{
	Organism* parent1 = organism;
	Organism* parent2 = this;

	int* possibleX = new int[6];
	int* possibleY = new int[6];
	int numberOfPossibilities = 0;

	world->GenerateEmptyCells(possibleX, possibleY, &numberOfPossibilities, parent1->GetX(), parent1->GetY());
	world->GenerateEmptyCells(possibleX, possibleY, &numberOfPossibilities, parent2->GetX(), parent2->GetY());

	if (numberOfPossibilities != 0)
	{
		int random = rand() % numberOfPossibilities;
		Organism* newBorn = this->CreateOrganism(possibleX[random], possibleY[random], world);
		world->AddOrganism(newBorn);
		cout << newBorn->GetName() << ": was born on (" << possibleX[random] << ", " << possibleY[random] << ")" << endl;
		world->SetNumberOfNewBorns(world->GetNumberOfNewBorns() + 1);
	}

	delete[] possibleX;
	delete[] possibleY;
}

void Animal::Escape(int numberOfPossibilities, int* possibleX, int* possibleY)
{
	int random = rand() % numberOfPossibilities;

	cout << this->GetName() << ": escaped from (" << pos_x << ", " << pos_y << ") to (";

	pos_x = possibleX[random];
	pos_y = possibleY[random];

	cout << pos_x << ", " << pos_y << ")" << endl;


	this->Draw();

	delete[] possibleX;
	delete[] possibleY;
}
