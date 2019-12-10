#ifndef _DrawableManager
#define _DrawableManager

#include <set>
#include "AzulCore.h"

class Drawable;

///
///	\ingroup GameObjectManagerGroup
///
class DrawableManager
{
private:
	typedef std::set<Drawable*> StorageSet;
	StorageSet storage;

	friend class Scene;
	///
	/// \brief Iterate through the set and call Draw on each item
	///
	void ProcessElements();

public:
	DrawableManager(){};
	~DrawableManager();
	DrawableManager(const DrawableManager&) = delete;
	DrawableManager& operator=(const DrawableManager&) = delete;

	///
	/// \brief Add a Drawable to the set
	///
	void Register(Drawable* dr);
	///
	/// \brief Remove a Drawable from the set
	///
	void Deregister(Drawable* dr);
	///
	/// \brief Clears the manager for deletion
	///
	void Delete();
};

#endif _DrawableManager