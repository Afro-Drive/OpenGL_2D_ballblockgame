#ifndef BALL_COLLIDER_H
#define BALL_COLLIDER_H

#include<glm/glm.hpp>

#include "collider.h"

// forward reference
class BoxCollider2D;
class Brock;
class BallCollider2D;
class Player;
class GameObject;
class GameObjectMediator;


class BallCollider2D :
    public Collider2D
{
    public:
        BallCollider2D();
        BallCollider2D(glm::vec2 pos, GameObject& target, float radius, GameObjectMediator& mediator);

        float Radius();
        static Collision CheckCollision(BallCollider2D& one, BoxCollider2D& two);
        Direction VectorDirection(glm::vec2 target) override;
        Collision DoCollision(Collider2D& other) override;
        Collision CheckCollision(BoxCollider2D& other) override;
        Collision DoCollision(BoxCollider2D& other) override;
        Collision CheckCollision(BallCollider2D& other) override;
        Collision DoCollision(BallCollider2D& other) override;

    private:
        float radius;
        void CalcPhysicsByPlayer(Player& other);
        void CalcPhysicsByBrock(Brock& other, Collision preResult);
};

inline float BallCollider2D::Radius()
{
    return radius;
}
#endif // !BALL_COLLIDER_H
