#ifndef BALL_OBJECT_H
#define BALL_OBJECT_H


#include<glad/gl.h>
#include<glm/glm.hpp>

#include"gameObject.h"
#include"texture.h"

//forward reference
class GameObjectMediator;
class Collilder2D;
class BallCollider2D;


/// <summary>
/// Ball Object holds the state of the Ball object inheriting
/// relevant state data from GameObject. Contains some extra
/// functionality specific to this game's ball object that
/// were too specific for within GameObject alone.
/// </summary>
class BallObject :
    public GameObject
{
    public:
        // Initial velocity of the Ball
        const glm::vec2 INITIAL_BALL_VELOCITY = glm::vec2(100.0f, -350.0f);

        // ball state
        float Radius;
        bool  Stuck;
        bool  Sticky, PassThrough;
        // constructor(s)
        BallObject();
        BallObject(glm::vec2 pos, float radius, glm::vec2 velocity, Texture2D sprite, BallCollider2D* collider, GameObjectMediator& mediator, GameTag myTag = GameTag::BALL);
        // moves the ball, keeping it constrained within the window bounds (except bottom edge); returns new position
        void Move(float dt);
        // resets the ball to original state with given position and velocity
        void      Reset(glm::vec2 position, glm::vec2 velocity);
        void      Update(float dt);
        void DoSpecialOnCollision() override;
};

#endif