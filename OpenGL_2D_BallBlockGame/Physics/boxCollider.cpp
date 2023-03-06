#include "boxCollider.h"

#include<iostream>
#include<typeinfo>
#include<tuple>

#include"ballCollider.h"
#include"ballObject.h"
#include"player.h"
#include"brock.h"
#include"transform.h"


BoxCollider2D::BoxCollider2D(glm::vec2 pos, glm::vec2 size, GameObject& target, GameObjectMediator& mediator, GameTag myTag)
    :Collider2D(pos, size, target, mediator, myTag)
{
}

Collision BoxCollider2D::CheckCollision(BallCollider2D& other)
{
	return BallCollider2D::CheckCollision(other, *this);
}

Collision BoxCollider2D::DoCollision(BoxCollider2D& other)
{
	return this->CheckCollision(other);
}

Collision BoxCollider2D::DoCollision(BallCollider2D& other)
{
	return this->CheckCollision(other);
}

Collision BoxCollider2D::DoCollision(Collider2D& other)
{
	return other.DoCollision(*this);
}

Collision BoxCollider2D::CheckCollision(BoxCollider2D& other)
{
	// collision x-axis?
	bool collisionX = this->transform->Position.x + this->transform->Size.x >= other.transform->Position.x
		&& other.transform->Position.x + other.transform->Size.x >= this->transform->Position.x;
	// collision y-axis?
	bool collisionY = this->transform->Position.y + this->transform->Size.y >= other.transform->Position.y
		&& other.transform->Position.y + other.transform->Size.y >= this->transform->Position.y;
	bool isCollision = collisionX && collisionY;

	// In this game, when BoxCollider & BoxCollider collide, returns no direction, vector.
	return std::make_tuple(isCollision, Direction::UP, glm::vec2(0.0f));
}
