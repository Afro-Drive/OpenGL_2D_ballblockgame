#ifndef TITLE_SCENE_H
#define TITLE_SCENE_H


#include "abstractScene.h"


class TitleScene :
    public AbstractScene
{
    public:
        TitleScene(unsigned int width, unsigned int height, ISoundEngine* soundEngine, SceneMediator* sceneMediator);

        virtual void Init() override;
        virtual void Update(float dt) override;
        virtual void Render(SpriteRenderer* renderer) override;
        virtual void ProcessInput(float dt) override;
        unsigned int GetLevel();

    private:
        unsigned int level;
};

#endif // !TITLE_SCENE_H
