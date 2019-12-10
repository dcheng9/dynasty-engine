#ifndef _KeyboardEventManager
#define _KeyboardEventManager

#include <map>
#include "SingleKeyEventManager.h"

#include "AzulCore.h"

class Inputable;

///
///	\ingroup GameObjectManagerGroup
///
class KeyboardEventManager
{
private:
	typedef std::map<AZUL_KEY, SingleKeyEventManager*> KeyMgrMap;
	KeyMgrMap skeMgrMap;

	friend class Scene;
	///
	/// \brief Iterate through the map and call ProcessElements on each SingleKeyEventManager
	///
	void ProcessElements();

public:
	KeyboardEventManager(){};
	~KeyboardEventManager();
	KeyboardEventManager(const KeyboardEventManager&) = delete;
	KeyboardEventManager& operator=(const KeyboardEventManager&) = delete;

	///
	/// \brief Create a new SingleKeyEventManager if there isn't one and add an Inputable and INPUT_EVENT_TYPE to it
	///
	void Register(Inputable* in, AZUL_KEY k, INPUT_EVENT_TYPE e);
	///
	/// \brief Remove an Inputable from its SingleKeyEventManager
	///
	void Deregister(Inputable* in, AZUL_KEY k, INPUT_EVENT_TYPE e);
	///
	/// \brief Clears the manager for deletion
	///
	void Delete();
};

#endif _KeyboardEventManager