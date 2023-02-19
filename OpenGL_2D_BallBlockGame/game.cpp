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
#include"screenDesc.h"
#include"Scene/SceneMediator.h"


//// Initial size of the player paddle
//const glm::vec2 PLAYER_SIZE(100.0f, 20.0f);
//// Initial velocity of the player paddle
//const float PLAYER_VELOCITY(500.0f);
//// Initial velocity of the Ball
//const glm::vec2 INITIAL_BALL_VELOCITY(100.0f, -350.0f);
//// Radius of the ball object
//const float BALL_RADIUS = 12.5f;
////float ShakeTime = 0.0f;
//// The Width of the screen
//const unsigned int SCREEN_WIDTH = 800;
//// The Height of the screen
//const unsigned int SCREEN_HEIGHT = 600;


// Game-related State data
//GameObject* Player;
//BallObject* Ball;
SpriteRenderer* Renderer;
//ParticleGenerator* Particles;
//PostProcessor* Effects;
ISoundEngine* soundEngine;
//TextRenderer* Text;
SceneManager* sceneManager;
SceneMediator* sceneMediator;


Game::Game()
{

}

Game::~Game()
{
	SceneManager::DestroySelf();
	delete Renderer;
	delete sceneMediator;
	//delete Player;
	//delete Ball;
	//delete Particles;
	//delete Effects;
	soundEngine->drop();
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
	//Particles = new ParticleGenerator(
	//	ResourceManager::GetShader("particle"),
	//	ResourceManager::GetTexture("particle"),
	//	500);
	//Effects = new PostProcessor(ResourceManager::GetShader("postprocessing"), this->Width, this->Height);
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
	// load levels
	//GameLevel one;
	//one.Load("levels/one.lvl", this->Width, this->Height / 2);
	//GameLevel two;
	//two.Load("levels/two.lvl", this->Width, this->Height / 2);
	//GameLevel three;
	//three.Load("levels/three.lvl", this->Width, this->Height / 2);
	//GameLevel four;
	//four.Load("levels/four.lvl", this->Width, this->Height / 2);
	//this->Levels.push_back(one);
	//this->Levels.push_back(two);
	//this->Levels.push_back(three);
	//this->Levels.push_back(four);
	//this->Level = 0;
	//this->Lives = 3;
	//// Player configure
	//glm::vec2 playerPos = glm::vec2(
	//	this->Width / 2.0f - PLAYER_SIZE.x / 2.0f,
	//	this->Height - PLAYER_SIZE.y);
	//Player = new GameObject(playerPos, PLAYER_SIZE, ResourceManager::GetTexture("paddle"));
	//// Ball configure
	//glm::vec2 ballPos = playerPos + glm::vec2(PLAYER_SIZE.x / 2.0f - BALL_RADIUS, -BALL_RADIUS * 2.0f);
	//// fix sticky paddle 
	//Ball = new BallObject(ballPos, BALL_RADIUS, INITIAL_BALL_VELOCITY, ResourceManager::GetTexture("ball"));
	//// Audio
	//SoundEngine->play2D("Audio/BGM/breakout.mp3", true);
	//// UI-Text
	//Text = new TextRenderer(this->Width, this->Height);
	//Text->Load("Fonts/OCRAEXT.TTF", 24);
	
	// initialize sound engine, enable to use sound related functions
	// This will be destroyed in AbstractScene's destructor
	soundEngine = createIrrKlangDevice();
	// scene related
	sceneManager = SceneManager::GetInstance();
	sceneMediator = new SceneMediator();
	AbstractScene* titleScene = new TitleScene(ScreenDesc::WIDTH, ScreenDesc::HEIGHT, soundEngine, sceneMediator);
	sceneManager->AddScene(SceneName::TITLE, *titleScene);
	AbstractScene* endScene = new EndScene(ScreenDesc::WIDTH, ScreenDesc::HEIGHT, soundEngine, sceneMediator);
	sceneManager->AddScene(SceneName::END, *endScene);
	AbstractScene* gameMainScene = new GameMainScene(ScreenDesc::WIDTH, ScreenDesc::HEIGHT, soundEngine, sceneMediator);
	sceneManager->AddScene(SceneName::GAME_MAIN, *gameMainScene);
	sceneManager->ChangeScene(SceneName::TITLE);
}

//void Game::ProcessInput(float dt)
//{
	//if (this->State == GAME_MENU)
	//{
	//	if (this->Keys[GLFW_KEY_ENTER] && !this->KeysProcessed[GLFW_KEY_ENTER])
	//	{
	//		this->State = GAME_ACTIVE;
	//		this->KeysProcessed[GLFW_KEY_ENTER] = true;
	//	}
	//	if (this->Keys[GLFW_KEY_W] && !this->KeysProcessed[GLFW_KEY_W])
	//	{
	//		this->Level = (this->Level + 1) % 4;
	//		this->KeysProcessed[GLFW_KEY_W] = true;
	//	}
	//	if (this->Keys[GLFW_KEY_S] && !this->KeysProcessed[GLFW_KEY_S])
	//	{
	//		if (this->Level > 0)
	//			--this->Level;
	//		else
	//			this->Level = 3;
	//		this->KeysProcessed[GLFW_KEY_S] = true;
	//	}
	//}
	//if (this->State == GAME_ACTIVE)
	//{
	//	float velocity = PLAYER_VELOCITY * dt;
	//	// move playerboard
	//	if (this->Keys[GLFW_KEY_A])
	//	{
	//		if (Player->Position.x >= 0.0f)
	//		{
	//			Player->Position.x -= velocity;
	//			if (Ball->Stuck)
	//				Ball->Position.x -= velocity;
	//		}
	//	}
	//	if (this->Keys[GLFW_KEY_D])
	//	{
	//		if (Player->Position.x <= this->Width - Player->Size.x)
	//		{
	//			Player->Position.x += velocity;
	//			if (Ball->Stuck)
	//				Ball->Position.x += velocity;
	//		}
	//	}
	//	if (this->Keys[GLFW_KEY_SPACE])
	//		Ball->Stuck = false;
	//}
	//if (this->State == GAME_WIN)
	//{
	//	if (this->Keys[GLFW_KEY_ENTER])
	//	{
	//		this->KeysProcessed[GLFW_KEY_ENTER] = true;
	//		Effects->Chaos = false;
	//		this->State = GAME_MENU;
	//	}
	//}
//}

void Game::Run(float dt)
{
	sceneManager->RunScene(*Renderer, dt);

	//// update objects
	//Ball->Move(dt, this->Width);
	//// check for collisions
	//this->DoCollisions();
	//// update particles
	//Particles->Update(dt, *Ball, 2, glm::vec2(Ball->Radius / 2.0f));
	//// update PowerUps
	//this->UpdatePowerUps(dt);
	//// reduce shake time
	//if (ShakeTime > 0.0f)
	//{
	//	ShakeTime -= dt;
	//	if (ShakeTime <= 0.0f)
	//		Effects->Shake = false;
	//}
	//if (Ball->Position.y >= this->Height) // di ball reach bottom edge?
	//{
	//	--this->Lives;
	//	// did the player lose all his lives?
	//	if (this->Lives == 0)
	//	{
	//		// Game over
	//		this->ResetLevel();
	//		this->State = GAME_MENU;
	//	}
	//	this->ResetPlayer();
	//}
	//if (this->State == GAME_ACTIVE && this->Levels[this->Level].IsCompleted())
	//{
	//	this->ResetLevel();
	//	this->ResetPlayer();
	//	Effects->Chaos = true;
	//	this->State = GAME_WIN;
	//}
}

//void Game::Render()
//{
	//if (this->State == GAME_ACTIVE || this->State == GAME_MENU)
	//{
		//// begin rendering to postprocessing framebuffer
		//Effects->BeginRender();

		//// draw background
		//Texture2D bgTex = ResourceManager::GetTexture("background");
		//Renderer->DrawSprite(bgTex,
		//	glm::vec2(0.0f, 0.0f), glm::vec2(this->Width, this->Height), 0.0f);
		//// draw level
		//this->Levels[this->Level].Draw(*Renderer);
		//// player render
		//Player->Draw(*Renderer);
		//// draw particles
		//Particles->Draw();
		//// Ball renderer
		//Ball->Draw(*Renderer);
		//// PowerUp render
		//for (PowerUp& powerUp : this->PowerUps)
		//	if (!powerUp.Destroyed)
		//		powerUp.Draw(*Renderer);
		//// end rendering to postprocessing framebuffer
		//Effects->EndRender();
		//// render postprocessing quad
		//Effects->Render(glfwGetTime());
		//std::stringstream ss;
		//ss << this->Lives;
		//Text->RenderText("Lives: " + ss.str(), 5.0f, 5.0f, 1.0f);
	//}
	//if (this->State == GAME_MENU)
	//{
	//	Text->RenderText("Press ENTER to start", 250.0f, Height / 2, 1.0f);
	//	Text->RenderText("Press W or S to select level", 245.0f, Height / 2 + 20.0f, 0.75f);
	//}
	//if (this->State == GAME_WIN)
	//{
	//	Text->RenderText("You WON!!", 320.0f, Height / 2 - 20.0f, 1.0f, glm::vec3(0.0f, 1.0f, 0.0f));
	//	Text->RenderText("Press ENTER to retry or ESC to quit", 130.0f, Height / 2 , 1.0f, glm::vec3(1.0f, 1.0f, 0.0f));
	//}
//}

//void Game::DoCollisions()
//{
//	for (GameObject& box : this->Levels[this->Level].Bricks)
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
//					SoundEngine->play2D("Audio/SE/bleep.mp3", false);
//				}
//				else
//				{
//					// if block is solid, enable shake effect
//					ShakeTime = 0.05f;
//					Effects->Shake = true;
//					SoundEngine->play2D("Audio/SE/solid.wav", false);
//				}
//				// collision resolution
//				Direction dir = std::get<1>(collision);
//				glm::vec2 diff_vector = std::get<2>(collision);
//				if (!(Ball->PassThrough && !box.IsSolid))
//				{
//				    if (dir == LEFT || dir == RIGHT) // horizontal collision
//				    {
//				    	Ball->Velocity.x = -Ball->Velocity.x; // reverse horizontal velocity
//				    	// relocate
//				    	float penetration = Ball->Radius - std::abs(diff_vector.x);
//				    	if (dir == LEFT)
//				    		Ball->Position.x += penetration; // move ball to right
//				    	else
//				    		Ball->Position.x -= penetration; // move ball to left
//				    }
//				    else // vertical collision
//				    {
//				    	Ball->Velocity.y = -Ball->Velocity.y; // reverse vertical velocity
//				    	// relocate
//				    	float penetration = Ball->Radius - std::abs(diff_vector.y);
//				    	if (dir == UP)
//				    		Ball->Position.y -= penetration; // move ball back up
//				    	else
//				    		Ball->Position.y += penetration; // move ball back down
//				    }
//				}
//			}
//		}
//	}
//	// also check collisions on PowerUps and if so, active them
//	for (PowerUp& powerUp : this->PowerUps)
//	{
//		if (!powerUp.Destroyed)
//		{
//			if (powerUp.Position.y >= this->Height)
//				powerUp.Destroyed = true;
//			if (CheckCollision(*Player, powerUp))
//			{
//				// collided with player, now activate powerup
//				ActivatePowerUp(powerUp);
//				powerUp.Destroyed = true;
//				powerUp.Activated = true;
//				SoundEngine->play2D("Audio/SE/powerup.wav", false);
//			}
//		}
//	}
//	// and finally check collisions for player pad (unless stuck)
//	Collision result = CheckCollision(*Ball, *Player);
//	if (!Ball->Stuck && std::get<0>(result))
//	{
//		// check where it hit the board, and change velocity based on where it hit the board
//		float centerBoard = Player->Position.x + Player->Size.x / 2.0f;
//		float distance = (Ball->Position.x + Ball->Radius) - centerBoard;
//		float percentage = distance / (Player->Size.x / 2.0f);
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
//		SoundEngine->play2D("Audio/SE/bleep.wav", false);
//	}
//}

//bool Game::CheckCollision(GameObject& one, GameObject& two)
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

//Collision Game::CheckCollision(BallObject& one, GameObject& two)
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

//Direction Game::VectorDirection(glm::vec2 target)
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

//void Game::ResetPlayer()
//{
//	//// reset player/ball stats
//	//Player->Size = PLAYER_SIZE;
//	//Player->Position = glm::vec2(this->Width / 2.0f - PLAYER_SIZE.x / 2.0f, this->Height - PLAYER_SIZE.y);
//	//Ball->Reset(Player->Position + glm::vec2(PLAYER_SIZE.x / 2.0f - BALL_RADIUS, -(BALL_RADIUS * 2.0f)), INITIAL_BALL_VELOCITY);
//}

//void Game::ResetLevel()
//{
//	if (this->Level == 0)
//		this->Levels[0].Load("Levels/one.lvl", this->Width, this->Height / 2);
//	if (this->Level == 1)
//		this->Levels[1].Load("Levels/two.lvl", this->Width, this->Height / 2); 
//	if (this->Level == 2)
//		this->Levels[2].Load("Levels/three.lvl", this->Width, this->Height / 2); 
//	if (this->Level == 3)
//		this->Levels[3].Load("Levels/four.lvl", this->Width, this->Height / 2);
//
//	this->Lives = 3;
//}

//bool ShouldSpawn(unsigned int chance)
//{
//	unsigned int random = rand() % chance;
//	return random == 0;
//}
//void Game::SpawnPowerUps(GameObject& block)
//{
//	if (ShouldSpawn(75)) // 1 in 75 chance
//		this->PowerUps.push_back(PowerUp("speed", glm::vec3(0.5f, 0.5f, 1.0f), 0.0f, block.Position, ResourceManager::GetTexture("powerup_speed")));
//	if (ShouldSpawn(75))
//		this->PowerUps.push_back(PowerUp("sticky", glm::vec3(1.0f, 0.5f, 1.0f), 20.0f, block.Position, ResourceManager::GetTexture("powerup_sticky")));
//	if (ShouldSpawn(75))
//		this->PowerUps.push_back(PowerUp("pass-through", glm::vec3(0.5f, 1.0f, 0.5f), 10.0f, block.Position, ResourceManager::GetTexture("powerup_passthrough")));
//	if (ShouldSpawn(75))
//		this->PowerUps.push_back(PowerUp("pad-size-increase", glm::vec3(1.0f, 0.6f, 0.4f), 0.0f, block.Position, ResourceManager::GetTexture("powerup_increase")));
//	if (ShouldSpawn(15)) // negative powerups should spawn more often
//		this->PowerUps.push_back(PowerUp("confuse", glm::vec3(1.0f, 0.3f, 0.3f), 15.0f, block.Position, ResourceManager::GetTexture("powerup_confuse")));
//	if (ShouldSpawn(15))
//		this->PowerUps.push_back(PowerUp("chaos", glm::vec3(0.9f, 0.5f, 0.25f), 15.0f, block.Position, ResourceManager::GetTexture("powerup_chaos")));
//}

//void Game::UpdatePowerUps(float dt)
//{
	//for (PowerUp& powerUp : this->PowerUps)
	//{
	//	powerUp.Position += powerUp.Velocity * dt;
	//	if (powerUp.Activated)
	//	{
	//		powerUp.Duration -= dt;

	//		if (powerUp.Duration <= 0.0f)
	//		{
	//			// remove powerup from list (will late be removed)
	//			powerUp.Activated = false;
	//			// deactivate effects
	//			if (powerUp.Type == "sticky")
	//			{
	//				if (!IsOtherPowerUpActive(this->PowerUps, "sticky"))
	//				{
	//					// only reset if no other PowerUp of tyep sticky is active
	//					Ball->Sticky = false;
	//					Player->Color = glm::vec3(1.0f);
	//				}
	//			}
	//			else if (powerUp.Type == "pass-through")
	//			{
	//				if (!IsOtherPowerUpActive(this->PowerUps, "pass-through"))
	//				{
	//					// only reset if no other PowerUp of tyep pass-through is active
	//					Ball->PassThrough = false;
	//					Player->Color = glm::vec3(1.0f);
	//				}
	//			}
	//			if (powerUp.Type == "confuse")
	//			{
	//				if (!IsOtherPowerUpActive(this->PowerUps, "confuse"))
	//				{
	//					// only reset if no other PowerUp of tyep confuse is active
	//					Effects->Confuse = false;
	//				}
	//			}
	//			else if (powerUp.Type == "chaos")
	//			{
	//				if (!IsOtherPowerUpActive(this->PowerUps, "chaos"))
	//				{
	//					// only reset if no other PowerUp of tyep chaos is active
	//					Effects->Chaos = false;
	//				}
	//			}
	//		}
	//	}
	//}
	//this->PowerUps.erase(
	//	std::remove_if(
	//		this->PowerUps.begin(),
	//		this->PowerUps.end(),
	//		[](const PowerUp& powerUp){ return powerUp.Destroyed && !powerUp.Activated; }),
	//	this->PowerUps.end());
//}

//void Game::ActivatePowerUp(PowerUp& powerUp)
//{
	//if (powerUp.Type == "speed")
	//{
	//	Ball->Velocity *= 1.2;
	//}
	//else if (powerUp.Type == "sticky")
	//{
	//	Ball->Sticky = true;
	//	Player->Color = glm::vec3(1.0f, 0.5f, 1.0f);
	//}
	//else if (powerUp.Type == "pass-through")
	//{
	//	Ball->PassThrough = true;
	//	Player->Color = glm::vec3(1.0f, 0.5f, 0.5f);
	//}
	//else if (powerUp.Type == "pad-size-increase")
	//{
	//	Player->Size.x += 50;
	//}
	//else if (powerUp.Type == "confuse")
	//{
	//	if (!Effects->Chaos)
	//		Effects->Confuse = true; // only activate if chaos wasn't already activated
	//}
	//else if (powerUp.Type == "chaos")
	//{
	//	if (!Effects->Confuse)
	//		Effects->Chaos = true; // only activate if confuse wasn't already activated
	//}
//}

//bool Game::IsOtherPowerUpActive(std::vector<PowerUp>& powerUps, std::string type)
//{
//	for (const PowerUp& powerUp : powerUps)
//	{
//		if (powerUp.Activated)
//			if (powerUp.Type == type)
//				return true;
//	}
//	return false;
//}
