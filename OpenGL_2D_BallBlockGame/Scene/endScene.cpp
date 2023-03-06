#include "endScene.h"

#include<sstream>

#include<textRenderer.h>
#include<postProcessor.h>
#include<input.h>
#include"sceneMediator.h"


EndScene::EndScene(unsigned int width, unsigned int height, SceneMediator* sceneMediator, UIMediator* uIMediator)
	:AbstractScene(width, height, sceneMediator, uIMediator),
     isComplete(false), score(0),
	 HEADER_POS(glm::vec3(320.0f, height / 2 - 20.0f, 1.0f)), SENTENSE_POS(glm::vec3(130.0f, height / 2, 1.0f)), SCORE_POS(glm::vec3(300.0f, height / 2 - 50.0f, 1.4f))
{ 
}

EndScene::~EndScene()
{
}

void EndScene::Init()
{
	nextScene = SceneName::TITLE;
	isEnd = false;
	isComplete = (this->sceneMediator->ShareLives() > 0);
	score = this->sceneMediator->ShareScore();
}

void EndScene::Update(float dt)
{
}

void EndScene::Render(SpriteRenderer* renderer)
{
	std::stringstream scoreStr;
	scoreStr << this->score;
	text->RenderText("SCORE: " + scoreStr.str(), SCORE_POS.x, SCORE_POS.y, SCORE_POS.z, glm::vec3(0.0f, 1.0f, 0.0f));

	if (isComplete)
		text->RenderText("You WON!!", HEADER_POS.x, HEADER_POS.y, HEADER_POS.z, glm::vec3(0.0f, 1.0f, 0.0f));
	else
		text->RenderText("Game Over..", HEADER_POS.x, HEADER_POS.y, HEADER_POS.z, glm::vec3(0.0f, 1.0f, 0.0f));
	
	text->RenderText(
		"Press ENTER to retry or ESC to quit",
		SENTENSE_POS.x, SENTENSE_POS.y, SENTENSE_POS.z,
		glm::vec3(1.0f, 1.0f, 0.0f));
}

void EndScene::ProcessInput(float dt)
{
	if (Input::Keys[GLFW_KEY_ENTER])
	{
		effects->Chaos = false;
		this->isEnd = true;
	}
}
