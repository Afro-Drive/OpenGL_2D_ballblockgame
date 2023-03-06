#ifndef SCORE_UI_H
#define SCORE_UI_H

#include "baseUI.h"

class GameObjectMediator;
class UIMediator;


class ScoreUI :
    public BaseUI
{
    public:
        ScoreUI(UIMediator& uiMediator, GameObjectMediator& gameObjectMediator);
        ~ScoreUI();
        void Draw(TextRenderer& textRenderer) override;
        void SetScore(unsigned int score);
        
    private:
        unsigned int score;
};

inline void ScoreUI::SetScore(unsigned int score)
{
    this->score = score;
}

#endif // !SCORE_UI_H
