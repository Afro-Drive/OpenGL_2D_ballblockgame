#ifndef SCENE_MEDIATOR_H
#define SCENE_MEDIATOR_H

#include<vector>

#include"../gameLevel.h"

class SceneMediator
{
    public:
        SceneMediator() { };
        virtual void Share();
        /// <summary>
        /// Be shared GameLevel vector data from GameMainScene
        /// </summary>
        /// <returns></returns>
        std::vector<GameLevel> ShareStages();
        unsigned int ShareLevel();

    private:
        std::vector<GameLevel> stages;
};

#endif // !SCENE_MEDIATOR_H
