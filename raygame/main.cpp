/*******************************************************************************************
*
*   raylib [core] example - basic window
*
*   This example has been created using raylib 1.0 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2013-2016 Ramon Santamaria (@raysan5)
*
********************************************************************************************/
void startScreen();
void endScreen();

#include "raylib.h"
#include "examples.h"
#include "tanksMain.h"

int main()
{

	// Initialization
	//--------------------------------------------------------------------------------------
	int screenWidth = 800;
	int screenHeight = 450;
	InitWindow(screenWidth, screenHeight, "Tanks!");
	SetTargetFPS(60);  // Set target frames-per-second

	//dropFiles();
	//storageValues();
	//ThreeD();
	//fps();
	startScreen();
	tanksMain();
	endScreen();


	// De-Initialization
	//--------------------------------------------------------------------------------------
	CloseWindow();        // Close window and OpenGL context
	//--------------------------------------------------------------------------------------

	return 0;
}

void startScreen()
{
	while (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) != true)
	{
		BeginDrawing();

		ClearBackground(RAYWHITE);
		DrawText("Tanks!", GetScreenWidth() / 2, GetScreenHeight() / 2, 50, BLACK);

		EndDrawing();
	}
	return;
}

void endScreen()
{
	while (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) != true)
	{
		BeginDrawing();

		ClearBackground(RAYWHITE);
		DrawText("You died.", GetScreenWidth() / 2, GetScreenHeight() / 2, 50, BLACK);

		EndDrawing();
	}
	return;
}