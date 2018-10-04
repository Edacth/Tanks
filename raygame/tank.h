#pragma once
#include "raylib.h"

class Structure;
class Projectile;

class Tank
{
public:

	Rectangle rectangle;
	int health;
	float speed;
	Color color;
	Vector2 barrelPosition1;
	Vector2 barrelPosition2;
	float angle;
	bool active;
	int damageHistory[10][4];

	void instantiate(Vector2 position, int preset);
	void move(Structure* buildings, int buildingsLength);
	bool detectCollision(Vector2 newPos, Structure* buildings, int buildingsLength);
	void fire(Projectile* shells, int shellArraySize, int parentID);
	void takeDamage(int damage);
	void positionBarrel(Vector2 target);

protected:
};

