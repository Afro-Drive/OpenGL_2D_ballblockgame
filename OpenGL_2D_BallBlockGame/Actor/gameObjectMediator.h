#ifndef GAME_OBJECT_MEDIATOR_H
#define GAME_OBJECT_MEDIATOR_H


#include<irrKlang/irrKlang.h>
using namespace irrklang;
#pragma comment(lib, "irrKlang.lib") // link with irrKlang.dll
#include<vector>
#include<glm/glm.hpp>
#include<string>

#include<gameMainScene.h>
#include"../Scene/abstractScene.h"

// forword reference
class GameObject;
class PowerUp;
class Brock;
class PostProcessor;


class GameObjectMediator
{
	public:
		GameObjectMediator();
		GameObjectMediator(ISoundEngine& soundEngine, PostProcessor& effects, GameMainScene& gameMainScene);

		ISoundEngine* getSoundEngine();
		std::vector<Brock*> GetBricks();
		GameObject* SurveyActiveGameObject(GameTag order);
		PostProcessor* GetEffects();
		glm::uvec2 GetScreenSize();
	private:
		ISoundEngine* soundEngine;
		GameMainScene* gameMainScene;
		PostProcessor* effects;
};

inline ISoundEngine* GameObjectMediator::getSoundEngine()
{
	return this->soundEngine;
}

inline std::vector<Brock*> GameObjectMediator::GetBricks()
{
	return this->gameMainScene->GetBricks();
}

inline PostProcessor* GameObjectMediator::GetEffects()
{
	return this->effects;
}

inline glm::uvec2 GameObjectMediator::GetScreenSize()
{
	return this->gameMainScene->AbstractScene::GetSceneSize();
}

#endif // !GAME_OBJECT_MEDIATOR_H
