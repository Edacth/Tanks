#include "projectile.h"
#include "math.h"
#include "tank.h"
#include "structure.h"
#include "explosion.h"
#include <cmath>
#include <iostream>
#include <string>
void srand(int seed);

void Projectile::instantiate(int preset, Explosion exPointer, int exArrayLength, Projectile shPointer, int shArrayLength)
{
	switch (preset)
	{
		//Player preset
	case 0:
		storagePoint = { -200, -200 };
		rectangle = { storagePoint.x, storagePoint.y, 10, 10 };
		angle = 0;
		speed = 0;
		active = false;
		color = RED;
		explosionsPointer = &exPointer;
		explosionArrayLength = exArrayLength;
		shellsPointer = &shPointer;
		shellsArrayLength = shArrayLength;
		break;
		//Enemy preset
	case 1:
		storagePoint = { -200, -190 };
		rectangle = { storagePoint.x, storagePoint.y, 10, 10 };
		angle = 0;
		speed = 0;
		active = false;
		color = BLACK;
		explosionsPointer = &exPointer;
		explosionArrayLength = exArrayLength;
		shellsPointer = &shPointer;
		shellsArrayLength = shArrayLength;
		break;
	default:
		break;
	}
}

void Projectile::forward()
{
	rectangle.x += speed * cos(angle);
	rectangle.y += speed * sin(angle);
	
}

bool Projectile::detectCollision(Structure* Structures, int structuresLength)
{
	for (int i = 0; i < structuresLength; i++)
	{
		if ( ( (CheckCollisionRecs(rectangle, Structures[i].rectangle)) ||
			((rectangle.x <= 0) || (rectangle.x >= 800) || (rectangle.y <= 0) ||
			(rectangle.y >= 450)) ) && active)
		{

			triggerExplosion();

			return true;
		}
	}
	return false;
}

bool Projectile::detectCollision(Tank* tanks, int tanksArraySize)
{
	for (int i = 0; i < tanksArraySize; i++)
	{
		if ((CheckCollisionRecs(rectangle, tanks[i].rectangle)) && active
			&& tanks[i].uuid != parentID)
		{

			triggerExplosion();

			return true;
		}
	}
	return false;
}

bool Projectile::detectCollision(Tank* tankPointer)
{
	if (CheckCollisionRecs(rectangle, tankPointer->rectangle) && active)
	{

		triggerExplosion();

		return true;
	}
	return false;
}

bool Projectile::detectCollision(Projectile* projectiles, int projectileArraySize)
{
	for (int i = 0; i < projectileArraySize; i++)
	{
		if ((CheckCollisionRecs(rectangle, projectiles[i].rectangle)) 
			&& active /*&& uuid != projectiles[i].uuid*/)
		{
			triggerExplosion();

			return true;
		}
	}
	return false;
}



void Projectile::triggerExplosion()
{
	int chosen = -1;
	for (int j = 0; j < explosionArrayLength; j++)
	{
		if (explosionsPointer[j].active == false)
		{
			chosen = j;
			break;
		}
	}
	explosionsPointer[chosen].position.x = rectangle.x;
	explosionsPointer[chosen].position.y = rectangle.y;
	explosionsPointer[chosen].lifespan = 60;
	explosionsPointer[chosen].radius = 60;
	explosionsPointer[chosen].active = true;
	explosionsPointer[chosen].uuid = ("e" + std::to_string(rand() % 10) + std::to_string(rand() % 10) + std::to_string(rand() % 10) + std::to_string(rand() % 10));


	active = false;
	speed = 0;
	rectangle.x = storagePoint.x;
	rectangle.y = storagePoint.y;
	angle = 0;
}