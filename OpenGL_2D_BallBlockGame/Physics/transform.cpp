#include "transform.h"

#include<collider.h>


Transform::Transform(glm::vec2 position, glm::vec2 size, Collider2D* collider, glm::vec2 velocity, float rotation, glm::vec3 color)
	:Position(position), Size(size), collider(collider), Velocity(velocity), Rotation(rotation), Color(color)
{
}

Transform::~Transform()
{
}
