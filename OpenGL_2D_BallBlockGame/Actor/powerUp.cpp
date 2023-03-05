#include"powerUp.h"

#include<tuple>

#include<player.h>
#include<gameObjectMediator.h>
#include"boxCollider.h"
#include<transform.h>

void PowerUp::Update(float dt)
{
	this->transform->Position += this->transform->Velocity * dt;
	this->transform->GetCollider()->transform->Position = this->transform->Position;
}

void PowerUp::DoSpecialOnCollision()
{
	this->mediator->getSoundEngine()->play2D("Audio/SE/powerup.wav", false);
}
