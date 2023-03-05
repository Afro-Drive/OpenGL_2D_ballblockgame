#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include<glad/gl.h>
#include<glm/glm.hpp>

#include<texture.h>

// forward declare
class GameObjectMediator;
class SpriteRenderer;
class Collider2D;

enum GameTag
{
	NONE,
	PLAYER,
	BALL,
	BROCK
};

/// <summary>
/// Container object for holding all state relevant for a single
/// game object entity. Each object in the game likely needs the 
/// minimal of state as described within GameObject
/// </summary>
class GameObject
{
	public:
		// object state
		glm::vec2 Position, Size, Velocity;
		glm::vec3 Color;
		float     Rotation;
		bool      IsSolid;
		bool      Destroyed;
		// render state
		Texture2D Sprite;
		// constructor(s)
		GameObject();
		GameObject(glm::vec2 pos, glm::vec2 size, Texture2D sprite, Collider2D* collider, GameObjectMediator& mediator, GameTag myTag, glm::vec3 color = glm::vec3(1.0f), glm::vec2 velocity = glm::vec2(0.0f, 0.0f));
		// draw sprite
		virtual void Draw(SpriteRenderer& renderer);
		// update state
		virtual void Update(float dt);
		/// <summary>
		/// Specific process when own collider detects.
		/// This process performs for own special(audio, color...etc)
		/// </summary>
		virtual void DoSpecialOnCollision();
		Collider2D* GetCollider();
		void SetCollider(Collider2D& collider);
		GameTag GetMyTag();
		void SetMyTag(GameTag myTag);

	protected:
		GameObjectMediator* mediator;
		Collider2D* collider;
		GameTag myTag;
};

inline Collider2D* GameObject::GetCollider()
{
	return this->collider;
}

inline void GameObject::SetCollider(Collider2D& collider)
{
	this->collider = &collider;
}

inline GameTag GameObject::GetMyTag()
{
	return this->myTag;
}

inline void GameObject::SetMyTag(GameTag myTag)
{
	this->myTag = myTag;
}

#endif