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
		// did the player lose all his lives?
		if (this->lives == 0)
		{
			// Game over
			this->ResetLevel();
			this->ResetPlayer();
			this->isEnd = true;
		}
		this->ResetPlayer();
	}
	if (this->stageVector[this->level]->IsCompleted())
	{
		this->ResetLevel();
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

//void GameMainScene::DoCollisions()
//{
//	for (GameObject& box : this->stageVector[this->level].Bricks)
//	{
//		if (!box.Destroyed)
//		{
//			Collision collision = CheckCollision(*Ball, box);
//			if (std::get<0>(collision)) // if collision is true
//			{
//				// destroy block if not solid
//				if (!box.IsSolid)
//				{
//					box.Destroyed = true;
//					this->SpawnPowerUps(box);
//					this->sceneMediator->getSoundEngine()->play2D("Audio/SE/bleep.mp3", false);
//				}
//				else
//				{
//					// if block is solid, enable shake effect
//					ShakeTime = 0.05f;
//					effects->Shake = true;
//					this->sceneMediator->getSoundEngine()->play2D("Audio/SE/solid.wav", false);
//				}
//				// collision resolution
//				Direction dir = std::get<1>(collision);
//				glm::vec2 diff_vector = std::get<2>(collision);
//				if (!(Ball->PassThrough && !box.IsSolid))
//				{
//					if (dir == LEFT || dir == RIGHT) // horizontal collision
//					{
//						Ball->Velocity.x = -Ball->Velocity.x; // reverse horizontal velocity
//						// relocate
//						float penetration = Ball->Radius - std::abs(diff_vector.x);
//						if (dir == LEFT)
//							Ball->Position.x += penetration; // move ball to right
//						else
//							Ball->Position.x -= penetration; // move ball to left
//					}
//					else // vertical collision
//					{
//						Ball->Velocity.y = -Ball->Velocity.y; // reverse vertical velocity
//						// relocate
//						float penetration = Ball->Radius - std::abs(diff_vector.y);
//						if (dir == UP)
//							Ball->Position.y -= penetration; // move ball back up
//						else
//							Ball->Position.y += penetration; // move ball back down
//					}
//				}
//			}
//		}
//	}
//	// also check collisions on PowerUps and if so, active them
//	for (PowerUp& powerUp : this->powerUps)
//	{
//		if (!powerUp.Destroyed)
//		{
//			if (powerUp.Position.y >= this->height)
//				powerUp.Destroyed = true;
//			if (CheckCollision(*player, powerUp))
//			{
//				// collided with player, now activate powerup
//				ActivatePowerUp(powerUp);
//				powerUp.Destroyed = true;
//				powerUp.Activated = true;
//				this->sceneMediator->getSoundEngine()->play2D("Audio/SE/powerup.wav", false);
//			}
//		}
//	}
//	// and finally check collisions for player pad (unless stuck)
//	Collision result = CheckCollision(*Ball, *player);
//	if (!Ball->Stuck && std::get<0>(result))
//	{
//		// check where it hit the board, and change velocity based on where it hit the board
//		float centerBoard = player->Position.x + player->Size.x / 2.0f;
//		float distance = (Ball->Position.x + Ball->Radius) - centerBoard;
//		float percentage = distance / (player->Size.x / 2.0f);
//		// then move accordingly
//		float strength = 2.0f;
//		glm::vec2 oldVelocity = Ball->Velocity;
//		Ball->Velocity.x = INITIAL_BALL_VELOCITY.x * percentage * strength;
//		Ball->Velocity.y = -Ball->Velocity.y;
//		Ball->Velocity = glm::normalize(Ball->Velocity) * glm::length(oldVelocity);
//		Ball->Velocity.y = -1.0f * abs(Ball->Velocity.y);
//
//		// if Sticky powerup is activated, also stick ball to paddle once new velocity vectors were calculated
//		Ball->Stuck = (Ball->Sticky);
//
//		this->sceneMediator->getSoundEngine()->play2D("Audio/SE/bleep.wav", false);
//	}
//}

//bool GameMainScene::CheckCollision(GameObject& one, GameObject& two)
//{
//	// collision x-axis?
//	bool collisionX = one.Position.x + one.Size.x >= two.Position.x
//		&& two.Position.x + two.Size.x >= one.Position.x;
//	// collision y-axis?
//	bool collisionY = one.Position.y + one.Size.y >= two.Position.y
//		&& two.Position.y + two.Size.y >= one.Position.y;
//
//	return collisionX && collisionY;
//}

//Collision GameMainScene::CheckCollision(BallObject& one, GameObject& two)
//{
//	// get center point circle first
//	glm::vec2 center(one.Position + one.Radius);
//	// calculate AABB info (center, half-extents)
//	glm::vec2 aabb_half_extents(two.Size.x / 2.0f, two.Size.y / 2.0f);
//	glm::vec2 aabb_center(
//		two.Position.x + aabb_half_extents.x,
//		two.Position.y + aabb_half_extents.y);
//	// get difference vector between both centers
//	glm::vec2 difference = center - aabb_center;
//	glm::vec2 clamped = glm::clamp(difference, -aabb_half_extents, aabb_half_extents);
//	// add clamped value to AABB_center and we get the value of box closest to circle
//	glm::vec2 closest = aabb_center + clamped;
//	// retrieve vector between center circle and clsoest point AABB and check if length <= radius
//	difference = closest - center;
//	if (glm::length(difference) <= one.Radius)
//		return std::make_tuple(true, VectorDirection(difference), difference);
//	else
//		return std::make_tuple(false, UP, glm::vec2(0.0f, 0.0f));
//}

//Direction GameMainScene::VectorDirection(glm::vec2 target)
//{
//	glm::vec2 compass[] = {
//		glm::vec2(0.0f, 1.0f),  // up
//		glm::vec2(1.0f, 0.0f),  // right
//		glm::vec2(0.0f, -1.0f), // down
//		glm::vec2(-1.0f, 0.0f)  // left
//	};
//	float max = 0.0f;
//	unsigned int best_match = -1;
//	for (unsigned int i = 0; i < 4; i++)
//	{
//		float dot_product = glm::dot(glm::normalize(target), compass[i]);
//		if (dot_product > max)
//		{
//			max = dot_product;
//			best_match = i;
//		}
//	}
//	return (Direction)best_match;
//}

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

//bool ShouldSpawn(unsigned int chance)
//{
//	unsigned int random = rand() % chance;
//	return random == 0;
//}
//void GameMainScene::SpawnPowerUps(GameObject& block)
//{
//	//if (ShouldSpawn(75)) // 1 in 75 chance
//	//	this->powerUps.push_back(PowerUp("speed", glm::vec3(0.5f, 0.5f, 1.0f), 0.0f, block.Position, ResourceManager::GetTexture("powerup_speed")));
//	//if (ShouldSpawn(75))
//	//	this->powerUps.push_back(PowerUp("sticky", glm::vec3(1.0f, 0.5f, 1.0f), 20.0f, block.Position, ResourceManager::GetTexture("powerup_sticky")));
//	//if (ShouldSpawn(75))
//	//	this->powerUps.push_back(PowerUp("pass-through", glm::vec3(0.5f, 1.0f, 0.5f), 10.0f, block.Position, ResourceManager::GetTexture("powerup_passthrough")));
//	//if (ShouldSpawn(75))
//	//	this->powerUps.push_back(PowerUp("pad-size-increase", glm::vec3(1.0f, 0.6f, 0.4f), 0.0f, block.Position, ResourceManager::GetTexture("powerup_increase")));
//	//if (ShouldSpawn(15)) // negative powerups should spawn more often
//	//	this->powerUps.push_back(PowerUp("confuse", glm::vec3(1.0f, 0.3f, 0.3f), 15.0f, block.Position, ResourceManager::GetTexture("powerup_confuse")));
//	//if (ShouldSpawn(15))
//	//	this->powerUps.push_back(PowerUp("chaos", glm::vec3(0.9f, 0.5f, 0.25f), 15.0f, block.Position, ResourceManager::GetTexture("powerup_chaos")));
//}

//void GameMainScene::UpdatePowerUps(float dt)
//{
//	for (PowerUp& powerUp : this->powerUps)
//	{
//		powerUp.Position += powerUp.Velocity * dt;
//		if (powerUp.Activated)
//		{
//			powerUp.Duration -= dt;
//
//			if (powerUp.Duration <= 0.0f)
//			{
//				// remove powerup from list (will late be removed)
//				powerUp.Activated = false;
//				// deactivate effects
//				if (powerUp.Type == "sticky")
//				{
//					if (!IsOtherPowerUpActive(this->powerUps, "sticky"))
//					{
//						// only reset if no other PowerUp of tyep sticky is active
//						Ball->Sticky = false;
//						player->Color = glm::vec3(1.0f);
//					}
//				}
//				else if (powerUp.Type == "pass-through")
//				{
//					if (!IsOtherPowerUpActive(this->powerUps, "pass-through"))
//					{
//						// only reset if no other PowerUp of tyep pass-through is active
//						Ball->PassThrough = false;
//						player->Color = glm::vec3(1.0f);
//					}
//				}
//				if (powerUp.Type == "confuse")
//				{
//					if (!IsOtherPowerUpActive(this->powerUps, "confuse"))
//					{
//						// only reset if no other PowerUp of tyep confuse is active
//						effects->Confuse = false;
//					}
//				}
//				else if (powerUp.Type == "chaos")
//				{
//					if (!IsOtherPowerUpActive(this->powerUps, "chaos"))
//					{
//						// only reset if no other PowerUp of tyep chaos is active
//						effects->Chaos = false;
//					}
//				}
//			}
//		}
//	}
//	this->powerUps.erase(
//		std::remove_if(
//			this->powerUps.begin(),
//			this->powerUps.end(),
//			[](const PowerUp& powerUp) { return powerUp.Destroyed && !powerUp.Activated; }),
//		this->powerUps.end());
//}

//void GameMainScene::ActivatePowerUp(PowerUp& powerUp)
//{
//	if (powerUp.Type == "speed")
//	{
//		Ball->Velocity *= 1.2;
//	}
//	else if (powerUp.Type == "sticky")
//	{
//		Ball->Sticky = true;
//		player->Color = glm::vec3(1.0f, 0.5f, 1.0f);
//	}
//	else if (powerUp.Type == "pass-through")
//	{
//		Ball->PassThrough = true;
//		player->Color = glm::vec3(1.0f, 0.5f, 0.5f);
//	}
//	else if (powerUp.Type == "pad-size-increase")
//	{
//		player->Size.x += 50;
//	}
//	else if (powerUp.Type == "confuse")
//	{
//		if (!effects->Chaos)
//			effects->Confuse = true; // only activate if chaos wasn't already activated
//	}
//	else if (powerUp.Type == "chaos")
//	{
//		if (!effects->Confuse)
//			effects->Chaos = true; // only activate if confuse wasn't already activated
//	}
//}

//bool GameMainScene::IsOtherPowerUpActive(std::vector<PowerUp>& powerUps, std::string type)
//{
//	//for (const PowerUp& powerUp : powerUps)
//	//{
//	//	if (powerUp.Activated)
//	//		if (powerUp.Type == type)
//	//			return true;
//	//}
//	return false
//}

bool GameMainScene::LoadStageData()
{
	bool loadFile = true;
	if (!isLoadedStage)
	{
		GameLevel* one = new GameLevel(*(this->gameObjectMediator));
		GameLevel* two = new GameLevel(*(this->gameObjectMediator));
		GameLevel* three = new GameLevel(*(this->gameObjectMediator));
		GameLevel* four = new GameLevel(*(this->gameObjectMediator));
		
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
