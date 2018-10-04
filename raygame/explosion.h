#include "raylib.h"

class Tank;

class Explosion
{
public:
	Vector2 position;
	float radius;
	bool active;
	Color color;
	int lifespan;
	int uuid[4];

public:
	void instantiate();
	void dealDamage(Tank* tanks, int tanksArrayLength);


protected:
	Vector2 storagePoint;
	
};
