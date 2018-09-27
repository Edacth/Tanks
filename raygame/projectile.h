#pragma once
#include "raylib.h"

class Tank;
class Structure;

class Projectile
{
public:

	Rectangle rectangle;
	float angle;
	float speed;
	bool active;
	Color color;

	void instantiate(int preset);
	void forward();
	bool detectCollision(Structure* Structures, int StructuresLength);
	bool detectCollision(Tank* tanks, int tanksLength);
	bool detectCollision(Tank* tank);

protected:
	Vector2 storagePoint;
};