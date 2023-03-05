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
#include<transform.h>


const float BASE_VELOCITY(500.0f);

Player::Player(glm::vec2 pos, glm::vec2 size, Texture2D sprite, GameObjectMediator& mediator, GameTag myTag, BoxCollider2D* collider, glm::vec3 color, glm::vec2 velocity)
	:GameObject(pos, size, sprite, collider, mediator, myTag, color, velocity),
	 ball(static_cast<BallObject*>(this->mediator->SurveyActiveGameObject(GameTag::BALL)))
{ }

Player::~Player()
{
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
		if (this->transform->Position.x >= 0.0f)
		{
			this->transform->Position.x -= velocity;
			if (ball->Stuck)
				ball->transform->Position.x -= velocity;
		}
	}
	if (Input::Keys[GLFW_KEY_D])
	{
		if (this->transform->Position.x <= ScreenDesc::WIDTH - this->transform->Size.x)
		{
			this->transform->Position.x += velocity;
			if (ball->Stuck)
				ball->transform->Position.x += velocity;
		}
	}
	if (Input::Keys[GLFW_KEY_SPACE])
	{
		ball->Stuck = false;
		ball->Sticky = false;
	}

	this->transform->GetCollider()->Update(dt);
}

void Player::DoSpecialOnCollision()
{
	this->mediator->getSoundEngine()->play2D("Audio/SE/bleep.wav", false);
}
