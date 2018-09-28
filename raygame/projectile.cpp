#include "projectile.h"
#include "math.h"
#include "tank.h"
#include "structure.h"

void Projectile::instantiate(int preset)
{
	switch (preset)
	{
		//Player preset
	case 0:
		storagePoint = { 200, 200 };
		rectangle = { storagePoint.x, storagePoint.y, 10, 10 };
		angle = 0;
		speed = 0;
		active = false;
		color = RED;
		break;
		//Enemy preset
	case 1:
		storagePoint = { 200, 190 };
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

bool Projectile::detectCollision(Structure* Structures, int StructuresLength)
{
	for (int i = 0; i < StructuresLength; i++)
	{
		if ((CheckCollisionRecs(rectangle, Structures[i].rectangle)) ||
			((rectangle.x <= 0) || (rectangle.x >= 800) || (rectangle.y <= 0) ||
			(rectangle.y >= 450)))
		{
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

bool Projectile::detectCollision(Tank* tanks, int tanksLength)
{
	for (int i = 0; i < tanksLength; i++)
	{
		if ((CheckCollisionRecs(rectangle, tanks[i].rectangle) && tanks[i].active && i != parentID) ||
			((rectangle.x <= 0) || (rectangle.x >= 800) || (rectangle.y <= 0) ||
			(rectangle.y >= 450)))
		{
			active = false;
			speed = 0;
			rectangle.x = storagePoint.x;
			rectangle.y = storagePoint.y;
			angle = 0;
			tanks[i].takeDamage(1);
			return true;
		}
	}
	return false;
}

bool Projectile::detectCollision(Tank* tankPointer)
{
	if (CheckCollisionRecs(rectangle, tankPointer->rectangle))
	{
		active = false;
		speed = 0;
		rectangle.x = storagePoint.x;
		rectangle.y = storagePoint.y;
		angle = 0;

		tankPointer->takeDamage(1);
		return true;
	}
	return false;
}