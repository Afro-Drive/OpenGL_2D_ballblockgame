#include "brock.h"

#include<gameObject.h>
#include"boxCollider.h"
#include<gameObjectMediator.h>


Brock::Brock()
	:GameObject()
{
}

Brock::Brock(glm::vec2 pos, glm::vec2 size, Texture2D texture, GameObjectMediator& mediator, GameTag myTag, BoxCollider2D* collider, glm::vec3 color, glm::vec2 velocity)
	:GameObject(pos, size, texture, collider, mediator, myTag, color, velocity)
{
}

void Brock::Update(float dt)
{
	collider->Update(dt);
}

void Brock::DoSpecialOnCollision()
{
	// switch sound effects
	this->IsSolid() ?
		this->mediator->getSoundEngine()->play2D("Audio/SE/solid.wav", false)
		:
		this->mediator->getSoundEngine()->play2D("Audio/SE/bleep.mp3", false);
}

