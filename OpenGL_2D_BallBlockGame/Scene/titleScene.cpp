#include "titleScene.h"

#include"sceneMediator.h"
#include<UIMediator.h>
#include<textRenderer.h>
#include<input.h>

TitleScene::TitleScene(unsigned int width, unsigned int height, SceneMediator* sceneMediator, UIMediator* uiMediator)
	:AbstractScene(width, height, sceneMediator, uiMediator),
     level(0)
{ }

void TitleScene::Init()
{
	this->nextScene = SceneName::GAME_MAIN;
	isEnd = false;
}

void TitleScene::Update(float dt)
{
}

void TitleScene::Render(SpriteRenderer* renderer)
{
	// back ground render(stage preview)
	sceneMediator->ShareStages()[level]->Draw(*renderer);

	text->RenderText("Press ENTER to start", 250.0f, (float)height / 2, 1.0f);
	text->RenderText("Press W or S to select level", 245.0f, height / 2 + 20.0f, 0.75f);
}

void TitleScene::ProcessInput(float dt)
{
	if (Input::getKeyTrigger(GLFW_KEY_ENTER))
		isEnd = true;

	if (Input::getKeyTrigger(GLFW_KEY_W))
		this->level = (this->level + 1) % 4;
	if (Input::getKeyTrigger(GLFW_KEY_S))
	{
		if (this->level > 0)
			--this->level;
		else
			this->level = 3;
	}
}

