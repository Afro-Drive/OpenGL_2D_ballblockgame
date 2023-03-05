#include "gameObject.h"

#include<gameObjectMediator.h>
#include<spriteRenderer.h>
#include"Actor/collider.h"


GameObject::GameObject()
	: Position(0.0f, 0.0f), Size(1.0f, 1.0f), Velocity(0.0f), Color(1.0f), Rotation(0.0f), Sprite(), collider(), mediator(), myTag(GameTag::NONE) { }

GameObject::GameObject(glm::vec2 pos, glm::vec2 size, Texture2D sprite, Collider2D* collider, GameObjectMediator& mediator, GameTag myTag, glm::vec3 color, glm::vec2 velocity)
	: Position(pos), Size(size), Velocity(velocity), Color(color), Rotation(0.0f), Sprite(sprite), collider(collider), mediator(&mediator), myTag(myTag) { }

void GameObject::Draw(SpriteRenderer& renderer)
{
	renderer.DrawSprite(this->Sprite, this->Position, this->Size, this->Rotation, this->Color);
}

void GameObject::Update(float dt)
{
}

void GameObject::DoSpecialOnCollision()
{
}
