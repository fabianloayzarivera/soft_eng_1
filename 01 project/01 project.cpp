// 01 project.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "windows.h"
#include <conio.h>
#include <list>
#include <iostream>
using namespace std;


#define KEY_ESCAPE 27
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_FIRE_LEFT 122
#define KEY_FIRE_RIGHT 99

struct Monster {
	int pos;
	int direction;
	char graphic = '8';
};

struct Bullet {
	int pos;
	int direction;
	char graphicLeft  = '<';
	char graphicRight = '>';
};

struct Game {

	//char game[100];
	int score = 0;
	int lives = 5;

};


void initGame(char game[], int worldSize, char playerChar, char floorChar);
void movePlayerLeft(char game[], int &playerPos);
void movePlayerRight(char game[], int &playerPos, int worldSize);
void fireRight(char game[], int playerPos, list<Bullet*> &listBullets, int &bulletAmount, int worldSize);
void fireLeft(char game[], int playerPos, list<Bullet*> &listBullets, int &bulletAmount);
void moveBullet(char game[], list<Bullet*> &listBullets, list<Monster*> &listMonsters, int &bulletAmount, int worldSize, int &monsterAmount, Game &gameObject);
void generateMonster(char game[], int direction, int worldSize, list<Monster*> &listMonsters, int &monsterAmount);
void moveMonsters(char game[], list<Monster*> &listMonsters, int worldSize, int &monsterAmount, int &playerPos, char playerChar, Game &gameObject);
bool checkHit(int nextPos, int actualPos, list<Monster*> &listMonsters, int &monsterAmount);


int main() {

	

	int key				= 0;
	int worldSize		= 75;
	char game[100]		= "";
	char playerChar		= '|';
	int playerPos		= worldSize / 2;
	char floorChar		= '_';
	char bulletCharLeft = '<';
	char bulletCharRight= '>';
	char gamePrev[100]	= "";
	int facing			= 1;
	bool bulletShot		= false;
	int bulletPos		= -1;
	int bulletDirection = 0;
	int lives			= 5;
	int score			= 0;
	char monsterChar	= '8';
	int monsterPos		= -1;
	int maxMonsters		= 3;
	int monsterAmount	= 0;
	int bulletAmount	= 0;
	Game gameObject;
	list<Monster*> listMonsters;
	list<Bullet*>  listBullets;
	

	initGame(game, worldSize, playerChar, floorChar);
	cout << endl << endl << endl << endl;
	printf("		%s  ", game);
	printf("LIVES: %4d   SCORE: %5d", lives, score);
	while (key != KEY_ESCAPE) {
		// Get input.
		strcpy(gamePrev, game);

		if (_kbhit()) {
			key = _getch();	
			//cout << key;
			if (key == KEY_LEFT)
				movePlayerLeft(game, playerPos);
			if (key == KEY_RIGHT)
				movePlayerRight(game, playerPos, worldSize);			
			if (key == KEY_FIRE_LEFT)
				fireLeft(game, playerPos,listBullets, bulletAmount);
			if (key == KEY_FIRE_RIGHT)
				fireRight(game, playerPos, listBullets, bulletAmount, worldSize);
			
		}
		// Update.
		if (monsterAmount < 3) {

			int direction = rand() % 2;
			generateMonster(game, direction, worldSize, listMonsters, monsterAmount);
			
		}
		
		moveBullet(game, listBullets, listMonsters,  bulletAmount, worldSize, monsterAmount, gameObject);
		moveMonsters(game, listMonsters, worldSize, monsterAmount, playerPos, playerChar,gameObject);
		
		
		// Print.
		if (gameObject.lives > 0) {
			if (strcmp(gamePrev, game) != 0) {
				system("cls");
				cout << endl << endl << endl << endl;
				printf("		%s  ", game);
				printf("LIVES: %4d   SCORE: %5d", gameObject.lives, gameObject.score);
			}
		}
		else {
			cout << "			GAME OVER !     " << endl;
			getchar();
		}

		Sleep(5);
	}

	cout << "EXIT";
}

void initGame(char game[], int worldSize, char playerChar, char floorChar) {
	int i;
	for (i = 0; i < worldSize; i++) {
		game[i] = floorChar;
		if (i == worldSize / 2) {
			game[i] = playerChar;
		}
	}
	//game[i] = '\0';
	
}

void movePlayerLeft(char game[], int &playerPos) {
	
	if (playerPos > 0) {
		char replace = game[playerPos - 1];
		game[playerPos - 1] = game[playerPos];
		game[playerPos] = replace;
		playerPos--;
	
	}
}

void movePlayerRight(char game[], int &playerPos, int worldSize) {

	if (playerPos < worldSize -1) {
		char replace = game[playerPos + 1];
		game[playerPos + 1] = game[playerPos];
		game[playerPos] = replace;
		playerPos++;
		
	}
}

void fireLeft(char game[], int playerPos, list<Bullet*> &listBullets, int &bulletAmount) {
	if (playerPos > 0) {
		Bullet* bullet = new Bullet;
		bullet->direction = 0;
		bullet->pos = playerPos - 1;
		game[bullet->pos] = bullet->graphicLeft;
		listBullets.push_back(bullet);
		bulletAmount++;
	}
}

void fireRight(char game[], int playerPos, list<Bullet*> &listBullets, int &bulletAmount, int worldSize) {
	if (playerPos < worldSize -1) {
		Bullet* bullet = new Bullet;
		bullet->direction = 1;
		bullet->pos = playerPos + 1;
		game[bullet->pos] = bullet->graphicRight;
		listBullets.push_back(bullet);
		bulletAmount++;
	}
}

void generateMonster(char game[], int direction, int worldSize, list<Monster*> &listMonsters, int &monsterAmount) {
	
	Monster* monster = new Monster;
	monster->direction = direction;
	if (!direction) {
		monster->pos = worldSize-1;
	}
	else {
		monster->pos = 0;
	}
	game[monster->pos] = monster->graphic;
	listMonsters.push_back(monster);
	monsterAmount++;
	
}

void moveMonsters(char game[], list<Monster*> &listMonsters, int worldSize, int &monsterAmount, int &playerPos, char playerChar, Game &gameObject) {
	int nextPos;

	for (auto mon = listMonsters.begin(); mon != listMonsters.end();)
	{
		if (!(*mon)->direction) 
			nextPos = (*mon)->pos - 1;
		else
			nextPos = (*mon)->pos + 1;

		if ((nextPos >= 0) && (nextPos <= worldSize - 1)) {
			
			if ((nextPos == playerPos) || ((*mon)->pos == playerPos)) {
				//Player Dead
				gameObject.lives--;
				playerPos = worldSize / 2;
				game[playerPos] = playerChar;
			}
				
			game[nextPos] = (*mon)->graphic;
			game[(*mon)->pos] = '_';
			(*mon)->pos = nextPos;
			mon++;
		}
		else {
			if (nextPos < 0)
				game[(*mon)->pos] = '_';
			else
				game[(*mon)->pos] = '_';
			
			mon = listMonsters.erase(mon);
			monsterAmount--;
		}
		

	}
}

void moveBullet(char game[], list<Bullet*> &listBullets, list<Monster*> &listMonsters, int &bulletAmount, int worldSize, int &monsterAmount, Game &gameObject) {

	int nextPos;
	char graph;

	for (auto bull = listBullets.begin(); bull != listBullets.end();)
	{
		if (!(*bull)->direction) {
			nextPos = (*bull)->pos - 1;
			graph = (*bull)->graphicLeft;

		}			
		else {
			nextPos = (*bull)->pos + 1;
			graph = (*bull)->graphicRight;
		}

		if ((nextPos >= 0) && (nextPos <= worldSize - 1)) {

			if (checkHit(nextPos, (*bull)->pos, listMonsters, monsterAmount)) {
				//hit monster
				gameObject.score++;
				game[nextPos] = '_';
				game[(*bull)->pos] = '_';
				bull = listBullets.erase(bull);
			}
			else {
				game[nextPos] = graph;
				game[(*bull)->pos] = '_';
				(*bull)->pos = nextPos;
				bull++;
			}
		}
		else {
			
			game[(*bull)->pos] = '_';
			bull = listBullets.erase(bull);
			bulletAmount--;
		}
			

	}	

	
}

bool checkHit(int nextPos, int actualPos, list<Monster*> &listMonsters, int &monsterAmount) {
	bool hit = false;

	for (auto mon = listMonsters.begin(); mon != listMonsters.end();)
	{
		if (((*mon)->pos == nextPos) || ((*mon)->pos == actualPos)) {
			//EnemyHit
			hit = true;
			mon = listMonsters.erase(mon);
			monsterAmount--;
		}
		else {
			mon++;
		}

	}
	return hit;
}

bool checkPlayerDead(int nextPos, int actualPos, int playerPos) {
	if ((nextPos == playerPos) || (actualPos == playerPos))
		return true;
	else
		return false;
}