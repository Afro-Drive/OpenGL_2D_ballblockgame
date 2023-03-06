#ifndef LIVES_UI_H
#define LIVES_UI_H

#include "baseUI.h"

#include<glm/glm.hpp>

class UIMediator;
class GameObjectMediator;


class LivesUI :
    public BaseUI
{
    public:
        LivesUI(UIMediator& uiMediator, GameObjectMediator& gameObjectMediator);
        void Draw(TextRenderer& textRenderer) override;
        void SetLives(unsigned int lives);

    private:
        unsigned int lives;
};

inline void LivesUI::SetLives(unsigned int lives)
{
    this->lives = lives;
}

#endif // !LIVES_UI_H
