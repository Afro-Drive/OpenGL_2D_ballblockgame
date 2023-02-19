#include "abstractScene.h"

#include<resourceManager.h>

AbstractScene::AbstractScene(unsigned width, unsigned int height, ISoundEngine* soundEngine, SceneMediator* sceneMediator)
	:width(width), height(height), soundEngine(soundEngine), sceneMediator(sceneMediator)
{
	// text-UI
	text = new TextRenderer(this->width, this->height);
	text->Load("Fonts/OCRAEXT.TTF", 24);
	// effect postprocessor
	effects = new PostProcessor(ResourceManager::GetShader("postprocessing"), this->width, this->height);
}

AbstractScene::~AbstractScene()
{
	delete text;
	delete effects;
	soundEngine->drop();
}

bool AbstractScene::GetIsEnd()
{
	return isEnd;
}

SceneName AbstractScene::GetNextScene()
{
	return nextScene;
}
