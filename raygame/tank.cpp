#include "tank.h"
#include "Structure.h"
#include "projectile.h"

void Tank::move(Structure* buildings, int buildingsLength)
{
	Vector2 newPos = { rectangle.x, rectangle.y };
	if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) //Get arrowkey input
	{
		newPos.x += 2.5f;
	}
	if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) //Get arrowkey input
	{
		newPos.x -= 2.5f;
	}
	if (!detectCollision(newPos, buildings, buildingsLength))
	{
		rectangle.x = newPos.x;
	}

	newPos = { rectangle.x, rectangle.y };
	if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) //Get arrowkey input
	{
		newPos.y -= 2.5f;
	}
	if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)) //Get arrowkey input
	{
		newPos.y += 2.5f;
	}

	if (!detectCollision(newPos, buildings, buildingsLength))
	{
		rectangle.y = newPos.y;
	}

}

bool Tank::detectCollision(Vector2 newPos, Structure* buildings, int buildingsLength)
{
	for (int i = 0; i < buildingsLength; i++)
	{
		if (CheckCollisionRecs({ newPos.x, newPos.y, rectangle.width, rectangle.height }, buildings[i].rectangle))
		{
			return true;
		}
	}
	return false;
}

void Tank::fire(Projectile* shells, int shellArraySize, Vector2 barrelPosition2, float angle)
{
	int j = -1;
	for (int i = 0; i < shellArraySize; i++)
	{
		if (shells[i].active == false)
		{
			j = i;
			shells[i].active = true;
			break;
		}
	}
	shells[j].rectangle.x = { barrelPosition2.x }; //Move projectile to barrel
	shells[j].rectangle.y = { barrelPosition2.y }; //Move projectile to barrel
	shells[j].angle = angle;
	shells[j].speed = 6;
}