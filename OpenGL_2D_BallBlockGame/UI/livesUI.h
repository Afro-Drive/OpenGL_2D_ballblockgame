#ifndef LIVES_UI_H
#define LIVES_UI_H

#include "baseUI.h"


class LivesUI :
    public BaseUI
{
    public:
        void Draw(TextRenderer& textRenderer) override;
};

#endif // !LIVES_UI_H
