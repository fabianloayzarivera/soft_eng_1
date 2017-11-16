#pragma once
#include "windows.h"
#include "monster.h"
#include "player.h"

#define KEY_ESCAPE 27
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_FIRE_LEFT 122
#define KEY_FIRE_RIGHT 99

void initGame(Player player);
void moveBullet(list<Bullet*> &listBullets, list<Monster*> &listMonsters);
bool checkHit(int nextPos, int actualPos, list<Monster*> &listMonsters);
void generateMonster(int direction, list<Monster*> &listMonsters);
void moveMonsters(list<Monster*> &listMonsters, Player &player);
void rain(int &rainPrev);