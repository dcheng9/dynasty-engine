#ifndef _SceneManager
#define _SceneManager

#include "AzulCore.h"

class Scene;
class GameObject;
class Camera;
class TerrainObject;

///
///	\ingroup OtherManagerGroup
///
class SceneManager
{
private:
	~SceneManager();
	static SceneManager* singleInst;

	SceneManager(){};		// Private constructor
	SceneManager(const SceneManager&) = delete;	// Prevent copy-construction
	SceneManager& operator=(const SceneManager&) = delete;	// Prevent assignment

	static SceneManager& Instance()		// Access reference (all public methods will be static)
	{
		if (!singleInst)
			singleInst = new SceneManager();
		return *singleInst;
	};

	Scene* currentScene;
	Camera* currentCamera;

	friend class Dynasty;
	///
	/// \brief Clears the manager for deletion
	///
	static void Delete();

public:
	///
	/// \brief Calls the current Scene's Initialize
	///
	static void InitializeScene();
	///
	/// \brief Calls the current Scene's Update
	///
	static void Update();
	///
	/// \brief Calls the current Scene's Draw
	///
	static void Draw();

	///
	/// \brief Call to add a GameObject to the current Scene, calls the GameObject's SceneEntry
	///
	/// \param go The GameObject you want to add from the scene
	///
	static void AddToScene(GameObject* go);
	///
	/// \brief Call to remove a GameObject to the current Scene, calls the GameObject's SceneExit
	///
	/// \param go The GameObject you want to remove from the scene
	///
	static void RemoveFromScene(GameObject* go);
	///
	/// \brief Call to set up a Scene to change
	///
	/// \param nextScene The Scene you want to change to
	///
	static void SetNextScene(Scene* nextScene);

	///
	/// \brief Returns the current Scene's Camera
	///
	static Camera* GetCurrentCamera();
	///
	/// \brief Returns the current Scene's TerrainObject
	///
	static TerrainObject* GetCurrentTerrain();

	///
	/// \brief Calls the current Scene's SceneEnd
	///
	static void EndCurrentScene();
	///
	/// \brief Calls the current Scene's Delete, which deletes all Scene level managers
	///
	static void DeleteCurrentScene();

	///
	/// \brief Called internally to change to a new Scene and call Initialize on it
	///
	static void SetScene(Scene* sc);
};
#endif _SceneManager