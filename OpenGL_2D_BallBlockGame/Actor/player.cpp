#include "player.h"

#include<vector>
#include<typeinfo>
#include<tuple>

#include<input.h>
#include<screenDesc.h>
#include"ballObject.h"
#include"boxCollider.h"
#include"powerUp.h"
#include<gameObjectMediator.h>


const float BASE_VELOCITY(500.0f);

Player::Player(glm::vec2 pos, glm::vec2 size, Texture2D sprite, GameObjectMediator& mediator, GameTag myTag, BoxCollider2D* collider, glm::vec3 color, glm::vec2 velocity)
	:GameObject(pos, size, sprite, collider, mediator, myTag, color, velocity),
	 ball(static_cast<BallObject*>(this->mediator->SurveyActiveGameObject(GameTag::BALL)))
{ }

Player::~Player()
{
	delete collider;
}

void Player::Draw(SpriteRenderer& renderer)
{
	GameObject::Draw(renderer);
}

void Player::Update(float dt)
{
	float velocity = BASE_VELOCITY * dt;

	if(Input::Keys[GLFW_KEY_A])
	{
		if (this->Position.x >= 0.0f)
		{
			this->Position.x -= velocity;
			if (ball->Stuck)
				ball->Position.x -= velocity;
		}
	}
	if (Input::Keys[GLFW_KEY_D])
	{
		if (this->Position.x <= ScreenDesc::WIDTH - this->Size.x)
		{
			this->Position.x += velocity;
			if (ball->Stuck)
				ball->Position.x += velocity;
		}
	}
	if (Input::Keys[GLFW_KEY_SPACE])
	{
		ball->Stuck = false;
		ball->Sticky = false;
	}

	this->collider->Update(dt);
}

void Player::DoSpecialOnCollision()
{
	this->mediator->getSoundEngine()->play2D("Audio/SE/bleep.wav", false);
}
