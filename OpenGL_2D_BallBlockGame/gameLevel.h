#ifndef GAME_LEVEL_H
#define GAME_LEVEL_H

#include<vector>
#include<fstream>
#include<sstream>
#include<glm/glm.hpp>

#include"gameObject.h"
#include"spriteRenderer.h"
#include"resourceManager.h"


class GameLevel
{
	public:
		// level state
		std::vector<GameObject> Bricks;
		// constructor
		GameLevel() { }
		// loads level from file
		void Load(const char* file, unsigned int levelWidth, unsigned int levelHeihgt);
		// render level
		void Draw(SpriteRenderer& renderer);
		// check fi the level is completed (all non-solid tiles are destroyed)
		bool IsCompleted();
	private:
		// initialize level from tile data
		void init(std::vector<std::vector<unsigned int>> tileData,
			unsigned int levelWidth, unsigned int levelHeight);
};

#endif