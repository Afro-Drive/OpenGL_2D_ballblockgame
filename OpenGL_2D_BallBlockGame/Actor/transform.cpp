#include "transform.h"

glm::vec2 Transform::Position()
{
    return this->position;
}

glm::vec2 Transform::Size()
{
    return this->size;
}

glm::vec2 Transform::Velocity()
{
    return this->velocity;
}

glm::vec3 Transform::Color()
{
    return this->color;
}

float Transform::Rotation()
{
    return this->rotation;
}
