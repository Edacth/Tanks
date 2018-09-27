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
	int screenWidth = 800;
	int screenHeight = 450;
	InitWindow(screenWidth, screenHeight, "Tanks!");
	SetTargetFPS(60);       // Set target frames-per-second
	Vector2 barrelPosition1 = {0, 0};
	Vector2 barrelPosition2 = {0, 0};
	Tank tank = { { (float)screenWidth / 2, (float)screenHeight / 2, 20, 20 }, 3, 2.5f, MAROON };
	Tank enemyForce[1] = { { { 300, 300, 20, 20 }, 1, 2.5f, BLACK } };
	Projectile shells[10];
	Projectile enemyShells[10];
	Structure buildings[2] = { { {500, 100, 60, 30}, PURPLE },{ { 500, 500, 60, 30 }, PURPLE } };
	int shellArraySize = 10;
	int buildingArraySize = 2;
	int enemyForceSize = 1;
	
	Vector2 mousePos; // Mouse position
	float slope = 0;
	float angle = 0;
	float rise = 0;
	float run = 0;
	int framesCounter = 0;
	char slopeText[64], mouseXText[64], mouseYText[64], riseText[64], runText[64], angleText[64], tankXText[64], tankYText[64], tankHealthText;
	

	for (int i = 0; i < shellArraySize; i++) //Instantiate projectiles
	{
		shells[i] = { {200, 200, 10, 10}, 0, 0, false, RED };
		enemyShells[i] = { {200, 180, 10, 10}, 0, 0, false, BLUE };
	}
	//--------------------------------------------------------------------------------------

	while (!WindowShouldClose()) // Main game loop
	{
		// Update
		//----------------------------------------------------------------------------------
		framesCounter++; //Counts frames
		mousePos = GetMousePosition(); //Get mouse position
		
		tank.move(buildings, buildingArraySize); //Handle the tank's movement

		//Trig Calculations
		rise = (mousePos.y - (tank.rectangle.y + (tank.rectangle.height / 2.0f)) );
		run = (mousePos.x - (tank.rectangle.x + ( tank.rectangle.width / 2.0f)));
		slope = (rise / run); //Calculate the slope
		angle = (atan2(rise, run));

		


		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) //Get left mouse input
		{
			tank.fire(shells, shellArraySize, barrelPosition2, angle); //Fire a projectile
		}

		if (((framesCounter / 120) % 2) == 1) //Have the enemy fire a projectile every 2 seconds
		{
			enemyForce[0].fire(enemyShells, shellArraySize, { enemyForce[0].rectangle.x + 30, enemyForce[0].rectangle.y }, 0);
			framesCounter = 0;
		}

		barrelPosition1 = { (tank.rectangle.x + (tank.rectangle.width / 2.0f)) + 10 * cos(angle),
			(tank.rectangle.y + (tank.rectangle.height / 2.0f)) + 10 * sin(angle) };
		barrelPosition2 = { (tank.rectangle.x + (tank.rectangle.width / 2.0f)) + 20 * cos(angle),
			(tank.rectangle.y + (tank.rectangle.height / 2.0f)) + 20 * sin(angle) };

		moveShells(shells, shellArraySize); //Traverses shells across the screen
		moveShells(enemyShells, shellArraySize); //Traverses shells across the screen
		
		for (int i = 0; i < shellArraySize; i++) //Check if any of the shells are colliding with objects
		{
			shells[i].detectCollision(buildings, buildingArraySize);
			shells[i].detectCollision(enemyForce, enemyForceSize);


			enemyShells[i].detectCollision(buildings, buildingArraySize);
			enemyShells[i].detectCollision(tank);
			
		}

		//Convert floats to char*
		{
			sprintf_s(slopeText, "%f", slope); //Convert to char*
			sprintf_s(angleText, "%f", angle); //Convert to char*
			sprintf_s(mouseXText, "%f", mousePos.x); //Convert to char*
			sprintf_s(mouseYText, "%f", mousePos.y); //Convert to char*
			sprintf_s(tankXText, "%f", (tank.rectangle.x + (tank.rectangle.width / 2.0f))); //Convert to char*
			sprintf_s(tankYText, "%f", (tank.rectangle.y + (tank.rectangle.height / 2.0f))); //Convert to char*
			sprintf_s(riseText, "%f", rise); //Convert to char*
			sprintf_s(runText, "%f", run); //Convert to char*
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

			DrawRectangleV({ tank.rectangle.x, tank.rectangle.y }, { tank.rectangle.width, tank.rectangle.height }, tank.color); //Draw tank body
			DrawLine(tank.rectangle.x + (tank.rectangle.width / 2.0f), tank.rectangle.y + (tank.rectangle.height / 2.0f), mousePos.x, mousePos.y, BLUE);
			DrawPoly(barrelPosition1, 4, 10, (angle * 180 / PI) - 45, BLUE); //Draw tank barrel
			DrawPoly(barrelPosition2, 4, 10, (angle * 180 / PI) - 45, BLUE); //Draw tank barrel
			

			DrawRectangleV({ enemyForce[0].rectangle.x, enemyForce[0].rectangle.y }, { enemyForce[0].rectangle.width, enemyForce[0].rectangle.height }, enemyForce[0].color); //Draw enemy tank
			drawShells(shells, shellArraySize);
			drawShells(enemyShells, shellArraySize);
			drawBuildings(buildings, 1);

			DrawCircleV(mousePos, 5, RED); //Draw target reticule

			EndDrawing();
		}
		//----------------------------------------------------------------------------------
	}

	// De-Initialization
	//--------------------------------------------------------------------------------------
	CloseWindow();        // Close window and OpenGL context
	//--------------------------------------------------------------------------------------

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

/*
void drawTanks(Tank tank)
{
	DrawRectangleV({ tank.rectangle.x, tank.rectangle.y }, { tank.rectangle.width, tank.rectangle.height }, tank.color); //Draw tank body
	DrawLine(tank.rectangle.x + (tank.rectangle.width / 2.0f), tank.rectangle.y + (tank.rectangle.height / 2.0f), mousePos.x, mousePos.y, BLUE);
	DrawPoly(barrelPosition1, 4, 10, (angle * 180 / PI) - 45, BLUE); //Draw tank barrel
	DrawPoly(barrelPosition2, 4, 10, (angle * 180 / PI) - 45, BLUE); //Draw tank barrel
}
*/