#include "Human.h"
#include <conio.h>

#define UP_KEY 72
#define RIGHT_KEY 77
#define DOWN_KEY 80
#define LEFT_KEY 75
#define ABILITY 120

Human::Human(int x, int y, World* world) : Animal("Human", 'X', 5, 4, 0, x, y, world)
{
}

void Human::Action()
{
	cout << "Now it's your turn to move, you are a human - X, if you want to activate special ability press 'x' or/and choose direction by pressing an arrow" << endl;

	char choice;
	char temp = _getch();

	if (temp == ABILITY) {
		if (world->IsAbilityActivated()) {
			cout << "The ability is already activated" << endl;
		}
		else if (!world->IsAbilityActivated() && world->GetTurnsWithAbility() > 0) {
			cout << "You have to wait "<< world->GetTurnsWithAbility() << " turns to activate it again" << endl;
		}
		else {
			world->ActivateAbility(true);
			cout << "Human ability activated" << endl;
		}
		temp = _getch();
		choice = _getch();
	}
	else {
		choice = _getch();
	}

	world->SetCell(pos_x, pos_y, nullptr);

	switch (choice) {
	case UP_KEY:
		if (pos_y - 1 > 0) {
			pos_y = pos_y - 1;
			cout << this->GetName() << ": has moved UP" << endl;
		}
		else {
			cout << "You can't move in this direction, there is a wall!" << endl;
		}
		break;
	case DOWN_KEY:
		if (pos_y + 1 < world->GetSizeY() + 1) {
			pos_y = pos_y + 1;
			cout << this->GetName() << ": has moved DOWN" << endl;
		}
		else {
			cout << "You can't move in this direction, there is a wall!" << endl;
		}
		break;
	case RIGHT_KEY:
		if (pos_x + 1 < world->GetSizeX() + 1) {
			pos_x = pos_x + 1;
			cout << this->GetName() << ": has moved RIGHT" << endl;
		}
		else {
			cout << "You can't move in this direction, there is a wall!" << endl;
		}
		break;
	case LEFT_KEY:
		if (pos_x - 1 > 0) {
			pos_x = pos_x - 1;
			cout << this->GetName() << ": has moved LEFT" << endl;
		}
		else {
			cout << "You can't move in this direction, there is a wall!" << endl;
		}
		break;
	}

	if (world->GetCell(pos_x, pos_y) != nullptr) {
		world->GetCell(pos_x, pos_y)->Collision(this);
	}
	else {
		this->Draw();
	}
}

void Human::Collision(Organism* attacker)
{
	int* possibleX = new int[4];
	int* possibleY = new int[4];
	int numberOfPossibilities = 0;

	world->GenerateEmptyCells(possibleX, possibleY, &numberOfPossibilities, attacker->GetX(), attacker->GetY());

	if (world->IsAbilityActivated()) {
		attacker->Escape(numberOfPossibilities, possibleX, possibleY);
	}
	else {
		Animal::Collision(attacker);
	}
}
