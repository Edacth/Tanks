#include "explosion.h"
#include "tank.h"

void Explosion::instantiate()
{

	storagePoint = { -200, -200 };
	position = { storagePoint.x, storagePoint.y };
	radius = 10;
	active = false;
	color = RED;
	//char* uuid = new char[4];
	



}

void Explosion::dealDamage(Tank* tanks, int tanksArrayLength)
{
	if (active)
	{
		lifespan--;
		radius--;
	}
	for (int i = 0; i < tanksArrayLength; i++)
	{
		if (CheckCollisionCircleRec(position, radius, tanks[i].rectangle))
		{
			
		}
	}


	if (lifespan <= 0)
	{
		position.x = storagePoint.x;
		position.y = storagePoint.y;
		active = false;
	}
}