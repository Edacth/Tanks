#pragma once
#include "raylib.h"

class Tank;
class Structure;
class Explosion;

class Projectile
{
public:

	Rectangle rectangle;
	float angle;
	float speed;
	bool active;
	Color color;
	int parentID;

	void instantiate(int preset);
	void forward();
	bool detectCollision(Structure* Structures, int structuresLength, Explosion* explosions, int explosionsLength);
	bool detectCollision(Tank* tanks, int tanksLength, Explosion* explosions, int explosionArraySize);
	bool detectCollision(Tank* tank, Explosion* explosions, int explosionArraySize);

protected:
	Vector2 storagePoint;
};