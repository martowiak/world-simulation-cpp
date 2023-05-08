#include "Guarana.h"

Guarana::Guarana(int x, int y, World* world) : Plant("Guarana", 'O', 0, 0, x, y, world)
{
}

void Guarana::Collision(Organism* attacker)
{
	Plant::Collision(attacker);
	attacker->SetStrength(attacker->GetStrength() + 3);
	cout << attacker->GetName() << "'s strength is increased to " << attacker->GetStrength() << " by eating Guarana" << endl;
}
