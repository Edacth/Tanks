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

public:
	void instantiate();
	void dealDamage(Tank* tanks, int tanksArrayLength);


protected:
	Vector2 storagePoint;
	
};
