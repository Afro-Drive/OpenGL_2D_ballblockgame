#ifndef END_SCENE_H
#define END_SCENE_H


#include"abstractScene.h"

class EndScene :
    public AbstractScene
{
    public:
        EndScene(unsigned int width, unsigned int height, SceneMediator* sceneMediator, UIMediator* uIMediator);
        ~EndScene();

        void Init() override;
        void Update(float dt) override;
        void Render(SpriteRenderer* renderer) override;
        void ProcessInput(float dt) override;
    private:
        bool isComplete;
};

#endif // !END_SCENE_H
