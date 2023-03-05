#include "gameObjectMediator.h"

#include<vector>

#include<gameObject.h>
#include<powerUp.h>
#include<postProcessor.h>
#include"brock.h"

GameObjectMediator::GameObjectMediator(ISoundEngine& soundEngine, PostProcessor& effects, GameMainScene& gameMainScene)
	:soundEngine(&soundEngine), effects(&effects), gameMainScene(&gameMainScene)
{
}
GameObject* GameObjectMediator::SurveyActiveGameObject(GameTag order)
{
	switch (order)
	{
	case GameTag::BALL:
		return (GameObject*)this->gameMainScene->GetBallObject();
	case GameTag::PLAYER:
		return (GameObject*)this->gameMainScene->GetPlayerObject();
	}
	
	return nullptr;
}
