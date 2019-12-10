#ifndef _AlarmableManager
#define _AlarmableManager

#include <map>
#include "AzulCore.h"

class AlarmMarker;

///
///	\ingroup GameObjectManagerGroup
///
class AlarmableManager
{
private:
	typedef std::map<float, AlarmMarker*> TimelineMap;
	TimelineMap tlMap;

	friend class Scene;
	///
	/// \brief Iterate through the map and call CallEvent on each item
	///
	void ProcessElements();

public:
	AlarmableManager(){};
	~AlarmableManager();
	AlarmableManager(const AlarmableManager&) = delete;
	AlarmableManager& operator=(const AlarmableManager&) = delete;

	///
	/// \brief Add an Alarm to the map with the time it will activate as its key
	///
	void Register(AlarmMarker* am);
	///
	/// \brief Remove an Alarm from the map
	///
	void Deregister(AlarmMarker* am);
	///
	/// \brief Clears the manager for deletion
	///
	void Delete();
};

#endif _AlarmableManager