//This is the main file of Tanks!


#include <string>
#include <math.h> 
#include <iostream>
#include "raylib.h"
#include "tank.h"
#include "tanksMain.h"
#include "projectile.h"
#include "Structure.h"


int tanksMain()
{
	// Initialization
	//--------------------------------------------------------------------------------------
	Vector2 barrelPosition1 = {0, 0};
	Vector2 barrelPosition2 = {0, 0};
	Tank tank;
	Tank* tankPointer;
	tankPointer = &tank;
	Tank enemyForce[2];
	Projectile shells[10];
	Projectile enemyShells[10];
	Structure buildings[2];
	int shellArraySize = 10;
	int buildingArraySize = 2;
	int enemyForceSize = 2;
	Vector2 mousePos; // Mouse position
	
	int framesCounter = 0;
	char slopeText[64], mouseXText[64], mouseYText[64], riseText[64], runText[64], angleText[64], tankXText[64], tankYText[64], tankHealthText[64];
	

	for (int i = 0; i < shellArraySize; i++) //Instantiate projectiles
	{
		shells[i].instantiate(0);
		enemyShells[i].instantiate(1);
	}

	tank.instantiate({ 400, 225 }, 0); //Instantiate the player
	enemyForce[0].instantiate({ 300, 300 }, 1); //Instantiate enemies
	enemyForce[1].instantiate({ 300, 200 }, 1); //Instantiate enemies
	

	buildings[0].instantiate({ 500, 100 }, { 60, 30 });
	buildings[1].instantiate({ 500, 200 }, { 60, 30 });
	//--------------------------------------------------------------------------------------


	while (!WindowShouldClose()) // Main game loop
	{
		// Update
		//----------------------------------------------------------------------------------
		framesCounter++; //Counts frames
		mousePos = GetMousePosition(); //Get mouse position

		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) //Get left mouse input
		{
			tank.fire(shells, shellArraySize, -1); //Fire a projectile
		}
		
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
					enemyForce[i].fire(enemyShells, shellArraySize, i);
				}
			}

			framesCounter = 0;
		}

		for (int i = 0; i < shellArraySize; i++) //Check if any of the shells are colliding with objects
		{
			shells[i].detectCollision(buildings, buildingArraySize);
			shells[i].detectCollision(enemyForce, enemyForceSize);


			enemyShells[i].detectCollision(buildings, buildingArraySize);
			enemyShells[i].detectCollision(enemyForce, enemyForceSize);
			enemyShells[i].detectCollision(&tank);
			
		}

		//Convert floats to char*
		{
			//sprintf_s(slopeText, "%f", slope); //Convert to char*
			//sprintf_s(angleText, "%f", angle); //Convert to char*
			//sprintf_s(mouseXText, "%f", mousePos.x); //Convert to char*
			//sprintf_s(mouseYText, "%f", mousePos.y); //Convert to char*
			//sprintf_s(tankXText, "%f", (tank.rectangle.x + (tank.rectangle.width / 2.0f))); //Convert to char*
			//sprintf_s(tankYText, "%f", (tank.rectangle.y + (tank.rectangle.height / 2.0f))); //Convert to char*
			//sprintf_s(riseText, "%f", rise); //Convert to char*
			//sprintf_s(runText, "%f", run); //Convert to char*
			sprintf_s(tankHealthText, "%f", (double)tank.health); //Convert to char*
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

			DrawText(tankHealthText, 10, 10, 20, DARKGRAY);

			drawTanks(tank);
			drawTanks(enemyForce, enemyForceSize);
			
			DrawLine(tank.rectangle.x + (tank.rectangle.width / 2.0f), tank.rectangle.y + (tank.rectangle.height / 2.0f), mousePos.x, mousePos.y, BLUE);


			drawShells(shells, shellArraySize);
			drawShells(enemyShells, shellArraySize);
			drawBuildings(buildings, buildingArraySize);

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
		if (tanks[i].active == true)
		{
			DrawRectangleV({ tanks[i].rectangle.x, tanks[i].rectangle.y }, { tanks[i].rectangle.width, tanks[i].rectangle.height }, tanks[i].color); //Draw tank body
			DrawPoly(tanks[i].barrelPosition1, 4, 10, (tanks[i].angle * 180 / PI) - 45, BLUE); //Draw tank barrel
			DrawPoly(tanks[i].barrelPosition2, 4, 10, (tanks[i].angle * 180 / PI) - 45, BLUE); //Draw tank barrel
		}
		
	}
	
}
