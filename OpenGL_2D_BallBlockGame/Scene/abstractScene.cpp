#include "abstractScene.h"

#include<resourceManager.h>
#include<gameObjectMediator.h>
#include<input.h>
#include"sceneMediator.h"
#include<textRenderer.h>
#include<postProcessor.h>


AbstractScene::AbstractScene(unsigned width, unsigned int height, SceneMediator* sceneMediator, UIMediator* uiMediator)
	:width(width), height(height), isEnd(false), nextScene(), sceneMediator(sceneMediator), uiMediator(uiMediator)
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
}
