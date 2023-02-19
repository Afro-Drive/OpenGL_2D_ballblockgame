#ifndef GAME_MAIN_SCENE_H
#define GAME_MAIN_SCENE_H


#include"abstractScene.h"

#include<vector>

#include<gameLevel.h>
#include<ballObject.h>
#include<powerUp.h>

enum Direction {
    UP,
    RIGHT,
    DOWN,
    LEFT
};

typedef std::tuple<bool, Direction, glm::vec2> Collision;


class GameMainScene :
    public AbstractScene
{
    public:
        GameMainScene(unsigned int width, unsigned int height, ISoundEngine* soundEngine, SceneMediator* sceneMediator);
        ~GameMainScene();

        virtual void Init() override;
        virtual void Update(float dt) override;
        virtual void Render(SpriteRenderer* renderer) override;
        virtual void ProcessInput(float dt) override;

        void DoCollisions();
        bool CheckCollision(GameObject& one, GameObject& two);
        Collision CheckCollision(BallObject& one, GameObject& two);
        Direction VectorDirection(glm::vec2 target);
        void ResetPlayer();
        void ResetLevel();
        void SpawnPowerUps(GameObject& block);
        void UpdatePowerUps(float dt);
        void ActivatePowerUp(PowerUp& powerUp);
        bool IsOtherPowerUpActive(std::vector<PowerUp>& powerUps, std::string type);
        bool isLoadedStage();
        bool LoadStageData();
        std::vector<GameLevel> getStageVector();

    private:
        unsigned int level;
        std::vector<GameLevel> stageVector;
        bool loadedStage;
        unsigned int lives;
        std::vector<PowerUp> powerUps;
};

#endif // !GAME_MAIN_SCENE_H
