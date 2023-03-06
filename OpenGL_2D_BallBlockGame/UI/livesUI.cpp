#include "livesUI.h"

#include<string>
#include<sstream>

#include"textRenderer.h"

const glm::vec3 DRAW_POS = glm::vec3(5.0f, 5.0f, 1.0f);


LivesUI::LivesUI(UIMediator& uiMediator, GameObjectMediator& gameObjectMediator)
	:BaseUI(uiMediator, gameObjectMediator),
	 lives(0)
{
}

void LivesUI::Draw(TextRenderer& textRenderer)
{
	std::stringstream livesStr;
	livesStr << this->lives;
	textRenderer.RenderText("Lives: " + livesStr.str(), DRAW_POS.x, DRAW_POS.y, DRAW_POS.z);
}
