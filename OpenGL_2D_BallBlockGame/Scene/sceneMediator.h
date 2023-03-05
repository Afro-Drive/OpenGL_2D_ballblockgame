#ifndef SCENE_MEDIATOR_H
#define SCENE_MEDIATOR_H

#include<vector>

#include<gameLevel.h>
#include<irrKlang/irrKlang.h>
using namespace irrklang;


class SceneMediator
{
    public:
        SceneMediator() { };
        SceneMediator(ISoundEngine& soundEngine);
        ~SceneMediator();

        virtual void Share();
        /// <summary>
        /// Be shared GameLevel vector data from GameMainScene
        /// </summary>
        /// <returns></returns>
        std::vector<GameLevel*> ShareStages();
        unsigned int ShareLevel();
        ISoundEngine* getSoundEngine();

    private:
        std::vector<GameLevel*> stages;
        ISoundEngine* soundEngine;
};

#endif // !SCENE_MEDIATOR_H