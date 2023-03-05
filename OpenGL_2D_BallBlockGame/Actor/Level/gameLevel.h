#ifndef GAME_LEVEL_H
#define GAME_LEVEL_H

#include<vector>
#include<glm/glm.hpp>

#include<brock.h>

// forward reference
class GameObjectMediator;
class PowerUpManager;
class SpriteRenderer;


enum class BrockColor
{
	SOLID = 1,
	WHITE = 2,
};

class GameLevel
{
	public:
		// level state
		std::vector<Brock*> Bricks;
		// constructor
		GameLevel() { };
		GameLevel(GameObjectMediator& mediator);
		~GameLevel();
		// loads level from file
		void Load(const char* file, unsigned int levelWidth, unsigned int levelHeihgt, bool firstLoad);
		// render level
		void Draw(SpriteRenderer& renderer);
		void Update(float dt);
		// check if the level is completed (all non-solid tiles are destroyed)
		bool IsCompleted();
		void JudgeCollision();
	private:
		GameObjectMediator* mediator;        
		PowerUpManager* powerUpManager;
		float shakeTime;
		std::vector<std::vector<unsigned int>> tileData;

		// initialize level from tile data
		void DesignData(unsigned int levelWidth, unsigned int levelHeight);
};

#endif