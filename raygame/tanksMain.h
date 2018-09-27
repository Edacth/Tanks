#pragma once
#include "raylib.h"
class Projectile;
class Structure;

//General funtions

int tanksMain();
void moveShells(Projectile* shells, int size);
void drawShells(Projectile* shells, int size);
void drawBuildings(Structure* buildings, int length);


