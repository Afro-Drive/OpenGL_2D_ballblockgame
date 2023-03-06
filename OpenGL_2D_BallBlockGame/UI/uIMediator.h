#ifndef UI_MEDIATOR_H
#define UI_MEDIATOR_H

class GameLevel;


class UIMediator
{
	public:
		UIMediator();
		unsigned int ShareScore();
		GameLevel* GetFocusLevel();
		void SetFocusLevel(GameLevel& focusLevel);

	private:
		GameLevel* focusLevel;
};

inline GameLevel* UIMediator::GetFocusLevel()
{
	return this->focusLevel;
}

inline void UIMediator::SetFocusLevel(GameLevel& focusLevel)
{
	this->focusLevel = &focusLevel;
}

#endif // !UI_MEDIATOR_H
