#ifndef _GameObject
#define _GameObject

#include "AzulCore.h"
#include "Updatable.h"
#include "Drawable.h"
#include "Alarmable.h"
#include "Inputable.h"
#include "Collidable.h"

class Scene;
class Camera;

///
///	\ingroup GameObjectGroup
///
class GameObject : public Updatable, public Drawable, public Alarmable, public Inputable, public Collidable
{
private:
	Scene* currentScene;

	friend class CommandSceneAddObject;
	///
	///	\ingroup GameObjectGroup
	///
	/// \brief Used to initialize GameObject to act in the current Scene
	///
	/// \par Example:
	///
	///		This example shows the basic use of registering all the GameObject's functions
	///
	///		\code
	///		void Box::SceneEntry()
	///		{
	///			UpdateRegistration();
	///			DrawRegistration();
	///			KeyEventRegistration(KEY_E, KEY_PRESS);
	///		}
	///		\endcode
	///
	virtual void SceneEntry(){};
	friend class CommandSceneRemoveObject;
	///
	///	\ingroup GameObjectGroup
	///
	/// \brief Used to clear the GameObject to leave the current Scene, similar to SceneEntry but where Deregistrations should be called
	///
	virtual void SceneExit(){};

	///
	/// \brief Called when the GameObject is created to store the currentScene
	///
	void SetScene(Scene* sc);

	///
	/// \brief Returns the current Scene
	///
	virtual Scene* GetGOScene() override;

public:
	GameObject();
	virtual ~GameObject(){};
	GameObject(const GameObject&) = delete;
	GameObject& operator=(const GameObject&) = delete;

	///
	/// \brief Call this when you want to delete an object during runtime
	///
	void MarkForSceneExit();

	///
	/// \brief Returns the current Camera from the current Scene
	///
	/// \par Example:
	///
	///		This example shows the basic method of drawing an object to the screen
	///
	///		\code
	///		void Spaceship::Draw()
	///		{
	///			// (modelName)->Render(GetSceneCamera());
	///			pGObj_SpaceshipWithTexture->Render(GetSceneCamera());
	///		}
	///		\endcode
	///
	Camera* GetSceneCamera();
};

#endif _GameObject