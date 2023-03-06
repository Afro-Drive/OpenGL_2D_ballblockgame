#include "game.h"

#include<glm/glm.hpp>
#include<algorithm>
#include<irrKlang/irrKlang.h>
using namespace irrklang;
#pragma comment(lib, "irrKlang.lib") // link with irrKlang.dll

#include"SpriteRenderer.h"
#include"resourceManager.h"
#include"Scene/sceneManager.h"
#include"Scene/titleScene.h"
#include"Scene/gameMainScene.h"
#include"Scene/endScene.h"
#include"Scene/abstractScene.h"
#include<screenDesc.h>
#include"Scene/SceneMediator.h"
#include"UI/uIMediator.h"

// Game-related State data
SpriteRenderer* Renderer;
ISoundEngine* soundEngine;
SceneManager* sceneManager;
SceneMediator* sceneMediator;
UIMediator* uIMediator;


Game::Game()
{

}

Game::~Game()
{
	SceneManager::DestroySelf();
	delete Renderer;
	delete sceneMediator;
	delete uIMediator;
}

void Game::Init()
{
	// load shaders
	ResourceManager::LoadShader("Shaders/sprite.vert", "Shaders/sprite.frag", nullptr, "sprite");
	ResourceManager::LoadShader("Shaders/particle.vert", "Shaders/particle.frag", nullptr, "particle");
	ResourceManager::LoadShader("Shaders/postProcessing.vert", "Shaders/postProcessing.frag", nullptr, "postprocessing");
	// configure shaders
	glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(ScreenDesc::WIDTH),
		static_cast<float>(ScreenDesc::HEIGHT), 0.0f, -1.0f, 1.0f);
	ResourceManager::GetShader("sprite").Use().SetInteger("image", 0);
	ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);
	ResourceManager::GetShader("particle").Use().SetInteger("sprite", 0);
	ResourceManager::GetShader("particle").SetMatrix4("projection", projection);
	// set render-specific controls
	Shader sprite = ResourceManager::GetShader("sprite");
	Renderer = new SpriteRenderer(sprite);
	// load textures
	ResourceManager::LoadTexture("Textures/pop_cat.png", true, "cat");
	ResourceManager::LoadTexture("Textures/background.jpg", false, "background");
	ResourceManager::LoadTexture("Textures/block.png", false, "block");
	ResourceManager::LoadTexture("Textures/block_solid.png", false, "block_solid");
	ResourceManager::LoadTexture("Textures/paddle.png", true, "paddle");
	ResourceManager::LoadTexture("Textures/awesomeface.png", true, "ball");
	ResourceManager::LoadTexture("Textures/particle.png", true, "particle");
	ResourceManager::LoadTexture("Textures/PowerUp/powerup_speed.png", true, "powerup_speed");
	ResourceManager::LoadTexture("Textures/PowerUp/powerup_sticky.png", true, "powerup_sticky");
	ResourceManager::LoadTexture("Textures/PowerUp/powerup_increase.png", true, "powerup_increase");
	ResourceManager::LoadTexture("Textures/PowerUp/powerup_confuse.png", true, "powerup_confuse");
	ResourceManager::LoadTexture("Textures/PowerUp/powerup_chaos.png", true, "powerup_chaos");
	ResourceManager::LoadTexture("Textures/PowerUp/powerup_passthrough.png", true, "powerup_passthrough");
	// This will be destroyed in AbstractScene's destructor
	soundEngine = createIrrKlangDevice();
	// UI
	uIMediator = new UIMediator();
	// scene related
	sceneManager = SceneManager::GetInstance();
	sceneMediator = new SceneMediator(*soundEngine);
	AbstractScene* titleScene = new TitleScene(ScreenDesc::WIDTH, ScreenDesc::HEIGHT, sceneMediator, uIMediator);
	sceneManager->AddScene(SceneName::TITLE, *titleScene);
	AbstractScene* endScene = new EndScene(ScreenDesc::WIDTH, ScreenDesc::HEIGHT, sceneMediator, uIMediator);
	sceneManager->AddScene(SceneName::END, *endScene);
	AbstractScene* gameMainScene = new GameMainScene(ScreenDesc::WIDTH, ScreenDesc::HEIGHT, sceneMediator, uIMediator);
	sceneManager->AddScene(SceneName::GAME_MAIN, *gameMainScene);
	sceneManager->ChangeScene(SceneName::TITLE);

	// Audio
	soundEngine->play2D("Audio/BGM/breakout.mp3", true);
}

void Game::Run(float dt)
{
	sceneManager->RunScene(*Renderer, dt);
}
