#include "Belladonna.h"

Belladonna::Belladonna(int x, int y, World* world) : Plant("Belladonna", 'o', 0, 0, x, y, world)
{
}

void Belladonna::Collision(Organism* attacker)
{
	cout << this->GetName() << ": was eaten by " << attacker->GetName() << endl;
	cout << attacker->GetName() << ": was killed by eating " << this->GetName() << endl;
	world->SetCell(attacker->GetX(), attacker->GetY(), nullptr);
	world->DeleteOrganism(attacker);
	world->DeleteOrganism(this);
}
