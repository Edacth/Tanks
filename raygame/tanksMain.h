#pragma once
#include "raylib.h"
class Projectile;
class Structure;
class Tank;
class Explosion;

//General funtions
int tanksMain();
void moveShells(Projectile* shells, int size);
void drawShells(Projectile* shells, int size);
void drawBuildings(Structure* buildings, int length);
void drawTanks(Tank tank);
void drawTanks(Tank* tanks, int length);
void drawExplosions(Explosion* explosions, int explosionsArraySize);
