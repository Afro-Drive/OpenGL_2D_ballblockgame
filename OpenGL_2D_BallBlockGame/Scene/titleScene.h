#ifndef TITLE_SCENE_H
#define TITLE_SCENE_H


#include "abstractScene.h"


class TitleScene :
    public AbstractScene
{
    public:
        TitleScene(unsigned int width, unsigned int height, SceneMediator* sceneMediator);

        void Init() override;
        void Update(float dt) override;
        void Render(SpriteRenderer* renderer) override;
        void ProcessInput(float dt) override;
        unsigned int GetLevel();

    private:
        unsigned int level;
};

#endif // !TITLE_SCENE_H
