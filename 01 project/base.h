#pragma once
#include "windows.h"
#include <conio.h>
#include <list>
#include <iostream>
#include "monster.h"
#include "game.h"
#include "bullet.h"
#include "mushroom.h"
#include "player.h"
using namespace std;


#define KEY_ESCAPE 27
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_FIRE_LEFT 122
#define KEY_FIRE_RIGHT 99

void moveBullet(list<Bullet*> &listBullets, list<Monster*> &listMonsters);
void generateMonster(int direction, list<Monster*> &listMonsters);
void moveMonsters(list<Monster*> &listMonsters, Player &player);
bool checkHit(int nextPos, int actualPos, list<Monster*> &listMonsters);