#include "scoreUI.h"

#include<glm/glm.hpp>

#include"uIMediator.h"
#include"textRenderer.h"
#include<string>
#include<gameObjectMediator.h>

const glm::vec2 DRAW_POS = glm::vec2(5.0f, 25.0f);


ScoreUI::ScoreUI(UIMediator& uiMediator, GameObjectMediator& gameObjectMediator)
	:BaseUI(uiMediator, gameObjectMediator),
	 score(0)
{
}

ScoreUI::~ScoreUI()
{
}

void ScoreUI::Draw(TextRenderer& textRenderer)
{
	std::string scoreStr = std::to_string(this->score);
	textRenderer.RenderText("Score: " + scoreStr, DRAW_POS.x, DRAW_POS.y, 1.0f);
}
