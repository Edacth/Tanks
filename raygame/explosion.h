#include "raylib.h"
#include <string>

class Tank;

class Explosion
{
public:
	Vector2 position;
	float radius;
	bool active;
	Color color;
	int lifespan;
	std::string uuid;
	std::string blacklist[10];

public:
	void instantiate();
	void dealDamage(Tank* tanks, int tanksArrayLength, Tank* playerTank);
	void addToBlacklist(std::string);
	bool checkBlacklist(std::string);
	void printBlacklist();


protected:
	int BLACKLIST_LENGTH = 10;

	Vector2 storagePoint;
	

};
