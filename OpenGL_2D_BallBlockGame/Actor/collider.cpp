#include "collider.h"

#include<typeinfo>
#include<iostream>


Collider2D::Collider2D()
	:GameObject(),
	 target(nullptr)
{
}

Collider2D::Collider2D(glm::vec2 pos, glm::vec2 size, GameObject& target, GameObjectMediator& mediator, GameTag myTag)
	:GameObject(pos, size, Texture2D(), this, mediator, myTag),
	 target(&target)
{
}

Direction Collider2D::VectorDirection(glm::vec2 target)
{
	return Direction::UP;
}

void Collider2D::Update(float dt)
{
	this->Position = target->Position;
}
