#include "gameMainScene.h"

#include<glm/glm.hpp>
#include<iostream>
#include<sstream>
#include<algorithm>

#include<resourceManager.h>
#include<gameObjectMediator.h>
#include"sceneMediator.h"
#include<spriteRenderer.h>
#include<particleGenerator.h>
#include<postProcessor.h>
#include<textRenderer.h>
#include<ballObject.h>
#include<player.h>
#include<ballCollider.h>
#include<boxCollider.h>
#include<transform.h>
#include<uIMediator.h>
#include<scoreUI.h>
#include<LivesUI.h>


// Initial size of the player paddle
const glm::vec2 PLAYER_SIZE(100.0f, 20.0f);
// Initial velocity of the player paddle
const float PLAYER_VELOCITY(500.0f);
// Initial velocity of the Ball
const glm::vec2 INITIAL_BALL_VELOCITY(100.0f, -350.0f);
// Radius of the ball object
const float BALL_RADIUS = 12.5f;

// Game-related State data
ParticleGenerator* Particles;
ScoreUI* scoreUI;
LivesUI* livesUI;


GameMainScene::GameMainScene(unsigned int width, unsigned int height, SceneMediator* sceneMediator, UIMediator* uiMediator)
	:AbstractScene(width, height, sceneMediator, uiMediator),
	 Ball(nullptr), isLoadedStage(false), level(0), lives(0), player(nullptr)
{
	gameObjectMediator = new GameObjectMediator(
		*(this->sceneMediator->getSoundEngine()),
		*(this->effects),
		*this);
}

GameMainScene::~GameMainScene()
{
	delete player;
	delete Ball;
	delete Particles;
	for (GameLevel* gl : stageVector)
	{
		delete gl;
	}
	stageVector.clear();
	delete scoreUI;
}

void GameMainScene::Init()
{
	// scene related
	nextScene = SceneName::END;
	isEnd = false;

	// load levels
	this->LoadStageData();

	this->level = this->sceneMediator->ShareLevel();
	this->lives = 3;

	Particles = new ParticleGenerator(
			ResourceManager::GetShader("particle"),
			ResourceManager::GetTexture("particle"),
			500);

	// Player configure
	glm::vec2 playerPos = glm::vec2(
		this->width / 2.0f - PLAYER_SIZE.x / 2.0f,
		this->height - PLAYER_SIZE.y);
	player = new Player(playerPos, PLAYER_SIZE, ResourceManager::GetTexture("paddle"), *gameObjectMediator);
	BoxCollider2D* playerCollider = new BoxCollider2D(playerPos, PLAYER_SIZE, *player, *(this->gameObjectMediator));
	player->transform->SetCollider(*playerCollider);
	
	// Ball configure
	glm::vec2 modifyPos = glm::vec2(PLAYER_SIZE.x / 2.0f - BALL_RADIUS, -BALL_RADIUS * 2.0f);
	glm::vec2 ballPos = playerPos + modifyPos;
	Ball = new BallObject(ballPos, BALL_RADIUS, INITIAL_BALL_VELOCITY, ResourceManager::GetTexture("ball"), nullptr, *gameObjectMediator);
	BallCollider2D* ballCollider = new BallCollider2D(ballPos, *Ball, BALL_RADIUS, *(this->gameObjectMediator));
	Ball->transform->SetCollider(*ballCollider);

	player->SetTargetBall(Ball);

	// UI
	this->uiMediator->SetFocusLevel(*(this->stageVector[level]));
	scoreUI = new ScoreUI(*(this->uiMediator), *(this->gameObjectMediator));
	livesUI = new LivesUI(*(this->uiMediator), *(this->gameObjectMediator));
	this->uiMediator->SetFollowingScoreUI(*scoreUI);
	this->uiMediator->SetFollowingLivesUI(*livesUI);
	this->uiMediator->UpdateLives(this->lives);
}

void GameMainScene::Update(float dt)
{
	// update objects
	Ball->Update(dt);
	player->Update(dt);
	// update particles
	Particles->Update(dt, *(dynamic_cast<GameObject*>(Ball)), 2, glm::vec2(Ball->Radius / 2.0f));
	// update PowerUps
	this->stageVector[level]->Update(dt);
	
	if (Ball->transform->Position.y >= this->height) // if ball reach bottom edge?
	{
		--this->lives;
		this->uiMediator->UpdateLives(this->lives);
		// did the player lose all his lives?
		if (this->lives == 0)
		{
			// Game over
			this->ResetPlayer();
			this->isEnd = true;
		}
		this->ResetPlayer();
	}
	if (this->stageVector[this->level]->IsCompleted())
	{
		this->ResetPlayer();
		effects->Chaos = true;
		this->isEnd = true;
	}

}

void GameMainScene::Render(SpriteRenderer* renderer)
{
	// begin rendering to postprocessing framebuffer
	effects->BeginRender();
	{
		// draw background
		Texture2D bgTex = ResourceManager::GetTexture("background");
		renderer->DrawSprite(bgTex,
			glm::vec2(0.0f, 0.0f), glm::vec2(this->width, this->height), 0.0f);
		// draw level
		this->stageVector[this->level]->Draw(*renderer);
		// player render
		player->Draw(*renderer);
		// draw particles
		Particles->Draw();
		// Ball renderer
		Ball->Draw(*renderer);
	}
	// end rendering to postprocessing framebuffer
	effects->EndRender();
	// render postprocessing quad
	effects->Render((float)glfwGetTime());

	std::stringstream ss;
	ss << this->lives;
	text->RenderText("Lives: " + ss.str(), 5.0f, 5.0f, 1.0f);
	scoreUI->Draw(*text);
}

void GameMainScene::ProcessInput(float dt)
{
}

void GameMainScene::ResetPlayer()
{
	// reset player/ball stats
	player->transform->Size = PLAYER_SIZE;
	player->transform->Position = glm::vec2(this->width / 2.0f - PLAYER_SIZE.x / 2.0f, this->height - PLAYER_SIZE.y);
	Ball->Reset(player->transform->Position + glm::vec2(PLAYER_SIZE.x / 2.0f - BALL_RADIUS, -(BALL_RADIUS * 2.0f)), INITIAL_BALL_VELOCITY);
}

void GameMainScene::ResetLevel()
{
	bool reload = false;

	if (this->level == 0)
		this->stageVector[0]->Load("Levels/one.lvl", this->width, this->height / 2, reload);
	if (this->level == 1)
		this->stageVector[1]->Load("Levels/two.lvl", this->width, this->height / 2, reload);
	if (this->level == 2)
		this->stageVector[2]->Load("Levels/three.lvl", this->width, this->height / 2, reload);
	if (this->level == 3)
		this->stageVector[3]->Load("Levels/four.lvl", this->width, this->height / 2, reload);
}

bool GameMainScene::LoadStageData()
{
	bool loadFile = true;
	if (!isLoadedStage)
	{
		GameLevel* one = new GameLevel(*(this->gameObjectMediator), *(this->uiMediator));
		GameLevel* two = new GameLevel(*(this->gameObjectMediator), *(this->uiMediator));
		GameLevel* three = new GameLevel(*(this->gameObjectMediator), *(this->uiMediator));
		GameLevel* four = new GameLevel(*(this->gameObjectMediator), *(this->uiMediator));
		
		one->Load("Levels/one.lvl", this->width, this->height / 2, loadFile);
		two->Load("Levels/two.lvl", this->width, this->height / 2, loadFile);
		three->Load("Levels/three.lvl", this->width, this->height / 2, loadFile);
		four->Load("Levels/four.lvl", this->width, this->height / 2, loadFile);

		this->stageVector.push_back(one);
		this->stageVector.push_back(two);
		this->stageVector.push_back(three);
		this->stageVector.push_back(four);

		this->isLoadedStage = true;
	}
	else
	{
		loadFile = false;
		this->stageVector[0]->Load("Levels/one.lvl", this->width, this->height / 2, loadFile);
		this->stageVector[1]->Load("Levels/two.lvl", this->width, this->height / 2, loadFile);
		this->stageVector[2]->Load("Levels/three.lvl", this->width, this->height / 2, loadFile);
		this->stageVector[3]->Load("Levels/four.lvl", this->width, this->height / 2, loadFile);
	}

	return isLoadedStage;
}
