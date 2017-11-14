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

struct Game {

	//char game[100];
};


void initGame(char game[], int worldSize, char playerChar, char floorChar);
void movePlayerLeft(char game[], int &playerPos);
void movePlayerRight(char game[], int &playerPos, int worldSize);
void fireRight(char game[], int playerPos, int &bulletPos, char bulletCharRight, int &bulletDirection, int worldSize);
void fireLeft(char game[], int playerPos, int &bulletPos, char bulletCharLeft, int &bulletDirection);
void moveBullet(char game[], int &bulletPos, int &bulletDirection, int worldSize);
void generateMonster(char game[], int direction, int worldSize, list<Monster*> &listMonsters, int &monsterAmount);
void moveMonsters(char game[], list<Monster*> &listMonsters, int worldSize, int &monsterAmount);



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
	std:list<Monster*> listMonsters;
	

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
				fireLeft(game, playerPos, bulletPos, bulletCharLeft, bulletDirection);
			if (key == KEY_FIRE_RIGHT)
				fireRight(game, playerPos, bulletPos, bulletCharRight, bulletDirection, worldSize);
			
		}
		// Update.
		if (monsterAmount < 3) {

			int direction = rand() % 2;
			generateMonster(game, direction, worldSize, listMonsters, monsterAmount);
			
		}
		if (bulletPos != -1) {
			moveBullet(game, bulletPos, bulletDirection, worldSize);
		}
		moveMonsters(game, listMonsters, worldSize, monsterAmount);
		
		
		// Print.
		if (strcmp(gamePrev, game) != 0) {
			system("cls");
			cout << endl << endl << endl << endl;
			printf("		%s  ", game);
			printf("LIVES: %4d   SCORE: %5d", lives, score);
		}
		// Set cursor to start position.
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

void fireLeft(char game[], int playerPos, int &bulletPos, char bulletCharLeft, int &bulletDirection) {
	if ((bulletPos == -1) && (playerPos > 0)) {
		bulletDirection = 0;
		bulletPos = playerPos - 1;
		game[bulletPos] = bulletCharLeft;
	}
}

void fireRight(char game[], int playerPos, int &bulletPos, char bulletCharRight, int &bulletDirection, int worldSize) {
	if ((bulletPos == -1) && (playerPos < worldSize -1)) {
		bulletDirection = 1;
		bulletPos = playerPos + 1;
		game[bulletPos] = bulletCharRight;
	}
}

void moveBullet(char game[], int &bulletPos, int &bulletDirection, int worldSize) {
	
	int nextPos;
	if (!bulletDirection)
		nextPos = bulletPos - 1;
	else
		nextPos = bulletPos + 1;

	if ((nextPos >= 0) && (nextPos <= worldSize - 1)) {
		char replace = game[nextPos];
		game[nextPos] = game[bulletPos];
		game[bulletPos] = replace;
		bulletPos = nextPos;
	}
	else {
		if (nextPos < 0)
			game[bulletPos] = game[bulletPos + 1];
		else
			game[bulletPos] = game[bulletPos - 1];
		bulletPos = -1;
	}
}

void generateMonster(char game[], int direction, int worldSize, list<Monster*> &listMonsters, int &monsterAmount) {
	
	Monster* monster = new Monster;
	monster->direction = direction;
	if (direction) {
		monster->pos = worldSize-1;
	}
	else {
		monster->pos = 0;
	}
	game[monster->pos] = monster->graphic;
	listMonsters.push_back(monster);
	monsterAmount++;
	
}

void moveMonsters(char game[], list<Monster*> &listMonsters, int worldSize, int &monsterAmount) {
	int nextPos;

	for (auto mon = listMonsters.begin(); mon != listMonsters.end();)
	{
		if ((*mon)->direction) 
			nextPos = (*mon)->pos - 1;
		else
			nextPos = (*mon)->pos + 1;

		if ((nextPos >= 0) && (nextPos <= worldSize - 1)) {
			
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