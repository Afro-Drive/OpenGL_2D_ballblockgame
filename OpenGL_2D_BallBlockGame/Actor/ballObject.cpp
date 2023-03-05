#include "ballObject.h"

#include<typeinfo>
#include<tuple>

#include"brock.h"
#include"ballCollider.h"
#include<player.h>
#include<gameObjectMediator.h>
#include<transform.h>


BallObject::BallObject(glm::vec2 pos, float radius, glm::vec2 velocity, Texture2D sprite, BallCollider2D* collider, GameObjectMediator& mediator, GameTag myTag)
	: GameObject(pos, glm::vec2(radius * 2.0f, radius * 2.0f), sprite, collider, mediator, myTag, glm::vec3(1.0f), velocity),
	  Radius(radius), Stuck(true), Sticky(false), PassThrough(false) { }

void BallObject::Move(float dt)
{
	// if stuck to player board, early guard
	if (this->Stuck)
		return;

	glm::uvec2 fieldSize = this->mediator->GetScreenSize();

	// move the ball
	this->transform->Position += transform->Velocity * dt;
	// then check if outside window bounds and if so, reverse velocity and restore at correct position
	if (this->transform->Position.x <= 0.0f)
	{
		this->transform->Velocity.x = -this->transform->Velocity.x;
		this->transform->Position.x = 0.0f;
	}
	else if (this->transform->Position.x + this->transform->Size.x >= fieldSize.x)
	{
		this->transform->Velocity.x = -this->transform->Velocity.x;
		this->transform->Position.x = fieldSize.x - this->transform->Size.x;
	}
	if (this->transform->Position.y <= 0.0f)
	{
		this->transform->Velocity.y = -this->transform->Velocity.y;
		this->transform->Position.y = 0.0f;
	}
}

// resets the ball to initial Stuck Position (if ball is outside window bounds)
void BallObject::Reset(glm::vec2 position, glm::vec2 velocity)
{
	this->transform->Position = position;
	this->transform->Velocity = velocity;
	this->Stuck = true;
	this->Sticky = false;
	this->PassThrough = false;
}

void BallObject::Update(float dt)
{	
	Move(dt);
	this->transform->GetCollider()->Update(dt);
}

void BallObject::DoSpecialOnCollision()
{
}