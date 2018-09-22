#pragma once
#include "raylib.h"
class Tank;
class Projectile;

class Structure
{
public:
	Rectangle rectangle;
	Color color;
};

class Projectile
{
public:

	Rectangle rectangle;
	float angle;
	float speed;
	bool active;
	Color color;

	void forward();
	bool detectCollision(Structure* buildings, int buildingsLength, Tank tank, Tank* enemyForce, int enemyForceLength);
};

class Tank
{
public:
	
	Rectangle rectangle;
	int health;
	float speed;
	Color color;

	void move(Structure* buildings, int buildingsLength);
	bool detectCollision(Vector2 newPos, Structure* buildings, int buildingsLength);
	bool detectCollision(Projectile* shells, int shellsLength);
	void fire(Projectile* shells, int shellArraySize, Vector2 barrelPosition2, float angle);
};



int tanks();
void simulateShells(Projectile* shells, int size);
void drawShells(Projectile* shells, int size);
void drawBuildings(Structure* buildings, int length);


