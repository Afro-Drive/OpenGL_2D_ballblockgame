#include "uIMediator.h"

#include<gameLevel.h>


UIMediator::UIMediator()
	:focusLevel(nullptr)
{
}

unsigned int UIMediator::ShareScore()
{
	return this->focusLevel->GetScore();
}
