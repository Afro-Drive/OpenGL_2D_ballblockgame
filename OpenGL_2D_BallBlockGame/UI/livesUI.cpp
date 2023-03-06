#include "livesUI.h"

#include<string>
#include<sstream>

#include"textRenderer.h"


LivesUI::LivesUI(UIMediator& uiMediator, GameObjectMediator& gameObjectMediator)
	:BaseUI(uiMediator, gameObjectMediator),
	 lives(0)
{
}

void LivesUI::Draw(TextRenderer& textRenderer)
{
	std::stringstream livesStr;
	livesStr << this->lives;
	textRenderer.RenderText("Lives: " + livesStr.str(), DRAW_POS.x, DRAW_POS.y, 1.0f);
}
