#pragma once
#include "raylib.h"
#include <string>

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
	std::string parentID;
	std::string uuid;

	void instantiate(int preset, Explosion exPointer, int exArrayLength, Projectile shPointer, int shArrayLength);
	void forward();
	bool detectCollision(Structure* Structures, int structuresLength);
	bool detectCollision(Tank* tanks, int tanksLength);
	bool detectCollision(Tank* tank);
	bool detectCollision(Projectile* projectiles, int projectileArraySize);
	void triggerExplosion();

protected:
	Vector2 storagePoint;
	Explosion* explosionsPointer;
	int explosionArrayLength;
	Projectile* shellsPointer;
	int shellsArrayLength;
};