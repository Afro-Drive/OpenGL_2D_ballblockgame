#include "sceneMediator.h"

#include"gameMainScene.h"
#include"titleScene.h"
#include"sceneManager.h"
#include"abstractScene.h"

SceneMediator::SceneMediator(ISoundEngine& soundEngine)
    :soundEngine(&soundEngine)
{
}

SceneMediator::~SceneMediator()
{
}

void SceneMediator::Share()
{
    GameMainScene* gameMainScene = static_cast<GameMainScene*>(
        SceneManager::GetInstance()->GetSceneMap()[SceneName::GAME_MAIN]);
    if (!gameMainScene->IsLoadedStage())
        gameMainScene->LoadStageData();

    this->stages = gameMainScene->GetStageVector();
}

std::vector<GameLevel*> SceneMediator::ShareStages()
{
    if (this->stages.empty())
        this->Share(); // load stage vector data from GameMainScene

    return stages;
}

unsigned int SceneMediator::ShareLevel()
{
    TitleScene* titleScene = static_cast<TitleScene*>(SceneManager::GetInstance()->GetSceneMap()[SceneName::TITLE]);
    return titleScene->GetLevel();
}

unsigned int SceneMediator::ShareLives()
{
    GameMainScene* gameMainScene = static_cast<GameMainScene*>(
        SceneManager::GetInstance()->GetSceneMap()[SceneName::GAME_MAIN]);
    return gameMainScene->GetLives();
}
