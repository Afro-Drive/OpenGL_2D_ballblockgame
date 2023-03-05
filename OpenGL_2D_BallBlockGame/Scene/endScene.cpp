#include "endScene.h"

#include<textRenderer.h>
#include<postProcessor.h>
#include<input.h>
#include"sceneMediator.h"


EndScene::EndScene(unsigned int width, unsigned int height, SceneMediator* sceneMediator)
	:AbstractScene(width, height, sceneMediator) { }

EndScene::~EndScene()
{
}

void EndScene::Init()
{
	nextScene = SceneName::TITLE;
	isEnd = false;
	isComplete = (this->sceneMediator->ShareLives() > 0);
}

void EndScene::Update(float dt)
{
}

void EndScene::Render(SpriteRenderer* renderer)
{
	glm::vec3 headerPos = glm::vec3(320.0f, height / 2 - 20.0f, 1.0f);
	glm::vec3 sentensePos = glm::vec3(130.0f, height / 2, 1.0f);

	if (isComplete)
		text->RenderText("You WON!!", headerPos.x, headerPos.y, headerPos.z, glm::vec3(0.0f, 1.0f, 0.0f));
	else
		text->RenderText("Game Over..", headerPos.x, headerPos.y, headerPos.z, glm::vec3(0.0f, 1.0f, 0.0f));
	
	text->RenderText(
		"Press ENTER to retry or ESC to quit",
		sentensePos.x, sentensePos.y, sentensePos.z,
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
