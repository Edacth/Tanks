#include "projectile.h"
#include "math.h"
#include "tank.h"
#include "structure.h"
#include "explosion.h"
#include <cmath>
#include <iostream>
#include <string>
void srand(int seed);

void Projectile::instantiate(int preset)
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
		break;
		//Enemy preset
	case 1:
		storagePoint = { -200, -190 };
		rectangle = { storagePoint.x, storagePoint.y, 10, 10 };
		angle = 0;
		speed = 0;
		active = false;
		color = BLACK;
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

bool Projectile::detectCollision(Structure* Structures, int structuresLength, Explosion* explosions, int explosionArraySize)
{
	for (int i = 0; i < structuresLength; i++)
	{
		if ( ( (CheckCollisionRecs(rectangle, Structures[i].rectangle)) ||
			((rectangle.x <= 0) || (rectangle.x >= 800) || (rectangle.y <= 0) ||
			(rectangle.y >= 450)) ) && active)
		{

			int chosen = -1;
			for (int j = 0; j < explosionArraySize; j++)
			{
				if (explosions[j].active == false)
				{
					chosen = j;
					break;
				}
			}
			explosions[chosen].position.x = rectangle.x;
			explosions[chosen].position.y = rectangle.y;
			explosions[chosen].lifespan = 60;
			explosions[chosen].radius = 60;
			explosions[chosen].active = true;
			for (int k = 0; k < 4; k++)
			{
				explosions[chosen].uuid = ( std::to_string(rand() % 10) + std::to_string(rand() % 10) + std::to_string(rand() % 10) + std::to_string(rand() % 10) );
			}

			std::cout << explosions[chosen].uuid << std::endl;
			active = false;
			speed = 0;
			rectangle.x = storagePoint.x;
			rectangle.y = storagePoint.y;
			angle = 0;

			return true;
		}
	}
	return false;
}

bool Projectile::detectCollision(Tank* tanks, int tanksArraySize, Explosion* explosions, int explosionArraySize)
{
	for (int i = 0; i < tanksArraySize; i++)
	{
		if (((CheckCollisionRecs(rectangle, tanks[i].rectangle)) ||
			((rectangle.x <= 0) || (rectangle.x >= 800) || (rectangle.y <= 0) ||
			(rectangle.y >= 450))) && active)
		{

			int chosen = -1;
			for (int j = 0; j < explosionArraySize; j++)
			{
				if (explosions[j].active == false)
				{
					chosen = j;
					break;
				}
			}
			explosions[chosen].position.x = rectangle.x;
			explosions[chosen].position.y = rectangle.y;
			explosions[chosen].lifespan = 60;
			explosions[chosen].radius = 60;
			explosions[chosen].active = true;
			for (int k = 0; k < 4; k++)
			{
				explosions[chosen].uuid = (std::to_string(rand() % 10) + std::to_string(rand() % 10) + std::to_string(rand() % 10) + std::to_string(rand() % 10));
			}

			std::cout << explosions[chosen].uuid << std::endl;
			active = false;
			speed = 0;
			rectangle.x = storagePoint.x;
			rectangle.y = storagePoint.y;
			angle = 0;

			return true;
		}
	}
	return false;
}

bool Projectile::detectCollision(Tank* tankPointer, Explosion* explosions, int explosionArraySize)
{
	if (CheckCollisionRecs(rectangle, tankPointer->rectangle) && active)
	{

		int chosen = -1;
		for (int j = 0; j < explosionArraySize; j++)
		{
			if (explosions[j].active == false)
			{
				chosen = j;
				break;
			}
		}
		explosions[chosen].position.x = rectangle.x;
		explosions[chosen].position.y = rectangle.y;
		explosions[chosen].lifespan = 60;
		explosions[chosen].radius = 60;
		explosions[chosen].active = true;
		for (int k = 0; k < 4; k++) //Generate uuid
		{
			explosions[chosen].uuid = (std::to_string(rand() % 10) + std::to_string(rand() % 10) + std::to_string(rand() % 10) + std::to_string(rand() % 10));
		}

		std::cout << explosions[chosen].uuid << std::endl;
		active = false;
		speed = 0;
		rectangle.x = storagePoint.x;
		rectangle.y = storagePoint.y;
		angle = 0;

		return true;
	}
	return false;
}