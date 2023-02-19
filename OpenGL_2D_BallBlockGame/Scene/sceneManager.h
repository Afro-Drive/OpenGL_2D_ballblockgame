#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H


#include<map>

#include<spriteRendererh.h>
#include"abstractScene.h"
#include<textRenderer.h>


class SceneManager
{
	public:
		/// <summary>
		/// Run scene registered as current scene. The scene execute Key-Input, Update, Render method.
		/// </summary>
		/// <param name="renderer"></param>
		/// <param name="dt"></param>
		void RunScene(SpriteRenderer& renderer, float dt);

		/// <summary>
		/// Add scene object to scene map defined inside this class. The scene is registered with scene name as the label.
		/// !Caution!
		/// When the scene is registered, also registered as current scene. If you use change method, the registerd scene in this is registerd as previous scene(param name = prevSceneName).
		/// </summary>
		/// <param name="sceneName"></param>
		/// <param name="newScene"></param>
		void AddScene(SceneName sceneName, AbstractScene& newScene);

		/// <summary>
		/// Retrieve current scene pointer
		/// </summary>
		/// <returns>currentScene</returns>
		AbstractScene* GetCurrentScene();

		/// <summary>
		/// Retrieve only one instance
		/// </summary>
		/// <returns></returns>
		static SceneManager* GetInstance();

		/// <summary>
		/// Clear all loaded scenes(execute each destructor), and delete myself.
		/// This method must never be called except finishing this game !!
		/// </summary>
		static void DestroySelf();

		/// <summary>
		/// End current scene, switch to next scene.
		/// This method is called by turning scene.isEnd flag true.
		/// </summary>
		/// <param name="nextScene"></param>
		void ChangeScene(SceneName nextScene);

		std::map<SceneName, AbstractScene*> GetSceneMap();
	
	private:
		/// <summary>
		/// private constructor
		/// </summary>
		SceneManager();
		SceneManager(const SceneManager&);
		/// <summary>
		/// private equal operator, pretend to override copy operator
		/// </summary>
		/// <param name=""></param>
		/// <returns></returns>
		SceneManager& operator= (const SceneManager&);
		/// <summary>
		/// private destructor
		/// </summary>
		~SceneManager();
		static SceneManager* Instance;
		AbstractScene* currentScene;
		SceneName prevSceneName, currentSceneName;
		std::map<SceneName, AbstractScene*> sceneMap;
};

#endif // !SCENE_MANAGER_H
