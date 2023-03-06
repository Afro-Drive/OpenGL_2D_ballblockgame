#ifndef UI_MEDIATOR_H
#define UI_MEDIATOR_H

class GameLevel;
class ScoreUI;
class LivesUI;


class UIMediator
{
	public:
		UIMediator();
		unsigned int ShareScore();
		GameLevel* GetFocusLevel();
		void SetFocusLevel(GameLevel& focusLevel);
		void SetFollowingScoreUI(ScoreUI& scoreUI);
		void SetFollowingLivesUI(LivesUI& livesUI);
		void UpdateScore(unsigned int currentScore);
		void UpdateLives(unsigned int currentLives);

	private:
		GameLevel* focusLevel;
		ScoreUI* scoreUI;
		LivesUI* livesUI;
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

inline void UIMediator::SetFollowingLivesUI(LivesUI& livesUI)
{
	this->livesUI = &livesUI;
}

#endif // !UI_MEDIATOR_H
