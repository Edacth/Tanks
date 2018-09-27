#include "projectile.h"
#include "math.h"
#include "tank.h"
#include "structure.h"

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
			rectangle.x = 200;
			rectangle.y = 200;
			angle = 0;
			return true;
		}
	}

	/*if (CheckCollisionRecs(tank.rectangle, rectangle))
	{
	active = false;
	speed = 0;
	rectangle.x = 200;
	rectangle.y = 200;
	angle = 0;
	return true;
	}*/

	return false;
}

bool Projectile::detectCollision(Tank* tanks, int tanksLength)
{
	for (int i = 0; i < tanksLength; i++)
	{
		if ((CheckCollisionRecs(rectangle, tanks[i].rectangle)) ||
			((rectangle.x <= 0) || (rectangle.x >= 800) || (rectangle.y <= 0) ||
			(rectangle.y >= 450)))
		{
			active = false;
			speed = 0;
			rectangle.x = 200;
			rectangle.y = 200;
			angle = 0;
			return true;
		}
	}

	return false;
}

bool Projectile::detectCollision(Tank tank)
{
	return false;
}