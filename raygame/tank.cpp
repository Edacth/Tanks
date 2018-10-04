#include <iostream>
#include "tank.h"
#include "Structure.h"
#include "projectile.h"

void Tank::instantiate(Vector2 position, int preset)
{
	switch (preset)
	{
	//Player preset
	case 0:
		rectangle = { position.x, position.y, 20, 20 };
		health = 3;
		speed = 2.5f;
		color = MAROON;
		barrelPosition1 = { 0, 0 };
		barrelPosition2 = { 0, 0 };
		angle = 0.0f;
		break;
	//Enemy preset
	case 1:
		rectangle = { position.x, position.y, 20, 20 };
		health = 3;
		speed = 2.5f;
		color = BLACK;
		barrelPosition1 = { 0, 0 };
		barrelPosition2 = { 0, 0 };
		angle = 90.0f;
		break;
	default:
		break;
	}

	active = true;
}

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

void Tank::fire(Projectile* shells, int shellArraySize, int pID)
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
	shells[j].parentID = pID;
}

void Tank::takeDamage(int damage)
{
	health = health - damage;
	//std::cout << health << std::endl;
	if (health <= 0)
	{
		active = false;
	}
}

void Tank::positionBarrel(Vector2 target)
{
	float slope = 0;
	float rise = 0;
	float run = 0;

	//Trig Calculations
	rise = (target.y - (rectangle.y + (rectangle.height / 2.0f)));
	run = (target.x - (rectangle.x + (rectangle.width / 2.0f)));
	slope = (rise / run); //Calculate the slope
	angle = (atan2(rise, run));

	barrelPosition1 = { (rectangle.x + (rectangle.width / 2.0f)) + 10 * cos(angle),
		(rectangle.y + (rectangle.height / 2.0f)) + 10 * sin(angle) };
	barrelPosition2 = { (rectangle.x + (rectangle.width / 2.0f)) + 20 * cos(angle),
		(rectangle.y + (rectangle.height / 2.0f)) + 20 * sin(angle) };
}