#ifndef TRANSFORM_H
#define TRANSFORM_H

#include<glm/glm.hpp>

#include<gameObjectMediator.h>


class Transform
{
	public:

		glm::vec2 Position();
		glm::vec2 Size();
		glm::vec2 Velocity();
		glm::vec3 Color();
		float Rotation();
		// update state
		virtual void Update(float dt);

	private:
		glm::vec2 position, size, velocity;
		glm::vec3 color;
		float rotation;
		GameObjectMediator* mediator;
};

#endif // !TRANSFORM_H
