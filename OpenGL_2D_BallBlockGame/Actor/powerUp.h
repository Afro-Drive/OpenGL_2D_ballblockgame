#ifndef POWER_UP_H
#define POWER_UP_H

#include<glm/glm.hpp>

#include <brock.h>
#include<texture.h>

// forward declare
class Player;
class GameObjectMediator;
class BoxCollider2D;
class Collider2D;

// The size of a PowerUp block
const glm::vec2 SIZE(60.0f, 20.0f);
// Velocity a PowerUp block has when spawned
const glm::vec2 VELOCITY(0.0f, 150.0f);

enum class PowerUpType
{
    STICKY,
    PASS_THROUGH,
    CONFUSE,
    CHAOS,
    SPEED,
    PAD_SIZE_INCREASE,
};


/// <summary>
/// PowerUp inherits its state and rendering functions from
/// GameObject but also holds extra information to state its
/// active duration and whether it is activated or not.
/// The type of PowerUp is stored as a string.
/// </summary>
class PowerUp :
    public Brock
{
    public:
        // powerup state
        PowerUpType Type;
        float       Duration;
        bool        Activated;
        // constructor
        PowerUp(PowerUpType type ,glm::vec3 color, float duration, glm::vec2 position, Texture2D texture, GameObjectMediator& mediator, BoxCollider2D* collider, GameTag myTag = GameTag::NONE)
            :Brock(position, SIZE, texture, mediator, myTag, collider, color, VELOCITY),
             Type(type), Duration(duration), Activated()
        { }
        void Update(float dt);
        void DoSpecialOnCollision() override;
};

#endif