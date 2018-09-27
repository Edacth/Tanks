#include <iostream>
#include "tank.h"
#include "Structure.h"

void Structure::instantiate(Vector2 position, Vector2 size)
{
	
		rectangle = { position.x, position.y, size.x, size.y };
		color = PURPLE;

}