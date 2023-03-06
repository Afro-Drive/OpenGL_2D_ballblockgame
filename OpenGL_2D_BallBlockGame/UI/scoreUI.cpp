#include "scoreUI.h"

#include<glm/glm.hpp>

#include"uIMediator.h"
#include"textRenderer.h"
#include<string>
#include<gameObjectMediator.h>

const glm::vec3 DRAW_POS = glm::vec3(5.0f, 25.0f, 1.0f);


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
	textRenderer.RenderText("Score: " + scoreStr, DRAW_POS.x, DRAW_POS.y, DRAW_POS.z);
}
