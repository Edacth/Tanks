//This is the main file of Tanks!


#include <string>
#include <math.h> 
#include <iostream>
#include "raylib.h"
#include "tank.h"
#include "tanksMain.h"
#include "projectile.h"
#include "Structure.h"
#include "explosion.h"


int tanksMain()
{
	// Initialization
	//--------------------------------------------------------------------------------------
	Tank tank;
	Tank* tankPointer;
	tankPointer = &tank;
	Tank enemyForce[3];
	Projectile shells[10];
	Projectile enemyShells[10];
	Explosion explosions[10];
	Structure buildings[3];
	int shellArraySize = 10;
	int explosionsArraySize = 10;
	int buildingArraySize = 3;
	int enemyForceSize = 3;
	Vector2 mousePos; // Mouse position
	bool isFirstTick = true;
	int framesCounter = 0;

	for (int i = 0; i < shellArraySize; i++) //Instantiate projectiles
	{
		shells[i].instantiate(0);
		enemyShells[i].instantiate(1);
		explosions[i].instantiate();
	}

	tank.instantiate({ 400, 225 }, 0); //Instantiate the player
	enemyForce[0].instantiate({ 300, 300 }, 1); //Instantiate enemies
	enemyForce[1].instantiate({ 300, 260 }, 1); //Instantiate enemies
	enemyForce[2].instantiate({ 100, 160 }, 1); //Instantiate enemies
	

	buildings[0].instantiate({ 500, 100 }, { 60, 30 });
	buildings[1].instantiate({ 500, 200 }, { 60, 30 });
	buildings[2].instantiate({ 2, 350 }, { 200, 30 });
	//--------------------------------------------------------------------------------------


	while (!WindowShouldClose()) // Main game loop
	{
		// Update
		//----------------------------------------------------------------------------------
		framesCounter++; //Counts frames
		mousePos = GetMousePosition(); //Get mouse position

		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && isFirstTick == false) //Get left mouse input
		{
			tank.fire(shells, shellArraySize); //Fire a projectile
		}
		isFirstTick = false;

		tank.move(buildings, buildingArraySize); //Handle the tank's movement
		for (int i = 0; i < enemyForceSize; i++)
		{
			enemyForce[i].positionBarrel({ tank.rectangle.x, tank.rectangle.y });
		}
		tank.positionBarrel(GetMousePosition()); //Handle the barrel's position

		moveShells(shells, shellArraySize); //Traverses shells across the screen
		moveShells(enemyShells, shellArraySize); //Traverses shells across the screen
		
		if (((framesCounter / 120) % 2) == 1) //Have the enemy fire a projectile every 2 seconds
		{
			for (int i = 0; i < enemyForceSize; i++)
			{
				if (enemyForce[i].active)
				{
					enemyForce[i].fire(enemyShells, shellArraySize);
				}
			}

			framesCounter = 0;
		}

		for (int i = 0; i < shellArraySize; i++) //Check if any of the shells are colliding with objects
		{
			
				shells[i].detectCollision(buildings, buildingArraySize, explosions, explosionsArraySize);
				shells[i].detectCollision(enemyForce, enemyForceSize, explosions, explosionsArraySize);

				enemyShells[i].detectCollision(buildings, buildingArraySize, explosions, explosionsArraySize);
				enemyShells[i].detectCollision(enemyForce, enemyForceSize, explosions, explosionsArraySize);
				enemyShells[i].detectCollision(shells, shellArraySize, explosions, explosionsArraySize);
				enemyShells[i].detectCollision(&tank, explosions, explosionsArraySize);
				//SHELLS AREN'T COLLIDING
			
			
		}

		for (int i = 0; i < explosionsArraySize; i++)
		{
			explosions[i].dealDamage(enemyForce, enemyForceSize, &tank);
		}

		//----------------------------------------------------------------------------------

		// Draw
		//----------------------------------------------------------------------------------
		{
			BeginDrawing();

			ClearBackground(RAYWHITE);

			/*DrawText("Mouse", 10, 10, 20, DARKGRAY);
			DrawText(mouseXText, 10, 30, 20, DARKGRAY);
			DrawText(mouseYText, 10, 50, 20, DARKGRAY);

			DrawText("Box", 500, 10, 20, DARKGRAY);
			DrawText(tankXText, 500, 40, 20, DARKGRAY);
			DrawText(tankYText, 500, 60, 20, DARKGRAY);

			DrawText("Rise/Run", 10, 80, 20, DARKGRAY);
			DrawText(riseText, 10, 100, 20, DARKGRAY);
			DrawText(runText, 10, 120, 20, DARKGRAY);

			DrawText("Slope", 10, 160, 20, DARKGRAY);
			DrawText(slopeText, 10, 180, 20, DARKGRAY);

			DrawText("Angle", 10, 220, 20, DARKGRAY);
			DrawText(angleText, 10, 240, 20, DARKGRAY);*/

			DrawText(("Score " + (std::to_string(tank.health))).c_str(), 10, 10, 20, DARKGRAY);
			drawTanks(tank); //Draws the player tank
			drawTanks(enemyForce, enemyForceSize); //Draws enemy tanks
			
			DrawLine(tank.rectangle.x + (tank.rectangle.width / 2.0f), tank.rectangle.y + (tank.rectangle.height / 2.0f), mousePos.x, mousePos.y, BLUE);


			drawShells(shells, shellArraySize); //Draw player shells
			drawShells(enemyShells, shellArraySize); //Draw enemy shells
			drawBuildings(buildings, buildingArraySize); //Draw buildings

			drawExplosions(explosions, explosionsArraySize);

			DrawCircleV(mousePos, 5, RED); //Draw target reticule

			EndDrawing();
		}
		//----------------------------------------------------------------------------------
		if (tank.health <= 0)
		{
			break;
		}
	}
	
	return 0;
}


void moveShells(Projectile* shells, int size)
{
	for (int i = 0; i < size; i++)
	{
		if (shells[i].active == true)
		{
			shells[i].forward();
		}
	}
}


void drawShells(Projectile* shells, int length)
{
	for (int i = 0; i < length; i++)
	{
		
		//DrawRectangleV({ shells[i].rectangle.x, shells[i].rectangle.y }, { shells[i].rectangle.width, shells[i].rectangle.height }, shells[i].color);
		DrawPoly({ (shells[i].rectangle.x + (shells[i].rectangle.width / 2.0f) ), (shells[i].rectangle.y + (shells[i].rectangle.width / 2.0f) ) }, 3, shells[i].rectangle.width, shells[i].angle * 180 / PI - 90, shells[i].color);
	}
}

void drawBuildings(Structure* buildings, int length)
{
	for (int i = 0; i < length; i++)
	{

		DrawRectangleV({ buildings[i].rectangle.x, buildings[i].rectangle.y }, { buildings[i].rectangle.width, buildings[i].rectangle.height }, buildings[i].color);
		
	}
}


void drawTanks(Tank tank)
{
	DrawRectangleV({ tank.rectangle.x, tank.rectangle.y }, { tank.rectangle.width, tank.rectangle.height }, tank.color); //Draw tank body
	DrawPoly(tank.barrelPosition1, 4, 10, (tank.angle * 180 / PI) - 45, BLUE); //Draw tank barrel
	DrawPoly(tank.barrelPosition2, 4, 10, (tank.angle * 180 / PI) - 45, BLUE); //Draw tank barrel
}

void drawTanks(Tank* tanks, int length)
{
	for (int i = 0; i < length; i++)
	{
		DrawRectangleV({ tanks[i].rectangle.x, tanks[i].rectangle.y }, { tanks[i].rectangle.width, tanks[i].rectangle.height }, tanks[i].color); //Draw tank body

		if (tanks[i].active == true)
		{
			DrawPoly(tanks[i].barrelPosition1, 4, 10, (tanks[i].angle * 180 / PI) - 45, BLUE); //Draw tank barrel
			DrawPoly(tanks[i].barrelPosition2, 4, 10, (tanks[i].angle * 180 / PI) - 45, BLUE); //Draw tank barrel
		}
		
	}
	
}

void drawExplosions(Explosion* explosions, int length)
{
	for (int i = 0; i < length; i++)
	{
		if (explosions[i].active == true)
		{
			DrawCircleV(explosions[i].position, explosions[i].radius, explosions[i].color);
		}
		

	}
}
