#ifndef COLLIDER_H
#define COLLIDER_H

#include<glm/glm.hpp>
#include<tuple>

#include<gameObject.h>

// forward reference
class BoxCollider2D;
class BallCollider2D;
class GameObjectMediator;
class Transform;

enum Direction {
    UP,
    RIGHT,
    DOWN,
    LEFT
};

typedef std::tuple<bool, Direction, glm::vec2> Collision;


class Collider2D :
    public GameObject
{
    public:
        Collider2D(glm::vec2 pos, glm::vec2 size, GameObject& target, GameObjectMediator& mediator, GameTag myTag = GameTag::NONE);

        /// <summary>
        /// Template method about collision
        /// In this function, other overload CheckCollision functions are performed.
        /// </summary>
        /// <param name="other"></param>
        /// <returns></returns>
        virtual Collision DoCollision(Collider2D& other) = 0;        
        virtual Collision DoCollision(BoxCollider2D& other) = 0;
        virtual Collision DoCollision(BallCollider2D& other) = 0;

        void Update(float dt) override;

        void SetTarget(GameObject& target);
        GameObject* GetTarget();

    protected:
        /// <summary>
        /// Following object. This class follows this member.
        /// If this member collides other one, this class calculates about physics value.
        /// </summary>
        GameObject* target;
        
        virtual Collision CheckCollision(BoxCollider2D& other) = 0;
        virtual Collision CheckCollision(BallCollider2D& other) = 0;
        /// <summary>
        /// Calcuration direction of vector from other target position
        /// </summary>
        /// <param name="target"></param>
        /// <returns></returns>
        virtual Direction VectorDirection(glm::vec2 target);
};

inline void Collider2D::SetTarget(GameObject& target)
{
    this->target = &target;
}

inline GameObject* Collider2D::GetTarget()
{
    return this->target;
}

#endif // !COLLIDER_2D_H
