#ifndef GAME_H
#define GAME_H

#include<glad/gl.h>
#include<GLFW/glfw3.h>

#include"gameLevel.h"

/// <summary>
/// Represents the current state of the game
/// </summary>
enum GameState {
	GAME_ACTIVE,
	GAME_MENU,
	GAME_WIN
};

/// <summary>
/// Game holds all game-related state and functionally.
/// Combines all game-related data into a single class for
/// easy access to each of the components and manageability
/// </summary>
class Game
{
	public:
		// game state
		GameState State;
		bool Keys[1024];
		unsigned int Width, Height;
		std::vector<GameLevel> Levels;
		unsigned int Level;
		// constructor
		Game(unsigned int width, unsigned int height);
		// destructor
		~Game();

		// Initialize game state(load all shader/textures/levels)
		void Init();
		// game loop
		void ProcessInput(float dt);
		void Update(float dt);
		void Render();
};

#endif