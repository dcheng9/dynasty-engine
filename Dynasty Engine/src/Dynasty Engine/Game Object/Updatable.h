#ifndef _Updatable
#define _Updatable

#include "AzulCore.h"

class Scene;

///
///	\ingroup GameObjectGroup
///
class Updatable
{
private:
	virtual Scene* GetGOScene() = 0;

public:
	Updatable(){};
	virtual ~Updatable(){};
	Updatable(const Updatable&) = delete;
	Updatable& operator=(const Updatable&) = delete;

	///
	///	\ingroup GameObjectGroup
	///
	/// \brief Use this function to program what you want to update, called every frame
	///
	virtual void Update(){};

	///
	/// \brief Called when you want to register a GameObject to Update
	///
	void Updatable::UpdateRegistration();
	///
	/// \brief Called when you want to deregister a GameObject to Update
	///
	void Updatable::UpdateDeregistration();
};

#endif _Updatable