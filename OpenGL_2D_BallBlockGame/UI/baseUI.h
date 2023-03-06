#ifndef BASE_UI_H
#define BASE_UI_H

#include <gameObject.h>

class TextRenderer;
class UIMediator;
class GameObjectMediator;


class BaseUI
	:public GameObject
{
	public:
		BaseUI(UIMediator& uiMediator, GameObjectMediator& gameObjectMediator);
		~BaseUI();
		virtual void Draw(TextRenderer& textRenderer) = 0;

	protected:
		UIMediator* uiMediator;
};

#endif // !BASE_UI_H
