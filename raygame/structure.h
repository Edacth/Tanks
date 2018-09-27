#pragma once

#include "raylib.h"

class Structure
{
public:
	Rectangle rectangle;
	Color color;

	void instantiate(Vector2 position, Vector2 size);
};