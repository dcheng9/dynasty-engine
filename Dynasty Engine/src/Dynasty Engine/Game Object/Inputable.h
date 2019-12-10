#ifndef _Inputable
#define _Inputable

#include "AzulCore.h"

enum INPUT_EVENT_TYPE { KEY_RELEASE = 0, KEY_PRESS = 1 };

class Scene;

///
///	\ingroup GameObjectGroup
///
class Inputable
{
private:
	virtual Scene* GetGOScene() = 0;

public:
	Inputable(){};
	virtual ~Inputable(){};
	Inputable(const Inputable&) = delete;
	Inputable& operator=(const Inputable&) = delete;

	///
	/// \brief Called when you want to register an GameObject to read keyboard inputs
	///		\param k The key you are registering, EX: KEY_W
	///		\param e What input to check for, EX: KEY_PRESS or KEY_RELEASE
	///
	void Inputable::KeyEventRegistration(AZUL_KEY k, INPUT_EVENT_TYPE e);
	///
	/// \brief Called when you want to deregister an GameObject to read keyboard inputs
	///		\param k The key you are deregistering, EX: KEY_W
	///		\param e What input to check for, EX: KEY_PRESS or KEY_RELEASE
	///
	void Inputable::KeyEventDeregistration(AZUL_KEY k, INPUT_EVENT_TYPE e);
	///
	///	\ingroup GameObjectGroup
	///
	/// \brief Use this function to program what you want to happen when a registered key is pressed
	///
	/// \par Example:
	///
	///		This example creates a Bullet when spacebar is pressed
	///
	///		\code
	///		void Spaceship::KeyPressed(AZUL_KEY k)
	///		{
	///			if (k == KEY_SPACE)
	///			{
	///				BulletFactory::CreateBullet(ShipRot, ShipPos);
	///			}
	///		}
	///		\endcode
	///
	virtual void Inputable::KeyPressed(AZUL_KEY k){ AZUL_UNUSED(k); }; //, bool ctrl, bool shft, bool alt); *!* IMPLEMENT LATER
	///
	/// \brief Use this function to program what you want to happen when a registered key is released, similar to KeyPressed
	///
	virtual void Inputable::KeyReleased(AZUL_KEY k){ AZUL_UNUSED(k); }; //, bool ctrl, bool shft, bool alt); *!* IMPLEMENT LATER

};

#endif _Inputable