#ifndef GAME_MAIN_SCENE_H
#define GAME_MAIN_SCENE_H


#include<vector>

#include"abstractScene.h"
#include<gameLevel.h>
#include<brock.h>


// forward declare
class GameObjectMediator;
class SceneMediator;
class BallObject;
class Player;


class GameMainScene :
    public AbstractScene
{
    public:
        GameMainScene(unsigned int width, unsigned int height, SceneMediator* sceneMediator, UIMediator* uiMediator);
        ~GameMainScene();

        void Init() override;
        void Update(float dt) override;
        void Render(SpriteRenderer* renderer) override;
        void ProcessInput(float dt) override;

        void ResetPlayer();
        void ResetLevel();
        bool IsLoadedStage();
        bool LoadStageData();
        std::vector<GameLevel*> GetStageVector();
        std::vector<Brock*> GetBricks();
        BallObject* GetBallObject();
        Player* GetPlayerObject();
        unsigned int GetLives();

    private:
        unsigned int level;
        std::vector<GameLevel*> stageVector;
        bool isLoadedStage;
        unsigned int lives;
        GameObjectMediator* gameObjectMediator;
        BallObject* Ball;
        Player* player;
};

inline std::vector<GameLevel*> GameMainScene::GetStageVector()
{
    return stageVector;
}

inline bool GameMainScene::IsLoadedStage()
{
    return isLoadedStage;
}

inline std::vector<Brock*> GameMainScene::GetBricks()
{
    return this->stageVector[this->level]->Bricks;
}

inline BallObject* GameMainScene::GetBallObject()
{
    return this->Ball;
}

inline Player* GameMainScene::GetPlayerObject()
{
    return this->player;
}

inline unsigned int GameMainScene::GetLives()
{
    return this->lives;
}

#endif // !GAME_MAIN_SCENE_H
