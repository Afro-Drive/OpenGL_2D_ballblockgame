#include "ballCollider.h"

#include<tuple>
#include<iostream>
#include<typeinfo>

#include"boxCollider.h"
#include"player.h"
#include"ballObject.h"
#include"brock.h"
#include"gameObjectMediator.h"

BallCollider2D::BallCollider2D()
    :Collider2D(),
	 radius(0.0f)
{
}

BallCollider2D::BallCollider2D(glm::vec2 pos, GameObject& target, float radius, GameObjectMediator& mediator)
    :Collider2D(pos, glm::vec2(0.0f), target, mediator),
	 radius(radius)
{
}

Collision BallCollider2D::CheckCollision(BallCollider2D& one, BoxCollider2D& two)
{
	// get center point circle first
	glm::vec2 center(one.Position + one.Radius());
	// calculate AABB info (center, half-extents)
	glm::vec2 aabb_half_extents(two.Size.x / 2.0f, two.Size.y / 2.0f);
	glm::vec2 aabb_center(
		two.Position.x + aabb_half_extents.x,
		two.Position.y + aabb_half_extents.y);

	// get difference vector between both centers
	glm::vec2 difference = center - aabb_center;
	glm::vec2 clamped = glm::clamp(difference, -aabb_half_extents, aabb_half_extents);
	// add clamped value to AABB_center and we get the value of box closest to circle
	glm::vec2 closest = aabb_center + clamped;

	// retrieve vector between center circle and clsoest point AABB and check if length <= radius
	difference = closest - center;
	bool isCollision = glm::length(difference) <= one.Radius();
	
	return std::make_tuple(isCollision, Direction::UP, difference);
}

Collision BallCollider2D::CheckCollision(BoxCollider2D& other)
{
	Collision result = this->CheckCollision(*this, other);
	if (std::get<0>(result))
		// calc direction based on collision result
		std::get<1>(result) = VectorDirection(std::get<2>(result));
	
	return result;
}

Collision BallCollider2D::DoCollision(BoxCollider2D& other)
{
	Collision collision = this->CheckCollision(other);

	if (!std::get<0>(collision)) // if collision is false, return early guard
		return collision;

	switch (other.GetTarget()->GetMyTag())
	{
	case GameTag::BROCK:
	{// proceed target's specific function
		Brock& brock = static_cast<Brock&>(*(other.GetTarget()));
		brock.DoSpecialOnCollision();
		this->CalcPhysicsByBrock(brock, collision);
		break;
	}
	case GameTag::PLAYER:
	{
		Player& player = static_cast<Player&>(*(other.GetTarget()));
		player.DoSpecialOnCollision();
		this->CalcPhysicsByPlayer(player);
		break;
	}
	}
	return collision;
}

Collision BallCollider2D::CheckCollision(BallCollider2D& other)
{
	return Collision();
}

Collision BallCollider2D::DoCollision(BallCollider2D& other)
{
	return Collision();
}

void BallCollider2D::CalcPhysicsByPlayer(Player& other)
{
	BallObject* target = static_cast<BallObject*>(this->target);

	// check where it hit the board, and change velocity based on where it hit the board
	float centerBoard = other.Position.x + other.Size.x / 2.0f;
	float distance = (this->Position.x + this->radius) - centerBoard;
	float percentage = distance / (other.Size.x / 2.0f);

	// then move accordingly
	float strength = 2.0f;
	glm::vec2 oldVelocity = target->Velocity;
	target->Velocity.x = target->INITIAL_BALL_VELOCITY.x * percentage * strength;
	target->Velocity = glm::normalize(target->Velocity) * glm::length(oldVelocity);
	target->Velocity.y = -1.0f * abs(target->Velocity.y);

	// if Sticky powerup is activated, also stick ball to paddle once new velocity vectors were calculated
	target->Stuck = (target->Sticky);
}

void BallCollider2D::CalcPhysicsByBrock(Brock& other, Collision preResult)
{
	BallObject* target = static_cast<BallObject*>(this->target);
	if (target->PassThrough) // early guard
		return;

	// collision resolution
	Direction dir = std::get<1>(preResult);
	glm::vec2 diff_vector = std::get<2>(preResult);
	float penetration;
	switch (dir)
	{
		// horizontal collision
	case LEFT:
	case RIGHT:
		target->Velocity.x = -target->Velocity.x; // reverse horizontal velocity
		// relocate
		penetration = this->radius - std::abs(diff_vector.x);
		dir == LEFT ?
			target->Position.x += penetration // move ball to right
			:
			target->Position.x -= penetration; // move ball to left
		break;

		// vertical collision
	case UP:
	case DOWN:
		target->Velocity.y = -target->Velocity.y; // reverse vertical velocity
		// relocate
		penetration = this->radius - std::abs(diff_vector.y);
		dir == UP ?
			target->Position.y -= penetration // move ball back up
			:
			target->Position.y += penetration; // move ball back down
		break;
	}
}

Collision BallCollider2D::DoCollision(Collider2D& other)
{
	return other.GetCollider()->DoCollision(*this);
}

Direction BallCollider2D::VectorDirection(glm::vec2 target)
{
	glm::vec2 compass[] = {
	glm::vec2(0.0f, 1.0f),  // up
	glm::vec2(1.0f, 0.0f),  // right
	glm::vec2(0.0f, -1.0f), // down
	glm::vec2(-1.0f, 0.0f)  // left
	};
	float max = 0.0f;
	unsigned int best_match = -1;
	for (unsigned int i = 0; i < 4; i++)
	{
		float dot_product = glm::dot(glm::normalize(target), compass[i]);
		if (dot_product > max)
		{
			max = dot_product;
			best_match = i;
		}
	}
	return (Direction)best_match;
}
