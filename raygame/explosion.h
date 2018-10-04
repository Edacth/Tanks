#include "raylib.h"

class Explosion
{
public:
	Vector2 position;
	float radius;
	bool active;
	Color color;
	int lifespan;

public:
	void instantiate();
	void dealDamage();


protected:
	Vector2 storagePoint;
	
};
