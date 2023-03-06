#include "gameObject.h"

#include<gameObjectMediator.h>
#include<spriteRenderer.h>
#include<collider.h>
#include<transform.h>


GameObject::GameObject(glm::vec2 pos, glm::vec2 size, Texture2D sprite, Collider2D* collider, GameObjectMediator& mediator, GameTag myTag, glm::vec3 color, glm::vec2 velocity)
	: Sprite(sprite), mediator(&mediator), myTag(myTag)
{
	transform = new Transform(pos, size, collider, velocity, 0.0f, color);
}

GameObject::GameObject(Transform& transform, Texture2D sprite, GameObjectMediator& mediator, GameTag myTag)
	:transform(&transform), Sprite(sprite), mediator(&mediator), myTag(myTag)
{ }

GameObject::~GameObject()
{
	delete this->transform;
}

void GameObject::Draw(SpriteRenderer& renderer)
{
	renderer.DrawSprite(
		this->Sprite,
		this->transform->Position,
		this->transform->Size,
		this->transform->Rotation,
		this->transform->Color);
}

void GameObject::Update(float dt)
{
}

void GameObject::DoSpecialOnCollision()
{
}
