#include"powerUp.h"

#include<tuple>

#include<player.h>
#include<gameObjectMediator.h>
#include"boxCollider.h"

void PowerUp::Update(float dt)
{
	this->collider->Position = this->Position;
	this->Position += this->Velocity * dt;
}

void PowerUp::DoSpecialOnCollision()
{
	this->mediator->getSoundEngine()->play2D("Audio/SE/powerup.wav", false);
}
