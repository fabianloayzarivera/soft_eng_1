#include "stdafx.h"
#include "mushroom.h"

int Mushroom::mushroomAmount = 0;

void Mushroom::generateMushroom(int randPos) {
	pos = randPos;
	Game::world[pos] = graphic;
}

void Mushroom::paintMushroom() {
	Game::world[pos] = graphic;
}
