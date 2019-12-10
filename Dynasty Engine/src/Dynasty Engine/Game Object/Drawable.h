#ifndef _Drawable
#define _Drawable

#include "AzulCore.h"

class GraphicsObject;
class Scene;

///
///	\ingroup GameObjectGroup
///
class Drawable
{
private:
	virtual Scene* GetGOScene() = 0;

public:
	Drawable(){};
	virtual ~Drawable(){};
	Drawable(const Drawable&) = delete;
	Drawable& operator=(const Drawable&) = delete;

	///
	///	\ingroup GameObjectGroup
	///
	/// \brief Use this function to program what you want to be drawn, called every frame
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
	virtual void Draw(){};

	///
	/// \brief Called when you want to register a GameObject to Draw
	///
	void Drawable::DrawRegistration();
	///
	/// \brief Called when you want to deregister a GameObject to Draw
	///
	void Drawable::DrawDeregistration();
};

#endif _Drawable