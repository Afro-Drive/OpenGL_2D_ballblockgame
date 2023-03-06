#include "baseUI.h"

#include<glm/glm.hpp>

#include<transform.h>
#include<texture.h>
#include<gameObjectMediator.h>
#include"uIMediator.h"


BaseUI::BaseUI(UIMediator& uiMediator, GameObjectMediator& gameObjectMediator)
	: GameObject(glm::vec2(0.0f), glm::vec2(0.0f), Texture2D(), nullptr, gameObjectMediator, GameTag::NONE),
	  uiMediator(&uiMediator)
{
}

BaseUI::~BaseUI()
{
}
