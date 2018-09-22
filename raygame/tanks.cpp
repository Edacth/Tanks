

#include "raylib.h"
#include "tanks.h"
#include <iostream>
#include <string>
#include <math.h> 

int tanks()
{
	// Initialization
	//--------------------------------------------------------------------------------------
	int screenWidth = 800;
	int screenHeight = 450;
	InitWindow(screenWidth, screenHeight, "Tanks!");
	SetTargetFPS(60);       // Set target frames-per-second

	Tank tank = { { (float)screenWidth / 2, (float)screenHeight / 2, 20, 20 }, 3, 2.5f, MAROON };
	Tank enemyForce[1] = { { { 300, 300, 20, 20 }, 1, 2.5f, BLACK } };
	Projectile shells[10];
	Projectile enemyShells[10];
	Structure buildings[2] = { { {500, 100, 60, 30}, PURPLE },{ { 500, 500, 60, 30 }, PURPLE } };
	int shellArraySize = 10;
	int buildingArraySize = 2;
	Vector2 barrelPosition1 = {0, 0};
	Vector2 barrelPosition2 = { 0, 0 };
	Vector2 mousePos; // Mouse position
	float slope = 0;
	float angle = 0;
	float rise = 0;
	float run = 0;
	int framesCounter = 0;
	char slopeText[64], mouseXText[64], mouseYText[64], riseText[64], runText[64], angleText[64], tankXText[64], tankYText[64], tankHealthText;
	

	for (int i = 0; i < shellArraySize; i++)
	{
		shells[i] = { {200, 200, 10, 10}, 0, 0, false, RED };
		enemyShells[i] = { {200, 180, 10, 10}, 0, 0, false, BLUE };
	}
	/*for (int i = 0; i < 2; i++)
	{
		enemyForce[i] = { { 300, 300, 20, 20 }, 1, 2.5f, MAROON };
	}*/
	//--------------------------------------------------------------------------------------

	
	while (!WindowShouldClose()) // Main game loop
	{
		// Update
		//----------------------------------------------------------------------------------
		framesCounter++;
		mousePos = GetMousePosition(); //Get mouse position
		
		tank.move(buildings, buildingArraySize); //Handle the tank's movement

		//Trig Calculations
		rise = (mousePos.y - (tank.rectangle.y + (tank.rectangle.height / 2.0f)) );
		run = (mousePos.x - (tank.rectangle.x + ( tank.rectangle.width / 2.0f)));
		slope = (rise / run); //Calculate the slope
		angle = (atan2(rise, run));

		barrelPosition1 = { (tank.rectangle.x + (tank.rectangle.width / 2.0f)) + 10 * cos(angle),
			(tank.rectangle.y + (tank.rectangle.height / 2.0f)) + 10 * sin(angle) };
		barrelPosition2 = { (tank.rectangle.x + (tank.rectangle.width / 2.0f)) + 20 * cos(angle),
			(tank.rectangle.y + (tank.rectangle.height / 2.0f)) + 20 * sin(angle) };


		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) //Get left mouse input
		{
			tank.fire(shells, shellArraySize, barrelPosition2, angle);
		}

		if (((framesCounter / 120) % 2) == 1)
		{
			enemyForce[0].fire(enemyShells, shellArraySize, { enemyForce[0].rectangle.x + 30, enemyForce[0].rectangle.y }, 0);
			framesCounter = 0;
		}

		simulateShells(shells, shellArraySize);
		simulateShells(enemyShells, shellArraySize);
		for (int i = 0; i < shellArraySize; i++)
		{
			shells[i].detectCollision(buildings, buildingArraySize, tank, enemyForce, 1);
			enemyShells[i].detectCollision(buildings, buildingArraySize, tank, enemyForce, 1);
			
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

void Projectile::forward()
{

	rectangle.x += speed * cos(angle);
	rectangle.y += speed * sin(angle);
}

bool Projectile::detectCollision(Structure* buildings, int buildingsLength, Tank tank, Tank* enemyForce, int enemyForceLength)
{
	for (int i = 0; i < buildingsLength; i++)
	{
		if ( (CheckCollisionRecs(rectangle, buildings[i].rectangle) ) ||
			( (rectangle.x <= 0) || (rectangle.x >= 800) || (rectangle.y <= 0) ||
			(rectangle.y >= 450) ))
		{
			active = false;
			speed = 0;
			rectangle.x = 200;
			rectangle.y = 200;
			angle = 0;
			return true;
		}
	}
	for (int i = 0; i < enemyForceLength; i++)
	{
		if ( (CheckCollisionRecs(rectangle, enemyForce[i].rectangle) ) ||
			( (rectangle.x <= 0) || (rectangle.x >= 800) || (rectangle.y <= 0) ||
			(rectangle.y >= 450) ))
		{
			active = false;
			speed = 0;
			rectangle.x = 200;
			rectangle.y = 200;
			angle = 0;
			return true;
		}
	}
	if (CheckCollisionRecs(tank.rectangle, rectangle))
	{
		active = false;
		speed = 0;
		rectangle.x = 200;
		rectangle.y = 200;
		angle = 0;
		return true;
	}
	
	return false;
}

void simulateShells(Projectile* shells, int size)
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

void Tank::move(Structure* buildings, int buildingsLength)
{
	Vector2 newPos = {rectangle.x, rectangle.y};
	if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) //Get arrowkey input
	{
		newPos.x += 2.5f;
	}
	if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) //Get arrowkey input
	{
		newPos.x -= 2.5f; 
	}
	if (!detectCollision(newPos, buildings, buildingsLength))
	{
		rectangle.x = newPos.x;
	}

	newPos = { rectangle.x, rectangle.y };
	if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) //Get arrowkey input
	{
		newPos.y -= 2.5f; 
	}
	if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)) //Get arrowkey input
	{
		newPos.y += 2.5f; 
	}
	
	if (!detectCollision(newPos, buildings, buildingsLength))
	{
		rectangle.y = newPos.y;
	}
	
}

bool Tank::detectCollision(Vector2 newPos, Structure* buildings, int buildingsLength)
{
	for (int i = 0; i < buildingsLength; i++)
	{
		if (CheckCollisionRecs({newPos.x, newPos.y, rectangle.width, rectangle.height}, buildings[i].rectangle))
		{
			return true;
		}
	}
	return false;
}

void Tank::fire(Projectile* shells, int shellArraySize, Vector2 barrelPosition2, float angle)
{
	int j = -1;
	for (int i = 0; i < shellArraySize; i++)
	{
		if (shells[i].active == false)
		{
			j = i;
			shells[i].active = true;
			break;
		}
	}
	shells[j].rectangle.x = { barrelPosition2.x }; //Move projectile to barrel
	shells[j].rectangle.y = { barrelPosition2.y }; //Move projectile to barrel
	shells[j].angle = angle;
	shells[j].speed = 6;
}