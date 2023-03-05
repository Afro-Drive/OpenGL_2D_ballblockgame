#ifndef TRANSFORM_H
#define TRANSFORM_H

#include<glm/glm.hpp>

class Collider2D;


class Transform
{
	public:
		Transform(glm::vec2 position, glm::vec2 size, Collider2D* collider ,glm::vec2 velocity = glm::vec2(0.0f, 0.0f), float rotation = 0.0f, glm::vec3 color = glm::vec3(1.0f));
		~Transform();
		// Object States
		glm::vec2 Position, Size, Velocity;
		float Rotation;
		glm::vec3 Color;
		// update state
		void Update(float dt);
		Collider2D* GetCollider();
		void SetCollider(Collider2D& collider);

	private:
		Collider2D* collider;
};

inline Collider2D* Transform::GetCollider()
{
	return this->collider;
}

inline void Transform::SetCollider(Collider2D& collider)
{
	this->collider = &collider;
}

inline void Transform::Update(float dt)
{

}

#endif // !TRANSFORM_H
