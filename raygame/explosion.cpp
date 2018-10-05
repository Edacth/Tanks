#include "explosion.h"
#include "tank.h"
#include "projectile.h"
#include <iostream>
#include <string>

void Explosion::instantiate(Explosion* exPointer, int exArrayLength, Projectile* shPointer, int shArrayLength)
{

	storagePoint = { -200, -200 };
	position = { storagePoint.x, storagePoint.y };
	radius = 10;
	active = false;
	color = RED;
	
	for (int i = 0; i < BLACKLIST_LENGTH - 1; i++)
	{
		blacklist[i] = "";
	}

	explosionsPointer = exPointer;
	explosionArrayLength = exArrayLength;
	shellsPointer = shPointer;
	shellsArrayLength = shArrayLength;
}

void Explosion::dealDamage(Tank* tanks, int tanksArrayLength, Tank* playerTank)
{
	if (active)
	{
		lifespan--;
		radius--;
	}
	for (int i = 0; i < tanksArrayLength; i++)
	{
		if (CheckCollisionCircleRec(position, radius, tanks[i].rectangle) && !checkBlacklist(tanks[i].uuid))
		{
			tanks[i].takeDamage(1);
			addToBlacklist(tanks[i].uuid);
			printBlacklist();
		}
	}
	if (CheckCollisionCircleRec(position, radius, playerTank->rectangle) && !checkBlacklist(playerTank->uuid))
	{
		playerTank->takeDamage(1);
		addToBlacklist(playerTank->uuid);
	}
	for (int i = 0; i < shellsArrayLength; i++)
	{
		if (CheckCollisionCircleRec(position, radius, shellsPointer[i].rectangle))
		{
			shellsPointer[i].triggerExplosion();

		}
	}

	if (lifespan <= 0)
	{
		position.x = storagePoint.x;
		position.y = storagePoint.y;
		active = false;
		for (int i = 0; i < BLACKLIST_LENGTH - 1; i++)
		{
			blacklist[i] = "";
		}
	}
}

void Explosion::addToBlacklist(std::string uuid)
{
	for (int i = BLACKLIST_LENGTH - 1; i > 0; i--)
	{
		blacklist[i] = blacklist[i - 1];

	}
	blacklist[0] = uuid;

}

bool Explosion::checkBlacklist(std::string uuid)
{
	for (int i = 0; i < blacklist->length(); i++)
	{
		if (blacklist[i] == uuid)
		{
			return true;
		}
	}
	return false;
}

void Explosion::printBlacklist()
{
	std::cout << "Blacklist:" << std::endl;
	for (int i = 0; i < BLACKLIST_LENGTH - 1; i++)
	{
		std::cout << blacklist[i] << " ";
	}
	std::cout << std::endl;
}