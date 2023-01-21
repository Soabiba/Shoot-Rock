#pragma once

static int screenWidth;//For some reason whenever I put them in a class or struct the game stops working so that's why they are still global
static int screenHeight;

class Level 
{
public:
	void InitGame(void);        // Initialize game
	void UpdateGame(void);      // Update game (one frame)
	void DrawGame(void);        // Draw game (one frame)
	void UnloadGame(void);      // Unload game
	void UpdateDrawFrame(void); // Update and Draw (one frame)
};
Level level;