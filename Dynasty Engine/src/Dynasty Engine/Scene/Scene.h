#ifndef _Scene
#define _Scene

#include "AzulCore.h"
#include "..\Managers\UpdatableManager.h"
#include "..\Managers\DrawableManager.h"
#include "..\Managers\AlarmableManager.h"
#include "..\Managers\KeyboardEventManager.h"
#include "..\Managers\CameraManager.h"
#include "..\Managers\CollisionManager.h"
#include "..\Managers\SceneTerrainManager.h"
#include "SceneRegistrationBroker.h"
#include "CommandCollisionRegistration.h"
#include "CommandCollisionDeregistration.h"
#include "..\Terrain\TerrainObject.h"

class GameObject;

///
///	\ingroup OtherUserDefGroup
///
class Scene
{
private:
	UpdatableManager UpdateMgr;
	DrawableManager DrawMgr;
	AlarmableManager AlarmMgr;
	KeyboardEventManager KeyEventMgr;
	CollisionManager CollisionMgr;
	CameraManager CameraMgr;
	SceneTerrainManager TerrainMgr;
	SceneRegistrationBroker RegistrationBrkr;

public:
	Scene(){};
	virtual ~Scene(){};
	Scene(const Scene&) = delete;
	Scene& operator=(const Scene&) = delete;

	///
	/// \brief Create a command to register an Updatable to its manager
	///
	void RegisterUpdate(Updatable* up);
	///
	/// \brief Create a command to deregister an Updatable from its manager
	///
	void DeregisterUpdate(Updatable* up);
	///
	/// \brief Create a command to register a Drawable to its manager
	///
	void RegisterDraw(Drawable* dr);
	///
	/// \brief Create a command to deregister an Drawable from its manager
	///
	void DeregisterDraw(Drawable* dr);
	///
	/// \brief Create a command to register an AlarmMarker to its manager
	///
	void RegisterAlarm(AlarmMarker* am);
	///
	/// \brief Create a command to deregister an AlarmMarker from its manager
	///
	void DeregisterAlarm(AlarmMarker* am);
	///
	/// \brief Create a command to register an Inputable to its manager
	///
	void RegisterKeyEvent(Inputable* in, AZUL_KEY k, INPUT_EVENT_TYPE e);
	///
	/// \brief Create a command to deregister an Inputable from its manager
	///
	void DeregisterKeyEvent(Inputable* in, AZUL_KEY k, INPUT_EVENT_TYPE e);

	///
	/// \brief Create a command to register an Collision to its manager
	///
	template <typename C>
	void RegisterCollision(C* c)
	{
		CommandCollisionRegistration<C>* ptrClCmd = new CommandCollisionRegistration<C>(c);
		RegistrationBrkr.addCommand(ptrClCmd);
	}
	
	///
	/// \brief Create a command to deregister a Collision from its manager
	///
	template <typename C>
	void DeregisterCollision(C* c)
	{
		CommandCollisionDeregistration<C>* ptrClCmd = new CommandCollisionDeregistration<C>(c);
		RegistrationBrkr.addCommand(ptrClCmd);
	}
	
	///
	/// \brief Create CollidableGroups and adds them as a pair to the manager
	///
	template <typename C1, typename C2>
	void SetCollisionPair()
	{
		CollisionMgr.SetCollisionPair<C1, C2>();

		CollisionMgr.AddColGroupDeleteCommand(CollidableGroup<C1>::GetShutdownCommand());
		CollisionMgr.AddColGroupDeleteCommand(CollidableGroup<C2>::GetShutdownCommand());
	}

	///
	/// \brief Create a CollidableGroup and adds it with itself to the manager
	///
	template <typename C>
	void SetCollisionSelf()
	{
		CollisionMgr.SetCollisionSelf<C>();

		CollisionMgr.AddColGroupDeleteCommand(CollidableGroup<C>::GetShutdownCommand());
	}

	///
	/// \brief Create a CollidableGroup and adds it with the TerrainObject to the manager
	///
	template <typename C>
	void SetCollisionTerrain()
	{
		CollisionMgr.SetCollisionTerrain<C>();

		CollisionMgr.AddColGroupDeleteCommand(CollidableGroup<C>::GetShutdownCommand());
	}

	///
	/// \brief Create a command to add a GameObject to the current Scene
	///
	void AddToScene(GameObject* go);
	///
	/// \brief Create a command to remove a GameObject from the current Scene
	///
	void RemoveFromScene(GameObject* go);
	///
	/// \brief Set the Scene's currentTerrain
	///
	void SetTerrain(const std::string& key);
	///
	/// \brief Call Delete on every Scene level manager
	///
	void Delete();

	///
	/// \brief Gets the Scene's CameraManager
	///
	CameraManager& GetCameraManager(){ return CameraMgr; }
	///
	/// \brief Gets the Scene's TerrainManager
	///
	SceneTerrainManager& GetTerrainManager(){ return TerrainMgr; }

protected:
	friend class SceneManager;
	///
	///	\ingroup OtherUserDefGroup
	///
	/// \brief Called when the Scene becomes the current Scene
	///
	/// \par Example:
	///
	///		This example shows a basic Scene creating new GameObjects, adding them to the Scene, and setting up collision pairs
	///
	///		\code
	///		void SceneTest::Initialize()
	///		{
	///			testSpaceship = new Spaceship();
	///			testBox = new Box();
	///			testCottage = new Cottage();
	///
	///			AddToScene(testSpaceship);
	///			AddToScene(testBox);
	///			AddToScene(testCottage);
	///
	///			SetCollisionPair<Spaceship, Cottage>();
	///			SetCollisionSelf<Spaceship>();
	///		}
	///		\endcode
	///
	virtual void Initialize() = 0;
	///
	///	\ingroup OtherUserDefGroup
	///
	/// \brief Called when the Scene is about to change, use this to call MarkForSceneExit on all active GameObjects
	///
	virtual void SceneEnd(){};

	///
	/// \brief Calls for all Scene level managers to process their sets and maps
	///
	void Update();
	///
	/// \brief Calls for the DrawableManager to process its set
	///
	void Draw();
};

#endif _Scene