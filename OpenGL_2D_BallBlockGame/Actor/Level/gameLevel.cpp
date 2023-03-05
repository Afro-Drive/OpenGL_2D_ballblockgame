#include"gameLevel.h"

#include<fstream>
#include<sstream>
#include<tuple>

#include<gameObjectMediator.h>
#include<powerUpManager.h>
#include"resourceManager.h"
#include<gameObjectMediator.h>
#include<postProcessor.h>
#include<ballObject.h>
#include<boxCollider.h>
#include<player.h>


GameLevel::GameLevel(GameObjectMediator& mediator)
	:mediator(&mediator)
{
	this->powerUpManager = new PowerUpManager(*(this->mediator));
	this->Bricks.clear();
}

GameLevel::~GameLevel()
{
	delete this->powerUpManager;
}

void GameLevel::Load(const char* file, unsigned int levelWidth, unsigned int levelHeihgt)
{
	// clear old data
	this->Bricks.clear();
	// load from file
	unsigned int tileCode;
	std::string line;
	std::ifstream fstream(file);
	std::vector<std::vector<unsigned int>> tileData;

	if (fstream)
	{
		while (std::getline(fstream, line)) // read each line from level file
		{
			std::istringstream sstream(line);
			std::vector<unsigned int> row;
			while (sstream >> tileCode) // read each word separated by spaces
				row.push_back(tileCode);
			tileData.push_back(row);
		}
		if (tileData.size() > 0)
			this->init(tileData, levelWidth, levelHeihgt);
	}
}

void GameLevel::Draw(SpriteRenderer& renderer)
{
	for (Brock* tile : this->Bricks)
		if (!tile->Destroyed)
			tile->Draw(renderer);

	powerUpManager->Draw(renderer);
}

bool GameLevel::IsCompleted()
{
	for (GameObject* tile : this->Bricks)
		if (!tile->IsSolid && !tile->Destroyed)
			return false;

	return true;
}

void GameLevel::JudgeCollision()
{
	// for ball & brock
	GameObject* ballObj = static_cast<BallObject*>(this->mediator->SurveyActiveGameObject(GameTag::BALL));
	for (Brock* box : this->Bricks)
	{
		if (box->Destroyed)
			continue;

		Collision onCollision = box->GetCollider()->DoCollision(*(ballObj->GetCollider()));
		if (std::get<0>(onCollision))
		{
			if (!box->IsSolid)
			{
				box->Destroyed = true;
				box->DoSpecialOnCollision();
				this->powerUpManager->Spawn(box->Position);
			}
			else
			{
				// if block is solid, enable shake effect
				shakeTime = 0.05f;
				this->mediator->GetEffects()->Shake = true;
			}
		}
	}

	// for player & ball
	if (!static_cast<BallObject*>(ballObj)->Stuck)
	{
		GameObject* player = static_cast<Player*>(this->mediator->SurveyActiveGameObject(GameTag::PLAYER));
		player->GetCollider()->DoCollision(*(ballObj->GetCollider()));
	}
}

void GameLevel::Update(float dt)
{
	// reduce shake time
	if (shakeTime > 0.0f)
	{
		shakeTime -= dt;
		if (shakeTime <= 0.0f)
			this->mediator->GetEffects()->Shake = false;
	}

	JudgeCollision();
	// perform update, judege collision related powerup
	this->powerUpManager->Update(dt);
}

void GameLevel::init(std::vector<std::vector<unsigned int>> tileData, unsigned int levelWidth, unsigned int levelHeight)
{
	shakeTime = 0.0f;

	// calculate dimensions
	unsigned int height = tileData.size();
	unsigned int width = tileData[0].size();
	float unit_width = levelWidth / static_cast<float>(width);
	float unit_height = levelHeight / height;

	// initialize level tiles based on tileData
	for (unsigned int y = 0; y < height; ++y)
	{
		for (unsigned int x = 0; x < width; ++x)
		{
			unsigned int targetUnit = tileData[y][x];
			// check block type from level data (2D level array)
			if (targetUnit == 1) // solid
			{
				glm::vec2 pos(unit_width * x, unit_height * y);
				glm::vec2 size(unit_width, unit_height);
				BoxCollider2D* collider = nullptr;
				Brock* brockObj = new Brock(pos, size,
					ResourceManager::GetTexture("block_solid"),
					*(this->mediator),
					GameTag::BROCK,
					collider,
					glm::vec3(0.8f, 0.8f, 0.7f),
					glm::vec2(0.0f, 0.0f)
				);
				collider = new BoxCollider2D(pos, size, *brockObj, *(this->mediator));
				brockObj->SetCollider(*collider);
				brockObj->IsSolid = true;
				this->Bricks.push_back(brockObj);
			}
			else if (targetUnit > 1)
			{
				glm::vec3 color = glm::vec3(1.0f); // original: white
				
				if (targetUnit == 2)
					color = glm::vec3(0.2f, 0.6f, 1.0f);
				else if (targetUnit == 3)
					color = glm::vec3(0.0f, 0.7f, 0.0f);
				else if (targetUnit == 4)
					color = glm::vec3(0.8f, 0.8f, 0.4f);
				else if (targetUnit == 5)
					color = glm::vec3(1.0f, 0.5f, 0.0f);

				glm::vec2 pos(unit_width * x, unit_height * y);
				glm::vec2 size(unit_width, unit_height);
				BoxCollider2D* collider = nullptr;
				Brock* brockObj = new Brock(pos, size,
					ResourceManager::GetTexture("block"),
					*(this->mediator),
					GameTag::BROCK,
					collider,
					color,
					glm::vec2(0.0f, 0.0f));
				collider = new BoxCollider2D(pos, size, *brockObj, *(this->mediator));
				brockObj->SetCollider(*collider);
				this->Bricks.push_back(brockObj);
			}
		}
	}
}
