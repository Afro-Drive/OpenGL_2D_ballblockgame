#ifndef POWER_UP_MANAGER_H
#define POWER_UP_MANAGER_H

#include<vector>

#include"powerUp.h"

// forward reference
class GameObjectMediator;
class Player;
class PostProcessor;
class BallObject;
class SpriteRenderer;


class PowerUpManager
{
	public:
		PowerUpManager(GameObjectMediator& mediator);
		~PowerUpManager();
		std::vector<PowerUp*> GetPowerUps();
		void Update(float dt);
		void Spawn(glm::vec2 spawnPos);
		void Draw(SpriteRenderer& renderer);

	private:
		void InActivatePowerUp(PowerUp& powerUp, BallObject& ball, Player& player, PostProcessor& effects);
		bool IsOtherPowerUpActive(PowerUp& powerUp, PowerUpType type);
		void ActivatePowerUp(PowerUp& powerUp, BallObject& ball, Player& player, PostProcessor& effects);

		std::vector<PowerUp*> powerUps;
		GameObjectMediator* mediator;
};

inline std::vector<PowerUp*> PowerUpManager::GetPowerUps()
{
	return this->powerUps;
}

#endif // !POWER_UP_MANAGER_H
