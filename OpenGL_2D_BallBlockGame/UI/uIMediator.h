#ifndef UI_MEDIATOR_H
#define UI_MEDIATOR_H

class GameLevel;
class ScoreUI;
class AbstractScene;


class UIMediator
{
	public:
		UIMediator();
		unsigned int ShareScore();
		GameLevel* GetFocusLevel();
		void SetFocusLevel(GameLevel& focusLevel);
		void SetFollowingScoreUI(ScoreUI& scoreUI);
		void UpdateScore(unsigned int currentScore);

	private:
		GameLevel* focusLevel;
		ScoreUI* scoreUI;
};

inline GameLevel* UIMediator::GetFocusLevel()
{
	return this->focusLevel;
}

inline void UIMediator::SetFocusLevel(GameLevel& focusLevel)
{
	this->focusLevel = &focusLevel;
}

inline void UIMediator::SetFollowingScoreUI(ScoreUI& scoreUI)
{
	this->scoreUI = &scoreUI;
}

#endif // !UI_MEDIATOR_H
