#ifndef BOX_COLLIDER_H
#define BOX_COLLIDER_H


#include "collider.h"

#include"boxCollider.h"
#include"ballCollider.h"

// forward reference
class GameObject;
class BallCollider2D;
class GameObjectMediator;


class BoxCollider2D :
    public Collider2D
{
    public:
        BoxCollider2D(glm::vec2 pos, glm::vec2 size, GameObject& target, GameObjectMediator& mediator, GameTag myTag = GameTag::NONE);
        Collision DoCollision(Collider2D& other) override;
        Collision DoCollision(BallCollider2D& other) override;
        Collision DoCollision(BoxCollider2D& other) override;

    protected:
        /// <summary>
        /// Check collision based AABB(axis-aligned bounding box)
        /// </summary>
        /// <param name="other"></param>
        /// <returns></returns>
        Collision CheckCollision(BoxCollider2D& other) override;
        
        /// <summary>
        /// Check collision based AABB(overload)
        /// </summary>
        /// <param name="other"></param>
        /// <returns></returns>
        Collision CheckCollision(BallCollider2D& other) override;
};

#endif // !BOX_COLLIDER_2D_H
