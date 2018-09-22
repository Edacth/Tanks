

#include "raylib.h"
#define MAX_COLUMNS 20

int dropFiles()
{
	// Initialization
	//--------------------------------------------------------------------------------------
	int screenWidth = 800;
	int screenHeight = 450;

	InitWindow(screenWidth, screenHeight, "raylib [core] example - drop files");

	int count = 0;
	char **droppedFiles = { 0 };

	SetTargetFPS(60);
	//--------------------------------------------------------------------------------------

	// Main game loop
	while (!WindowShouldClose())    // Detect window close button or ESC key
	{
		// Update
		//----------------------------------------------------------------------------------
		if (IsFileDropped())
		{
			droppedFiles = GetDroppedFiles(&count);
		}
		//----------------------------------------------------------------------------------

		// Draw
		//----------------------------------------------------------------------------------
		BeginDrawing();

		ClearBackground(RAYWHITE);

		if (count == 0) DrawText("Drop your files to this window!", 100, 40, 20, DARKGRAY);
		else
		{
			DrawText("Dropped files:", 100, 40, 20, DARKGRAY);

			for (int i = 0; i < count; i++)
			{
				if (i % 2 == 0) DrawRectangle(0, 85 + 40 * i, screenWidth, 40, Fade(LIGHTGRAY, 0.5f));
				else DrawRectangle(0, 85 + 40 * i, screenWidth, 40, Fade(LIGHTGRAY, 0.3f));

				DrawText(droppedFiles[i], 120, 100 + 40 * i, 10, GRAY);
			}

			DrawText("Drop new files...", 100, 110 + 40 * count, 20, DARKGRAY);
		}

		EndDrawing();
		//----------------------------------------------------------------------------------
	}

	// De-Initialization
	//--------------------------------------------------------------------------------------
	ClearDroppedFiles();    // Clear internal buffers

	CloseWindow();          // Close window and OpenGL context
							//--------------------------------------------------------------------------------------

	return 0;
}

// NOTE: Storage positions must start with 0, directly related to file memory layout
typedef enum { STORAGE_SCORE = 0, STORAGE_HISCORE } StorageData;

int storageValues()
{
	// Initialization
	//--------------------------------------------------------------------------------------
	int screenWidth = 800;
	int screenHeight = 450;

	InitWindow(screenWidth, screenHeight, "raylib [core] example - storage save/load values");

	int score = 0;
	int hiscore = 0;

	int framesCounter = 0;

	SetTargetFPS(60);
	//--------------------------------------------------------------------------------------

	// Main game loop
	while (!WindowShouldClose())    // Detect window close button or ESC key
	{
		// Update
		//----------------------------------------------------------------------------------
		if (IsKeyPressed(KEY_R))
		{
			score = GetRandomValue(1000, 2000);
			hiscore = GetRandomValue(2000, 4000);
		}

		if (IsKeyPressed(KEY_ENTER))
		{
			StorageSaveValue(STORAGE_SCORE, score);
			StorageSaveValue(STORAGE_HISCORE, hiscore);
		}
		else if (IsKeyPressed(KEY_SPACE))
		{
			// NOTE: If requested position could not be found, value 0 is returned
			score = StorageLoadValue(STORAGE_SCORE);
			hiscore = StorageLoadValue(STORAGE_HISCORE);
		}

		framesCounter++;
		//----------------------------------------------------------------------------------

		// Draw
		//----------------------------------------------------------------------------------
		BeginDrawing();

		ClearBackground(RAYWHITE);

		DrawText(FormatText("SCORE: %i", score), 280, 130, 40, MAROON);
		DrawText(FormatText("HI-SCORE: %i", hiscore), 210, 200, 50, BLACK);

		DrawText(FormatText("frames: %i", framesCounter), 10, 10, 20, LIME);

		DrawText("Press R to generate random numbers", 220, 40, 20, LIGHTGRAY);
		DrawText("Press ENTER to SAVE values", 250, 310, 20, LIGHTGRAY);
		DrawText("Press SPACE to LOAD values", 252, 350, 20, LIGHTGRAY);

		EndDrawing();
		//----------------------------------------------------------------------------------
	}

	// De-Initialization
	//--------------------------------------------------------------------------------------   
	CloseWindow();        // Close window and OpenGL context
						  //--------------------------------------------------------------------------------------

	return 0;
}

int ThreeD()
{
	// Initialization
	//--------------------------------------------------------------------------------------
	int screenWidth = 800;
	int screenHeight = 450;

	InitWindow(screenWidth, screenHeight, "raylib [core] example - 3d camera free");

	// Define the camera to look into our 3d world
	Camera3D camera;
	camera.position = { 10.0f, 10.0f, 10.0f }; // Camera position
	camera.target = { 0.0f, 0.0f, 0.0f };      // Camera looking at point
	camera.up = { 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
	camera.fovy = 45.0f;                                // Camera field-of-view Y
	camera.type = CAMERA_PERSPECTIVE;                   // Camera mode type

	Vector3 cubePosition = { 0.0f, 0.0f, 0.0f };

	SetCameraMode(camera, CAMERA_FREE); // Set a free camera mode

	SetTargetFPS(60);                   // Set our game to run at 60 frames-per-second
										//--------------------------------------------------------------------------------------

										// Main game loop
	while (!WindowShouldClose())        // Detect window close button or ESC key
	{
		// Update
		//----------------------------------------------------------------------------------
		UpdateCamera(&camera);          // Update camera

		if (IsKeyDown('Z')) camera.target = { 0.0f, 0.0f, 0.0f };
		//----------------------------------------------------------------------------------

		// Draw
		//----------------------------------------------------------------------------------
		BeginDrawing();

		ClearBackground(RAYWHITE);

		BeginMode3D(camera);

		DrawCube(cubePosition, 2.0f, 2.0f, 2.0f, RED);
		DrawCubeWires(cubePosition, 2.0f, 2.0f, 2.0f, MAROON);

		DrawGrid(10, 1.0f);

		EndMode3D();

		DrawRectangle(10, 10, 320, 133, Fade(SKYBLUE, 0.5f));
		DrawRectangleLines(10, 10, 320, 133, BLUE);

		DrawText("Free camera default controls:", 20, 20, 10, BLACK);
		DrawText("- Mouse Wheel to Zoom in-out", 40, 40, 10, DARKGRAY);
		DrawText("- Mouse Wheel Pressed to Pan", 40, 60, 10, DARKGRAY);
		DrawText("- Alt + Mouse Wheel Pressed to Rotate", 40, 80, 10, DARKGRAY);
		DrawText("- Alt + Ctrl + Mouse Wheel Pressed for Smooth Zoom", 40, 100, 10, DARKGRAY);
		DrawText("- Z to zoom to (0, 0, 0)", 40, 120, 10, DARKGRAY);

		EndDrawing();
		//----------------------------------------------------------------------------------
	}

	// De-Initialization
	//--------------------------------------------------------------------------------------
	CloseWindow();        // Close window and OpenGL context
						  //--------------------------------------------------------------------------------------

	return 0;
}

int fps()
{
	// Initialization
	//--------------------------------------------------------------------------------------
	int screenWidth = 800;
	int screenHeight = 450;

	InitWindow(screenWidth, screenHeight, "raylib [core] example - 3d camera first person");

	// Define the camera to look into our 3d world (position, target, up vector)
	Camera camera = { 0 };
	camera.position =  { 4.0f, 2.0f, 4.0f };
	camera.target =  { 0.0f, 1.8f, 0.0f };
	camera.up =  { 0.0f, 1.0f, 0.0f };
	camera.fovy = 60.0f;
	camera.type = CAMERA_PERSPECTIVE;

	// Generates some random columns
	float heights[MAX_COLUMNS];
	Vector3 positions[MAX_COLUMNS];
	Color colors[MAX_COLUMNS];

	for (int i = 0; i < MAX_COLUMNS; i++)
	{
		heights[i] = (float)GetRandomValue(1, 12);
		positions[i] = { (float)GetRandomValue(-15.0f, 15.0f), (float)heights[i] / 2, (float)GetRandomValue(-15.0f, 15.0f) };
		colors[i] = { (unsigned char)GetRandomValue(20.0f, 255.0f), (unsigned char)GetRandomValue(10, 55), (unsigned char)30, (unsigned char)255 };
	}

	SetCameraMode(camera, CAMERA_FIRST_PERSON); // Set a first person camera mode

	SetTargetFPS(60);                           // Set our game to run at 60 frames-per-second
												//--------------------------------------------------------------------------------------

												// Main game loop
	while (!WindowShouldClose())                // Detect window close button or ESC key
	{
		// Update
		//----------------------------------------------------------------------------------
		UpdateCamera(&camera);                  // Update camera
												//----------------------------------------------------------------------------------

												// Draw
												//----------------------------------------------------------------------------------
		BeginDrawing();

		ClearBackground(RAYWHITE);

		BeginMode3D(camera);

		DrawPlane( { 0.0f, 0.0f, 0.0f },  { 32.0f, 32.0f }, LIGHTGRAY); // Draw ground
		DrawCube( { -16.0f, 2.5f, 0.0f }, 1.0f, 5.0f, 32.0f, BLUE);     // Draw a blue wall
		DrawCube( { 16.0f, 2.5f, 0.0f }, 1.0f, 5.0f, 32.0f, LIME);      // Draw a green wall
		DrawCube( { 0.0f, 2.5f, 16.0f }, 32.0f, 5.0f, 1.0f, GOLD);      // Draw a yellow wall

																				 // Draw some cubes around
		for (int i = 0; i < MAX_COLUMNS; i++)
		{
			DrawCube(positions[i], 2.0f, heights[i], 2.0f, colors[i]);
			DrawCubeWires(positions[i], 2.0f, heights[i], 2.0f, MAROON);
		}

		EndMode3D();

		DrawRectangle(10, 10, 220, 70, Fade(SKYBLUE, 0.5f));
		DrawRectangleLines(10, 10, 220, 70, BLUE);

		DrawText("First person camera default controls:", 20, 20, 10, BLACK);
		DrawText("- Move with keys: W, A, S, D", 40, 40, 10, DARKGRAY);
		DrawText("- Mouse move to look around", 40, 60, 10, DARKGRAY);

		EndDrawing();
		//----------------------------------------------------------------------------------
	}

	// De-Initialization
	//--------------------------------------------------------------------------------------   
	CloseWindow();        // Close window and OpenGL context
	//--------------------------------------------------------------------------------------

	return 0;
}