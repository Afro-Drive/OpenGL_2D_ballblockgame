#ifndef PLAYER_H
#define PLAYER_H

#include <gameObject.h>

// forward reference
class BoxCollider2D;
class BallObject;


class Player :
    public GameObject
{
    public:
        Player(glm::vec2 pos, glm::vec2 size, Texture2D sprite, GameObjectMediator& mediator, GameTag myTag = GameTag::PLAYER, BoxCollider2D* collider = nullptr, glm::vec3 color = glm::vec3(1.0f), glm::vec2 velocity = glm::vec2(0.0f));
        ~Player();

        void Draw(SpriteRenderer& renderer);
        void Update(float dt);
        void DoSpecialOnCollision() override;
        void SetTargetBall(BallObject* ball);
    private:
        BallObject* ball;
};

inline void Player::SetTargetBall(BallObject* ball)
{
    this->ball = ball;
}

#endif // !PLAYER_H
