#include "uIMediator.h"

#include<gameLevel.h>
#include<scoreUI.h>
#include<livesUI.h>


UIMediator::UIMediator()
	:focusLevel(nullptr), scoreUI(nullptr), livesUI(nullptr)
{
}

unsigned int UIMediator::ShareScore()
{
	return this->focusLevel->GetScore();
}

void UIMediator::UpdateScore(unsigned int currentScore)
{
	if (this->scoreUI != nullptr)
		this->scoreUI->SetScore(currentScore);
}

void UIMediator::UpdateLives(unsigned int currentLives)
{
	if (this->livesUI != nullptr)
		this->livesUI->SetLives(currentLives);
}