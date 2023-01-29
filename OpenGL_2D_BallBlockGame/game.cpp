#include "game.h"

#include<glm/glm.hpp>

#include"SpriteRenderer.h"
#include"resourceManager.h"


SpriteRenderer* Renderer;


Game::Game(unsigned int width, unsigned int height)
	:State(GAME_ACTIVE), Keys(), Width(width), Height(height)
{

}

Game::~Game()
{

}

void Game::Init()
{
	// load shaders
	ResourceManager::LoadShader("sprite.vert", "sprite.frag", nullptr, "sprite");
	// configure shaders
	glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(this->Width),
		static_cast<float>(this->Height), 0.0f, -1.0f, 1.0f);
	ResourceManager::GetShader("sprite").Use().SetInteger("image", 0);
	ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);
	// set render-specific controls
	Shader sprite = ResourceManager::GetShader("sprite");
	Renderer = new SpriteRenderer(sprite);
	// load textures
	ResourceManager::LoadTexture("pop_cat.png", true, "cat");
}

void Game::ProcessInput(float dt)
{

}

void Game::Update(float dt)
{
}

void Game::Render()
{
	Texture2D catTex = ResourceManager::GetTexture("cat");
	Renderer->DrawSprite(catTex,
		glm::vec2(100.0f, 100.0f), glm::vec2(512.0f, 512.0f), 45.0f, glm::vec3(1.0f, 1.0f, 1.0f));
}