#ifndef ABSTRACT_SCENE_H
#define ABSTRACT_SCENE_H

#include "iScene.h"

#include<GLFW/glfw3.h>
#include<irrKlang/irrKlang.h>
using namespace irrklang;
#pragma comment(lib, "irrKlang.lib") // link with irrKlang.dll

// forward declare
class SceneMediator;
class SpriteRenderer;
class TextRenderer;
class PostProcessor;
class UIMediator;

enum class SceneName
{
    TITLE,
    GAME_MAIN,
    END,
};

class AbstractScene :
    public IScene
{
    public:
        AbstractScene(unsigned width, unsigned int height, SceneMediator* sceneMediator, UIMediator* uiMediator);
        ~AbstractScene();
        // IScene implements(but not difined in this class)
        virtual void Init() override = 0;
        virtual void Update(float dt) override = 0;
        virtual void Render(SpriteRenderer* renderer) override = 0;
        virtual void ProcessInput(float dt) override = 0;

        bool GetIsEnd();
        SceneName GetNextScene();
        glm::uvec2 GetSceneSize();

    protected:
        unsigned int width, height;
        bool isEnd;
        SceneName nextScene;
        TextRenderer* text;
        PostProcessor* effects;
        SceneMediator* sceneMediator;
        UIMediator* uiMediator;
};

inline bool AbstractScene::GetIsEnd()
{
    return isEnd;
}

inline SceneName AbstractScene::GetNextScene()
{
    return nextScene;
}

inline glm::uvec2 AbstractScene::GetSceneSize()
{
    return glm::uvec2(this->width, this->height);
}

#endif // !ABSTRACT_SCENE_H
