#include "sceneMediator.h"

#include"gameMainScene.h"
#include"titleScene.h"
#include"sceneManager.h"

void SceneMediator::Share()
{
    GameMainScene* gameMainScene = static_cast<GameMainScene*>(
        SceneManager::GetInstance()->GetSceneMap()[SceneName::GAME_MAIN]);
    if (!gameMainScene->isLoadedStage())
        gameMainScene->LoadStageData();

    this->stages = gameMainScene->getStageVector();
}

std::vector<GameLevel> SceneMediator::ShareStages()
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
