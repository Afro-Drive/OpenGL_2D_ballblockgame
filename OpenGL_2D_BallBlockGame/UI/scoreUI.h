#ifndef SCORE_UI_H
#define SCORE_UI_H

#include "baseUI.h"

class TextRenderer;
class GameObjectMediator;
class UIMediator;


class ScoreUI :
    public BaseUI
{
    public:
        ScoreUI(UIMediator& uiMediator, GameObjectMediator& gameObjectMediator);
        ~ScoreUI();
        void Draw(TextRenderer& textRenderer) override;
        
    private:
        unsigned int score;
};

#endif // !SCORE_UI_H
