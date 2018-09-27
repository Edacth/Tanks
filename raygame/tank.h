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

	void move(Structure* buildings, int buildingsLength);
	bool detectCollision(Vector2 newPos, Structure* buildings, int buildingsLength);
	bool detectCollision(Projectile* shells, int shellsLength);
	void fire(Projectile* shells, int shellArraySize, Vector2 barrelPosition2, float angle);
	void takeDamage(int damage);
};