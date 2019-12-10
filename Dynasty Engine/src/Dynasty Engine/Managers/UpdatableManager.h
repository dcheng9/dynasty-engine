#ifndef _UpdatableManager
#define _UpdatableManager

#include <set>
#include "AzulCore.h"

class Updatable;

///
///	\ingroup GameObjectManagerGroup
///
class UpdatableManager
{
private:
	typedef std::set<Updatable*> StorageSet;
	StorageSet storage;

	friend class Scene;
	///
	/// \brief Iterate through the set and call Update on each item
	///
	void ProcessElements();

public:
	UpdatableManager(){};
	~UpdatableManager();
	UpdatableManager(const UpdatableManager&) = delete;
	UpdatableManager& operator=(const UpdatableManager&) = delete;

	///
	/// \brief Add an Updatable to the set
	///
	void Register(Updatable* up);
	///
	/// \brief Remove an Updatable from the set
	///
	void Deregister(Updatable* up);
	///
	/// \brief Clears the manager for deletion
	///
	void Delete();
};

#endif _UpdatableManager