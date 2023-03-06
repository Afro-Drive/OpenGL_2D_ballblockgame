#include "scoreUI.h"

#include<glm/glm.hpp>

#include"uIMediator.h"
#include"textRenderer.h"
#include<string>
#include<gameObjectMediator.h>


ScoreUI::ScoreUI(UIMediator& uiMediator, GameObjectMediator& gameObjectMediator)
	:BaseUI(uiMediator, gameObjectMediator)
{
}

ScoreUI::~ScoreUI()
{
}

void ScoreUI::Draw(TextRenderer& textRenderer)
{
	std::string scoreStr = std::to_string(this->uiMediator->ShareScore());
	glm::vec2 scorePos = glm::vec2(5.0f, 25.0f);
	textRenderer.RenderText("Score: " + scoreStr, scorePos.x, scorePos.y, 1.0f);
}
