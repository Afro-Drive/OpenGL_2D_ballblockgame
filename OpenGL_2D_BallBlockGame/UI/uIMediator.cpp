#include "uIMediator.h"

#include<gameLevel.h>
#include<scoreUI.h>


UIMediator::UIMediator()
	:focusLevel(nullptr), scoreUI(nullptr)
{
}

unsigned int UIMediator::ShareScore()
{
	return this->focusLevel->GetScore();
}

void UIMediator::UpdateScore(unsigned int currentScore)
{
	this->scoreUI->SetScore(currentScore);
}