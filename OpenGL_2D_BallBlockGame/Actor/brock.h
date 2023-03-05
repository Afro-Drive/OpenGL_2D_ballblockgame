#ifndef BROCK_H
#define BROCK_H

#include<glm/glm.hpp>

#include<texture.h>
#include<gameObject.h>

// forward declare
class BoxCollider2D;
class GameObjectMediator;
class BoxCollider2D;


class Brock :
    public GameObject
{
    public:
        Brock();
        Brock(glm::vec2 pos, glm::vec2 size, Texture2D texture, GameObjectMediator& mediator, GameTag myTag = GameTag::BROCK, BoxCollider2D* collider = nullptr, glm::vec3 color = glm::vec3(1.0f), glm::vec2 velocity = glm::vec2(0.0f));

        void Update(float dt) override;
        bool IsSolid() const;
        void SetIsSolid(bool isSolid);
        bool Destroyed() const;
        void SetDestroyed(const bool destroyed);
        virtual void DoSpecialOnCollision() override;
    protected:
        bool      isSolid;
        bool      destroyed;
};

inline bool Brock::IsSolid() const
{
    return isSolid;
}

inline void Brock::SetIsSolid(bool isSolid)
{
    this->isSolid = isSolid;
}

inline bool Brock::Destroyed() const
{
    return destroyed;
}

inline void Brock::SetDestroyed(const bool destroyed)
{
    this->destroyed = destroyed;
}

#endif // !BROCK_H
