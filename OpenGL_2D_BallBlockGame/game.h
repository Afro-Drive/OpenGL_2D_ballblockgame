#ifndef GAME_H
#define GAME_H

#include<glad/gl.h>
#include<GLFW/glfw3.h>
#include<vector>

#include"gameLevel.h"
#include"gameObject.h"
#include"ballObject.h"
#include"Actor/powerUp.h"


/// <summary>
/// Game holds all game-related state and functionally.
/// Combines all game-related data into a single class for
/// easy access to each of the components and manageability
/// </summary>
class Game
{
	public:
		// game state
		std::vector<GameLevel> Levels;
		unsigned int Level;
		std::vector<PowerUp> PowerUps;
		unsigned int Lives;

		// constructor
		Game();
		// destructor
		~Game();

		// Initialize game state(load all shader/textures/levels)
		void Init();
		// game loop
		void Run(float dt);
};

#endif