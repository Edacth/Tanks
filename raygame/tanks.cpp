

#include "raylib.h"
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

	Vector2 tankPosition = { (float)screenWidth / 2, (float)screenHeight / 2 }; //Position of tank
	Vector2 barrelPosition1 = {0, 0};
	Vector2 barrelPosition2 = { 0, 0 };
	Vector2 tankSize = { (float)20, (float)20}; //Size of tank box
	Vector2 mousePos; // Mouse position
	float slope = 0;
	float angle = 0;
	float rise = 0;
	float run = 0;
	char slopeText[64], mouseXText[64], mouseYText[64], riseText[64], runText[64], angleText[64], tankXText[64], tankYText[64];
	SetTargetFPS(60);       // Set target frames-per-second
	//--------------------------------------------------------------------------------------

	
	while (!WindowShouldClose()) // Main game loop
	{
		// Update
		//----------------------------------------------------------------------------------
		mousePos = GetMousePosition(); //Get mouse position
		
		if (IsKeyDown(KEY_RIGHT)) tankPosition.x += 2.5f; //Get arrowkey input
		if (IsKeyDown(KEY_LEFT)) tankPosition.x -= 2.5f; //Get arrowkey input
		if (IsKeyDown(KEY_UP)) tankPosition.y -= 2.5f; //Get arrowkey input
		if (IsKeyDown(KEY_DOWN)) tankPosition.y += 2.5f; //Get arrowkey input

		//Trig Calculations
		rise = (mousePos.y - (tankPosition.y + (tankSize.y / 2.0f)) );
		run = (mousePos.x - (tankPosition.x + (tankSize.x / 2.0f)));
		slope = (rise / run); //Calculate the slope
		angle = (atan2(rise, run) * 180 / PI );

		barrelPosition1 = { (tankPosition.x + (tankSize.x / 2.0f)) + 10 * cos(atan2(rise, run)),
			(tankPosition.y + (tankSize.y / 2.0f)) + 10 * sin(atan2(rise, run)) };
		barrelPosition2 = { (tankPosition.x + (tankSize.x / 2.0f)) + 20 * cos(atan2(rise, run)),
			(tankPosition.y + (tankSize.y / 2.0f)) + 20 * sin(atan2(rise, run)) };

		//Convert floats to char*
		sprintf_s(slopeText, "%f", slope); //Convert to char*
		sprintf_s(angleText, "%f", angle); //Convert to char*
		sprintf_s(mouseXText, "%f", mousePos.x); //Convert to char*
		sprintf_s(mouseYText, "%f", mousePos.y); //Convert to char*
		sprintf_s(tankXText, "%f", (tankPosition.x + (tankSize.x / 2.0f))); //Convert to char*
		sprintf_s(tankYText, "%f", (tankPosition.y + (tankSize.y / 2.0f))); //Convert to char*
		sprintf_s(riseText, "%f", rise); //Convert to char*
		sprintf_s(runText, "%f", run); //Convert to char*

		//----------------------------------------------------------------------------------

		// Draw
		//----------------------------------------------------------------------------------
		BeginDrawing();

		ClearBackground(RAYWHITE);

		DrawText("Mouse", 10, 10, 20, DARKGRAY);
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
		DrawText(angleText, 10, 240, 20, DARKGRAY);


		DrawRectangleV(tankPosition, tankSize, MAROON);
		DrawLine(tankPosition.x + (tankSize.x / 2.0f), tankPosition.y + (tankSize.y / 2.0f), mousePos.x, mousePos.y, BLUE);

		//DrawCircle((tankPosition.x + (tankSize.x / 2.0f)) + 20 * cos(atan2(rise, run)), (tankPosition.y + (tankSize.y / 2.0f)) + 20 * sin(atan2(rise, run)), 3, RED); //Draw halfway mark
		DrawPoly(barrelPosition1, 4, 10, angle-45, BLUE);
		DrawPoly(barrelPosition2, 4, 10, angle - 45, BLUE);

		DrawCircleV(mousePos, 5, RED);//Draw target reticule

		EndDrawing();
		//----------------------------------------------------------------------------------
	}

	// De-Initialization
	//--------------------------------------------------------------------------------------
	CloseWindow();        // Close window and OpenGL context
	//--------------------------------------------------------------------------------------

	return 0;
}