#ifndef END_SCENE_H
#define END_SCENE_H


#include"abstractScene.h"

class EndScene :
    public AbstractScene
{
    public:
        EndScene(unsigned int width, unsigned int height, ISoundEngine* soundEngine, SceneMediator* sceneMediator);
        ~EndScene();

        virtual void Init() override;
        virtual void Update(float dt) override;
        virtual void Render(SpriteRenderer* renderer) override;
        virtual void ProcessInput(float dt) override;
};

#endif // !END_SCENE_H
