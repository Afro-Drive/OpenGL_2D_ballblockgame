#include "powerUpManager.h"

#include<tuple>

#include<gameObjectMediator.h>
#include<resourceManager.h>
#include"player.h"
#include<postProcessor.h>
#include<ballObject.h>
#include<collider.h>
#include<boxCollider.h>


PowerUpManager::PowerUpManager(GameObjectMediator& mediator)
	:mediator(&mediator)
{
}

PowerUpManager::~PowerUpManager()
{
	for (PowerUp* powerUp : this->powerUps)
	{
		delete powerUp;
	}
	powerUps.clear();
}

void PowerUpManager::Update(float dt)
{
	BallObject* Ball = (BallObject*)(this->mediator->SurveyActiveGameObject(GameTag::BALL));
	GameObject* player = this->mediator->SurveyActiveGameObject(GameTag::PLAYER);
	PostProcessor* effects = static_cast<PostProcessor*>(this->mediator->GetEffects());

	for (PowerUp* powerUp : this->powerUps)
    {
		// update for no destroyed object
		if (!powerUp->Destroyed)
		{
			powerUp->Update(dt);

			if (powerUp->Position.y >= this->mediator->GetScreenSize().y)
				powerUp->Destroyed = true;

			Collision onCollision = powerUp->GetCollider()->DoCollision(*(player->GetCollider()));
			if (std::get<0>(onCollision))
				// collided with player, now activate powerup
				ActivatePowerUp(*powerUp, *Ball, *(static_cast<Player*>(player)), *effects);
		}
		// update for activated object
		if (powerUp->Activated)
		{
			powerUp->Duration -= dt;

			if (powerUp->Duration <= 0.0f)
				InActivatePowerUp(*powerUp, *Ball, *(static_cast<Player*>(player)), *effects);
		}
	}
	this->powerUps.erase(
		std::remove_if(
			this->powerUps.begin(),
			this->powerUps.end(),
			[](const PowerUp* powerUp) { return powerUp->Destroyed && !powerUp->Activated; }),
		this->powerUps.end());
}

void PowerUpManager::ActivatePowerUp(PowerUp& powerUp, BallObject& ball, Player& player, PostProcessor& effects)
{
	powerUp.Destroyed = true;
	powerUp.Activated = true;
	
	switch (powerUp.Type)
	{
	case PowerUpType::SPEED:
		ball.Velocity *= 1.2;
		break;
	case PowerUpType::STICKY:
		ball.Sticky = true;
		player.Color = glm::vec3(1.0f, 0.5f, 1.0f);
		break;
	case PowerUpType::PASS_THROUGH:
		ball.PassThrough = true;
		player.Color = glm::vec3(1.0f, 0.5f, 0.5f);
		break;
	case PowerUpType::PAD_SIZE_INCREASE:
		player.Size.x += 50;
		break;
	case PowerUpType::CONFUSE:
		if (!effects.Confuse)
			effects.Confuse = true; // only activate if chaos wasn't already activated
		break;
	case PowerUpType::CHAOS:
		if (!effects.Chaos)
			effects.Chaos = true; // only activate if confuse wasn't already activated
		break;
	}

	powerUp.DoSpecialOnCollision();
}

void PowerUpManager::InActivatePowerUp(PowerUp& powerUp, BallObject& ball, Player& player, PostProcessor& effects)
{
	// remove powerup from list (will late be removed)
	powerUp.Activated = false;

	// deactivate effects
	switch (powerUp.Type) 
	{
	case PowerUpType::STICKY:
		if (!IsOtherPowerUpActive(powerUp, PowerUpType::STICKY))
		{
			// only reset if no other PowerUp of tyep sticky is active
			ball.Sticky = false;
			player.Color = glm::vec3(1.0f);
		}
		break;
	case PowerUpType::PASS_THROUGH:
		if (!IsOtherPowerUpActive(powerUp, PowerUpType::PASS_THROUGH))
		{
			// only reset if no other PowerUp of tyep pass-through is active
			ball.PassThrough = false;
			player.Color = glm::vec3(1.0f);
		}
		break;
	case PowerUpType::CONFUSE:
		if (!IsOtherPowerUpActive(powerUp, PowerUpType::CONFUSE))
			// only reset if no other PowerUp of tyep confuse is active
			effects.Confuse = false;
		break;
	case PowerUpType::CHAOS:
		if (!IsOtherPowerUpActive(powerUp, PowerUpType::CHAOS))
			// only reset if no other PowerUp of tyep chaos is active
			effects.Chaos = false;
		break;
	}
}

bool PowerUpManager::IsOtherPowerUpActive(PowerUp& powerUp, PowerUpType type)
{
	if (powerUp.Activated)
		if (powerUp.Type == type)
			return true;

	return false;
}

bool ShouldSpawn(unsigned int chance)
{
	unsigned int random = rand() % chance;
	return random == 0;
}
void PowerUpManager::Spawn(glm::vec2 spawnPos)
{
	PowerUp* pu;
	Collider2D* col;

	if (ShouldSpawn(75)) // 1 in 75 chance
	{
		pu = new PowerUp(PowerUpType::SPEED, glm::vec3(0.5f, 0.5f, 1.0f), 0.0f, spawnPos, ResourceManager::GetTexture("powerup_speed"), *(this->mediator), nullptr);
		col = new BoxCollider2D(spawnPos, pu->Size, *pu, *(this->mediator));
		pu->SetCollider(*col);
		this->powerUps.push_back(pu);
	}
	if (ShouldSpawn(75))
	{
		pu = new PowerUp(PowerUpType::STICKY, glm::vec3(1.0f, 0.5f, 1.0f), 20.0f, spawnPos, ResourceManager::GetTexture("powerup_sticky"), *(this->mediator), nullptr);
		col = new BoxCollider2D(spawnPos, pu->Size, *pu, *(this->mediator));
		pu->SetCollider(*col);
		this->powerUps.push_back(pu);
	}
	if (ShouldSpawn(75))
	{
		pu = new PowerUp(PowerUpType::PASS_THROUGH, glm::vec3(0.5f, 1.0f, 0.5f), 10.0f, spawnPos, ResourceManager::GetTexture("powerup_passthrough"), *(this->mediator), nullptr);
		col = new BoxCollider2D(spawnPos, pu->Size, *pu, *(this->mediator));
		pu->SetCollider(*col);
		this->powerUps.push_back(pu);
	}
	if (ShouldSpawn(75))
	{
		pu = new PowerUp(PowerUpType::PAD_SIZE_INCREASE, glm::vec3(1.0f, 0.6f, 0.4f), 0.0f, spawnPos, ResourceManager::GetTexture("powerup_increase"), *(this->mediator), nullptr);
		col = new BoxCollider2D(spawnPos, pu->Size, *pu, *(this->mediator));
		pu->SetCollider(*col);
		this->powerUps.push_back(pu);
	}

	if (ShouldSpawn(15)) // negative powerups should spawn more often
	{
		pu = new PowerUp(PowerUpType::CONFUSE, glm::vec3(1.0f, 0.3f, 0.3f), 15.0f, spawnPos, ResourceManager::GetTexture("powerup_confuse"), *(this->mediator), nullptr);
		col = new BoxCollider2D(spawnPos, pu->Size, *pu, *(this->mediator));
		pu->SetCollider(*col);
		this->powerUps.push_back(pu);
	}
	if (ShouldSpawn(15))
	{
		pu = new PowerUp(PowerUpType::CHAOS, glm::vec3(0.9f, 0.5f, 0.25f), 15.0f, spawnPos, ResourceManager::GetTexture("powerup_chaos"), *(this->mediator), nullptr);
		col = new BoxCollider2D(spawnPos, pu->Size, *pu, *(this->mediator));
		pu->SetCollider(*col);
		this->powerUps.push_back(pu);
	}
}

void PowerUpManager::Draw(SpriteRenderer& renderer)
{
	for (PowerUp* powerUp : this->powerUps)
		if (!powerUp->Destroyed)
			powerUp->Draw(renderer);
}

