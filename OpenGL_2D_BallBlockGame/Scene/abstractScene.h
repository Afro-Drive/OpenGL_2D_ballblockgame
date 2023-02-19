#ifndef ABSTRACT_SCENE_H
#define ABSTRACT_SCENE_H

#include "iScene.h"

#include<GLFW/glfw3.h>
#include<irrKlang/irrKlang.h>
using namespace irrklang;
#pragma comment(lib, "irrKlang.lib") // link with irrKlang.dll

#include<input.h>
#include<particleGenerator.h>
#include<postProcessor.h>
#include<textRenderer.h>
#include"SceneMediator.h"

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
        AbstractScene(unsigned width, unsigned int height, ISoundEngine* soundEngine, SceneMediator* sceneMediator);
        ~AbstractScene();
        // IScene implements(but not difined in this class)
        virtual void Init() override = 0;
        virtual void Update(float dt) override = 0;
        virtual void Render(SpriteRenderer* renderer) override = 0;
        virtual void ProcessInput(float dt) override = 0;

        bool GetIsEnd();
        SceneName GetNextScene();

    protected:
        unsigned int width, height;
        bool isEnd;
        SceneName nextScene;
        ISoundEngine* soundEngine;
        TextRenderer* text;
        PostProcessor* effects;
        SceneMediator* sceneMediator;
};

#endif // !ABSTRACT_SCENE_H
