#pragma once
#include <conio.h>
#include <list>
#include <iostream>
#include "bullet.h"
#include "game.h"
#include "mushroom.h"
using namespace std;

class Player {
public:
	int pos;
	char graphic;

	Player(int p, char g);
	void fireRight(list<Bullet*> &listBullets);
	void fireLeft(list<Bullet*> &listBullets);
	void movePlayerLeft(Mushroom &mushroom);
	void movePlayerRight(Mushroom &mushroom);
};