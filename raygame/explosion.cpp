#include "explosion.h"

void Explosion::instantiate()
{

		storagePoint = { 200, 150 };
		position = {storagePoint.x, storagePoint.y};
		radius = 10;
		active = false;
		color = RED;


}

void Explosion::dealDamage()
{
	if (active)
	{
		lifespan--;
		radius--;
	}




	if (lifespan <= 0)
	{
		position.x = storagePoint.x;
		position.y = storagePoint.y;
		active = false;
	}
	//explosions[0].rectangle = { explosions[0].storagePoint.x }
}