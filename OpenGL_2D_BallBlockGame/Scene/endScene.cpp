#include "endScene.h"

#include<textRenderer.h>
#include<postProcessor.h>
#include<input.h>


EndScene::EndScene(unsigned int width, unsigned int height, SceneMediator* sceneMediator)
	:AbstractScene(width, height, sceneMediator) { }

EndScene::~EndScene()
{
}

void EndScene::Init()
{
	nextScene = SceneName::TITLE;
}

void EndScene::Update(float dt)
{
}

void EndScene::Render(SpriteRenderer* renderer)
{
	text->RenderText("You WON!!", 320.0f, height / 2 - 20.0f, 1.0f, glm::vec3(0.0f, 1.0f, 0.0f));
	text->RenderText("Press ENTER to retry or ESC to quit", 130.0f, height / 2, 1.0f, glm::vec3(1.0f, 1.0f, 0.0f));
}

void EndScene::ProcessInput(float dt)
{
	if (Input::Keys[GLFW_KEY_ENTER])
	{
		effects->Chaos = false;
		this->isEnd = true;
	}
}
