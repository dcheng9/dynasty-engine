#ifndef _Visualizer
#define _Visualizer

#include "AzulCore.h"
#include "..\Managers\ModelManager.h"
#include "..\Managers\ShaderManager.h"
#include <set>

class CollisionVolume;
class CommandBase;
class BoundingSphere;
class AABB;
class TerrainCell;

///
///	\ingroup UsefulTools
///
class Visualizer
{
private:
	~Visualizer();
	static Visualizer* singleInst;

	Visualizer();
	Visualizer(const Visualizer&) = delete;	// Prevent copy-construction
	Visualizer& operator=(const Visualizer&) = delete;	// Prevent assignment

	static Visualizer& Instance()		// Access reference (all public methods will be static)
	{
		if (!singleInst)
			singleInst = new Visualizer();
		return *singleInst;
	};

	typedef std::set<CommandBase*> CommandSet;
	CommandSet storage;

	Vect DEFAULT_COLOR;
	GraphicsObject_WireframeConstantColor *WFUnitSphere = NULL;
	GraphicsObject_WireframeConstantColor *WFUnitBox = NULL;

	bool checkCol = false;

	friend class Dynasty;
	///
	/// \brief Clears the Visualizer for deletion
	///
	static void Delete();

	void pRenderBS(CollisionVolume* cv, const Vect& col);
	void pRenderAABBOBB(CollisionVolume* cv, const Vect& col);
	void pRenderTerrainAABB(TerrainCell& cell);

public:

	///
	/// \brief Called to draw a BoundingSphere around the GameObject
	///
	/// \param mod The GameObject's BoundingSphere
	///	\param col The color you want the BoundingSphere to be
	/// 
	/// \par Example:
	///
	///		\code
	///		void Spaceship::Draw()
	///		{
	///			Visualizer::RenderBS(bSphere, Vect(0, 0, 1.0f));
	///		}
	///		\endcode
	///
	static void RenderBS(CollisionVolume* cv, const Vect& col);

	///
	/// \brief Called to draw a AABB or OBB around the GameObject
	///
	static void RenderAABBOBB(CollisionVolume* cv, const Vect& col);

	///
	/// \brief Called by the system to draw a AABBs mapping to cell min and max points on a terrain
	///
	static void RenderTerrainAABB(TerrainCell& cell);

	///
	///	\ingroup UsefulTools
	///
	///
	/// \brief Called by the user to draw an AABB of TerrainCell under a GameObject
	///
	/// \param p The GameObject's position
	///
	static void HighlightTerrain(const Vect& p);

	///
	///	\ingroup UsefulTools
	///
	///
	/// \brief Called by the user to draw the AABBs of TerrainCells under a GameObject
	///
	/// \param cv The GameObject's BoundingSphere
	/// 
	/// \par Example:
	///
	///		\code
	///		void Spaceship::Draw()
	///		{
	///			Visualizer::HighlightTerrain(GetBSphere());
	///		}
	///		\endcode
	///
	static void HighlightTerrain(const BoundingSphere* cv);

	///
	///	\ingroup UsefulTools
	///
	///
	/// \brief Register an Object's CollisionVolume
	///
	static void Register(CollisionVolume* cv, const Vect& col);

	///
	/// \brief Iterate through the set and call execute on each item
	///
	static void ProcessElements();

	static void ClearVisualizer();
};

#endif _Visualizer