#include "sceneManager.h"

#include<iostream>

#include<spriteRenderer.h>
#include<textRenderer.h>

SceneManager* SceneManager::Instance = nullptr;


SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
	// delete(and execute destructor) each scene pointer
	for (auto scenePair : sceneMap)
		delete scenePair.second;

	// Clear all element of map
	sceneMap.clear();
}

SceneManager* SceneManager::GetInstance()
{
	if (Instance == nullptr)
		Instance = new SceneManager();

	return Instance;
}

void SceneManager::DestroySelf()
{
	delete Instance;
}

std::map<SceneName, AbstractScene*> SceneManager::GetSceneMap()
{
	return sceneMap;
}

void SceneManager::ChangeScene(SceneName nextScene)
{
	// scene is not found, do nothing
	AbstractScene* next = sceneMap[nextScene];
	if (next == nullptr) {
		std::cout << "Unable to change scene because there is not scene No." << (unsigned int)nextScene << " in Scene Map !" << std::endl;
		return;
	}

	prevSceneName = currentSceneName;

	next->Init();
	currentScene = next;
	currentSceneName = nextScene;
}



void SceneManager::RunScene(SpriteRenderer& renderer, float dt)
{
	currentScene->ProcessInput(dt);
	currentScene->Update(dt);
	currentScene->Render(&renderer);

	if (currentScene->GetIsEnd())
		this->ChangeScene(currentScene->GetNextScene());
}

void SceneManager::AddScene(SceneName sceneName, AbstractScene& newScene)
{
	sceneMap[sceneName] = &newScene;
	currentScene = &newScene;
	currentSceneName = sceneName;
}

