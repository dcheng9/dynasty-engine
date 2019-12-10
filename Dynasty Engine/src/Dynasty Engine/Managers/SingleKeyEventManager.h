#ifndef _SingleKeyEventManager
#define _SingleKeyEventManager

#include <set>

#include "AzulCore.h"

class Inputable;
enum INPUT_EVENT_TYPE;

///
///	\ingroup GameObjectManagerGroup
///
class SingleKeyEventManager
{
private:

	std::set<Inputable*> pressedInputs;
	std::set<Inputable*> releasedInputs;

	AZUL_KEY monitorKey;

	bool previousState = false;
	bool currentState = false;

	friend class Scene;
	
public:
	SingleKeyEventManager(){};
	~SingleKeyEventManager();
	SingleKeyEventManager(const SingleKeyEventManager&) = delete;
	SingleKeyEventManager& operator=(const SingleKeyEventManager&) = delete;

	SingleKeyEventManager(AZUL_KEY k);

	///
	/// \brief Iterate through the both sets and check if the key's state have changed to report back to the KeyboadEventManager
	///
	void ProcessElements();
	///
	/// \brief Add an Inputable to a set depending on the INPUT_EVENT_TYPE passed in
	///
	void Register(Inputable* in, INPUT_EVENT_TYPE e);
	///
	/// \brief Remove an Inputable from a set depending on the INPUT_EVENT_TYPE passed in
	///
	void Deregister(Inputable* in, INPUT_EVENT_TYPE e);
};

#endif _SingleKeyEventManager