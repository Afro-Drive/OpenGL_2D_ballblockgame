#ifndef I_SCENE_H
#define I_SCENE_H


#include<spriteRendererh.h>

class IScene
{
    public:
        virtual ~IScene() {};

        virtual void Init() = 0;
        // scene main loop related
        virtual void Update(float dt) = 0;
        virtual void Render(SpriteRenderer* renderer) = 0;
        virtual void ProcessInput(float dt) = 0;
};

#endif // !I_SCENE_H
