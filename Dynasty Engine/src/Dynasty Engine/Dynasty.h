#ifndef DYNASTY_H
#define DYNASTY_H

#include "AzulCore.h"

///
/// \mainpage Beginner's Basic Tutorial
///
///	To get started, the user first needs to create definitions for GameInitialize and LoadAllResources
///
///	The following example shows LoadAllResources, which its purpose is to load all needed assets
///
///	\par Example:
///
///		This example shows loading Models, Shaders, Textures, and Terrains, also note to set the Scene that the game will start with
///
///		\code
///		#include "..\Dynasty Engine\Dynasty.h"
///		#include "..\Dynasty Engine\Managers\ModelManager.h"
///		#include "..\Dynasty Engine\Managers\ShaderManager.h"
///		#include "..\Dynasty Engine\Managers\TextureManager.h"
///		#include "..\Dynasty Engine\Managers\TerrainManager.h"
///
///		#include "..\Dynasty Engine\Managers\SceneManager.h"
///
///		#include "Scenes\IntroScene.h"
///
///		void Dynasty::LoadResources()
///		{
///			//---------------------------------------------------------------------------------------------------------
///			// Load the Models
///			//---------------------------------------------------------------------------------------------------------
///
///			ModelManager::LoadModel("modelBoundingSphere", "BoundingSphere.azul");
///			ModelManager::LoadModel("modelSpaceFrigate", "space_frigate.azul");
///
///			//---------------------------------------------------------------------------------------------------------
///			// Load the Textures
///			//---------------------------------------------------------------------------------------------------------
///
///			TextureManager::LoadTexture("textSpaceFrigate", "space_frigate.tga");
///
///			//---------------------------------------------------------------------------------------------------------
///			// Load the Shaders
///			//---------------------------------------------------------------------------------------------------------
///
///			ShaderManager::LoadShader("shaderFlat", "textureFlatRender");
///			ShaderManager::LoadShader("shaderConstColor", "colorConstantRender");
///
///			//---------------------------------------------------------------------------------------------------------
///			// Load the Terrains
///			//---------------------------------------------------------------------------------------------------------
///
///			TerrainManager::LoadTerrain("terrainLevel0", "testHeightMap.tga", 500, 30, 0, "textGrid", 1, 1);
///			TerrainManager::LoadTerrain("terrainLevel1", "testComplexHeightMap.tga", 500, 40, 0, "textGrid", 1, 1);
///
///			SceneManager::SetScene(new IntroScene);
///		}
///		\endcode
///
///	Next you need to define GameInitialize which sets up game window settings
///
///	\par Example:
///
///		This example shows a basic setup
///
///		\code
///		#include "..\Dynasty Engine\Dynasty.h"
///		#include "..\Dynasty Engine\Managers\ModelManager.h"
///		#include "..\Dynasty Engine\Managers\ShaderManager.h"
//		#include "..\Dynasty Engine\Managers\TextureManager.h"
///
///		#include "..\Dynasty Engine\Managers\SceneManager.h"
///
///		#include "Scenes\IntroScene.h"
///
///		void Dynasty::GameInitialize()
///		{
///			DebugMsg::out("Game() started\n");
///
///			// Game Window Device setup
///			Dynasty::SetWindowName("Dynasty Engine Test");
///			Dynasty::SetWidthHeight(800, 600);
///			Dynasty::SetClear(0.4f, 0.4f, 0.8f, 1.0f);
///		}
///		\endcode
///
///	Now to set up your first scene, this is where you create GameObjects and add them into the scene,
///	as well as where you set up what happens when the scene ends
///
/// \par Header:
///
///		\code
///		#include "..\..\Dynasty Engine\Scene\Scene.h"
///
///		class Box;
///
///		class IntroScene : public Scene
///		{
///		public:
///			IntroScene(){};
///			virtual ~IntroScene(){};
///			IntroScene(const IntroScene&) = delete;
///			IntroScene& operator=(const IntroScene&) = delete;
///
///		private:
///
///			virtual void Initialize() override;
///			virtual void SceneEnd() override;
///
///			Box* testBox;
///		};
///		\endcode
///
///	\par Definition:
///
///		\code
///		#include "IntroScene.h"
///
///		#include "..\..\Dynasty Engine\Game Object\GameObject.h"
///
///		#include "..\Objects\Box.h"
///
///		void IntroScene::Initialize()
///		{
///			testBox = new Box();
///		
///			AddToScene(testBox);
///		}
///
///		void IntroScene::SceneEnd()
///		{
///			testBox->MarkForSceneExit();
///		}
///		\endcode
///
///	Now you can begin creating any GameObjects you want
///
///	\par Example:
///	
///		This is a basic Box GameObject that rotates constantly and if you press "E" it changes to the next scene
///
///	\par Header:
///
///		\code
///		#include "AzulCore.h"
///		#include "..\..\Dynasty Engine\Game Object\GameObject.h"
///
///		class Box : public GameObject
///		{
///		private:
///			GraphicsObject_WireframeConstantColor *pGObj_AzulBox;
///
///			virtual void SceneEntry() override;
///			virtual void SceneExit() override;
///
///		public:
///			Box();
///			~Box();
///
///			float angle;
///
///			virtual void Update() override;
///			virtual void Draw() override;
///			virtual void KeyPressed(AZUL_KEY k) override;
///		};
///		\endcode
///
///	\par Definition:
///
///		\code
///		#include "Box.h"
///
///		#include "..\..\Dynasty Engine\Managers\ModelManager.h"
///		#include "..\..\Dynasty Engine\Managers\ShaderManager.h"
///		#include "..\..\Dynasty Engine\Managers\TextureManager.h"
///		#include "..\..\Dynasty Engine\Managers\CameraManager.h"
///		#include "..\..\Dynasty Engine\Managers\UpdatableManager.h"
///		#include "..\..\Dynasty Engine\Managers\DrawableManager.h"
///		#include "..\..\Dynasty Engine\Managers\SceneManager.h"
///
///		#include "..\Scenes\SceneTest.h"
///
///		void Box::SceneEntry()
///		{
///			DebugMsg::out("Box Entering Scene \n");
///
///			UpdateRegistration();
///			DrawRegistration();
///			KeyEventRegistration(KEY_E, KEY_PRESS);
///		}
///
///		void Box::SceneExit()
///		{
///			DebugMsg::out("Box Exiting Scene \n");
///
///			UpdateDeregistration();
///			DrawDeregistration();
///			KeyEventDeregistration(KEY_E, KEY_PRESS);
///		}
///
///		Box::Box()
///		{
///			Vect Yellow(1.0f, 1.0f, 0.0f);
///			pGObj_AzulBox = new GraphicsObject_WireframeConstantColor(ModelManager::GetModel("modelBoundingBox"), ShaderManager::GetShader("shaderConstColor"), Yellow);
///
///			angle = 0.0f;
///		}
///
///		Box::~Box()
///		{
///			UpdateDeregistration();
///			DrawDeregistration();
///			KeyEventDeregistration(KEY_E, KEY_PRESS);
///
///			DebugMsg::out("Box Exiting Scene \n");
///		}
///
///		void Box::Update()
///		{
///			Matrix world;
///			Matrix Rot;
///			Matrix Scale;
///			Matrix Trans;
///
///			angle += 0.02f;
///
///			Scale.set(SCALE, 10, 10, 10);
///			Rot = Matrix(ROT_Y, angle) * Matrix(ROT_Z, 0.25f*angle);
///			Trans.set(TRANS, 40, 30, 0);
///			world = Scale * Rot * Trans;
///			pGObj_AzulBox->SetWorld(world);
///		}
///
///		void Box::Draw()
///		{
///			pGObj_AzulBox->Render(GetSceneCamera());
///		}
///
///		void Box::KeyPressed(AZUL_KEY k)
///		{
///			if (k == KEY_E)
///			{
///				DebugMsg::out("Changing Scene \n");
///				SceneManager::SetNextScene(new SceneTest);
///			}
///		}
///		\endcode
///
///	Any GameObjects you want to make can follow this basic format no matter what functions you want
///
///	Have fun!
///

///
/// \page Advanced Advanced Mechanics Tutorial
///
///	This will show the user how to set up Terrain and Collisions for a Scene
///
///	The following example shows a Scene that sets up a Terrain and collisions
///
///	\par Example:
///
///		To set a Terrain for the Scene, simply call SetTerrain() at the beginning of the Scene's Initialize().
///		To set up Collisions with GameObjects, put the appropriate Collision calls at the end of Initialize().
///		SetCollisionPair<>() checks between two GameObjects, SetCollisionSelf<>() checks between GameObjects of the same class,
///		and SetCollisionTerrain<>() checks between a GameObject and the Terrain you set for the Scene.
///
///		\code
///		#include "SceneTest.h"
///
///		#include "..\..\Dynasty Engine\Game Object\GameObject.h"
///		#include "..\Objects\Spaceship.h"
///		#include "..\Objects\Cottage.h"
///		#include "..\..\Dynasty Engine\Managers\CameraManager.h"
///
///		void SceneTest::Initialize()
///		{
///			// Orient Camera
///			Vect up3DCam(0.0f, 1.0f, 0.0f);
///			Vect pos3DCam(-50.0f, 200.0f, 0.0f);
///			Vect lookAt3DCam(-40.0f, -20.0f, 0.0f);
///			GetCameraManager().GetCurrentCamera()->setOrientAndPosition(up3DCam, lookAt3DCam, pos3DCam);
///			GetCameraManager().GetCurrentCamera()->updateCamera();
///
///			SetTerrain("terrainLevel1");
///
///			Vect shipPos1 = Vect(0, 35, -100);
///			testSpaceship = new Spaceship(shipPos1);
///
///			Vect cottagePos1 = Vect(-50, 20, 0);
///			testCottage1 = new Cottage(cottagePos1);
///
///			AddToScene(testSpaceship);
///
///			AddToScene(testCottage1);
///
///			SetCollisionPair<Spaceship, Cottage>();
///			SetCollisionSelf<Spaceship>();
///			SetCollisionSelf<Cottage>();
///			SetCollisionTerrain<Spaceship>();
///		}
///		\endcode
///
///	Next, set up your GameObject to work with collisions
///
/// The following example shows relevant information dealing with collision set up
///
///	\par Example:
///
///		In SceneEntry(), call for the GameObject to register it's collision.
///		Also note the use of the Visualizer tool for a visualized model in the shape of the GameObject's ColliderModel
///
///		\code
///		#include "Spaceship.h"
///		#include "..\..\Dynasty Engine\Collider\Visualizer.h"
///
///		#include "..\..\Dynasty Engine\Collider\BoundingSphere.h"
///		#include "..\..\Dynasty Engine\Collider\AABB.h"
///		#include "..\..\Dynasty Engine\Collider\OBB.h"
///
///		void Spaceship::SceneEntry()
///		{
///			CollisionRegistration<Spaceship>(this);
///		
///			Visualizer::Register(cVolume, Vect(0.0f, 0.0f, 0.0f, 0.0f));
///			Visualizer::Register(GetBSphere(), Vect(0.0f, 0.0f, 0.0f, 0.0f));
///		}
///		
///		void Spaceship::SceneExit()
///		{
///			CollisionDeregistration<Spaceship>(this);
///		}
///		\endcode
///
///		In the constructor, call to set the ColliderModel and update the CollisionData.
///		There different types of ColliderModels you can try out to fit your needs:
///		BoundingSphere - Sphere that is draw from the center of your model to the edge of the model.
///		Axis Aligned Bounding Box (AABB) - Box that is constantly changing its dimensions so that the edges are always at the model's farthest points.
///		Oriented Bounding Box (OBB) - Box with fixed dimensions based on the model's farthest points that follows and rotates with your model.
///
///		\code
///		Spaceship::Spaceship(Vect& startPosition)
///		{
///			SetColliderModel(pGObj_SpaceshipWithTexture->getModel(), AABBtype);
///			UpdateCollisionData(pGObj_SpaceshipWithTexture->getWorld());
///		}
///		\endcode
///
///		Also update the CollisionData in the Update()!
///
///		\code
///		void Spaceship::Update()
///		{
///			ShipPos += Vect(0, 0, 1) * ShipRot * ShipTransSpeed * ShipForwardSpeed;
///			ShipRot *= Matrix(ROT_Y, ShipTurnSpeed);
///
///			Matrix world = ShipScale * ShipRot * Matrix(TRANS, ShipPos);
///
///			UpdateCollisionData(world);
///		}
///		\endcode
///
///		Another Visualizer tool in Draw(), using this function will highlight the Terrain directly below the GameObject
///
///		\code
///		void Spaceship::Draw()
///		{
///			Visualizer::HighlightTerrain(GetBSphere());
///		}
///		\endcode
///
///		Finally, program the Collision() function to set the GameObject's behavior when it triggers collision.
///		Also note that if you set up Terrain collision, you can use the CollisionTerrain() function to program that behavior.
///
///		\code
///		void Spaceship::Collision(Cottage*)
///		{
///			DebugMsg::out("Collision Spaceship with Cottage\n");
///		}
///		\endcode
///
///		That's all you need to do to set up Terrain and Collisions!
///
///		Good luck!
///

///
///	\defgroup GameObjectGroup User Defined Game Object
///		
///		Everything pertaining to defining and using GameObjects that the user need to know about
///
///	\defgroup OtherUserDefGroup User Defined Stuff
///
///		Miscellaneous classes and functions the user needs to define before the game will run
///
///	\defgroup UsefulTools Useful Tools
///
///		Debugging Tools that may help the user, mostly for collision
///
///	\defgroup GameObjectManagerGroup Game Object Managers
///
///		Managers that keep track of all the functions of GameObject
///
///	\defgroup AssetManagerGroup Asset Managers
///
///		Managers that keep track of asset creation and loading
///
///	\defgroup OtherManagerGroup Other Managers
///
///		Miscellaneous managers that keep track of other systems within the game
///
///	\defgroup OtherInternalGroup Other Internal Stuff
///
///		Miscellaneous classes mainly used in the internal engine
///

///
///	\ingroup OtherInternalGroup
///
class Dynasty : public Engine
{
private:
	~Dynasty() {};
	static Dynasty* singleInst;

	Dynasty() {};
	Dynasty(const Dynasty&) = delete;
	Dynasty& operator=(const Dynasty&) = delete;

	static Dynasty& Instance()
	{
		if (!singleInst)
			singleInst = new Dynasty();
		return *singleInst;
	};

	///
	/// \brief Call GameInitialize
	///
	virtual void Initialize();
	///
	/// \brief Call LoadResources
	///
	virtual void LoadContent();
	///
	/// \brief Call the SceneManager's Update
	///
	virtual void Update();
	///
	/// \brief Call the SceneManager's Draw
	///
	virtual void Draw();
	///
	/// \brief Call all the singleton managers' Delete function
	///
	virtual void UnLoadContent();


public:
	// Methods Users need to overload in their game

	///
	///	\ingroup OtherUserDefGroup
	///
	/// \brief User defined where all Models, Shaders, and Textures are loaded
	///
	///	\par Example:
	///
	///		This example shows loading Models, Shaders, and Textures, also note to set the Scene that the game will start with
	///
	///		\code
	///		void Dynasty::LoadResources()
	///		{
	///			//---------------------------------------------------------------------------------------------------------
	///			// Load the Models
	///			//---------------------------------------------------------------------------------------------------------
	///
	///			ModelManager::LoadModel("modelBoundingSphere", "BoundingSphere.azul");
	///			ModelManager::LoadModel("modelSpaceFrigate", "space_frigate.azul");
	///
	///			//---------------------------------------------------------------------------------------------------------
	///			// Load the Textures
	///			//---------------------------------------------------------------------------------------------------------
	///
	///			TextureManager::LoadTexture("textSpaceFrigate", "space_frigate.tga");
	///
	///			//---------------------------------------------------------------------------------------------------------
	///			// Load the Shaders
	///			//---------------------------------------------------------------------------------------------------------
	///
	///			ShaderManager::LoadShader("shaderFlat", "textureFlatRender");
	///			ShaderManager::LoadShader("shaderConstColor", "colorConstantRender");
	///
	///			//---------------------------------------------------------------------------------------------------------
	///			// Load the Terrains
	///			//---------------------------------------------------------------------------------------------------------
	///
	///			TerrainManager::LoadTerrain("terrainLevel0", "testHeightMap.tga", 500, 30, 0, "textGrid", 1, 1);
	///			TerrainManager::LoadTerrain("terrainLevel1", "testComplexHeightMap.tga", 500, 40, 0, "textGrid", 1, 1);
	///
	///			SceneManager::SetScene(new IntroScene);
	///		}
	///		\endcode
	///
	static void LoadResources();
	///
	///	\ingroup OtherUserDefGroup
	///
	/// \brief User defined to set up the game window
	///
	///	\par Example:
	///
	///		This example shows a basic setup
	///
	///		\code
	///		void Dynasty::GameInitialize()
	///		{
	///			DebugMsg::out("Game() started\n");
	///
	///			// Game Window Device setup
	///			Dynasty::SetWindowName("Dynasty Engine Test");
	///			Dynasty::SetWidthHeight(800, 600);
	///			Dynasty::SetClear(0.4f, 0.4f, 0.8f, 1.0f);
	///		}
	///		\endcode
	///
	static void GameInitialize();

	static void Run();
	static float GetTime();
	static int GetWidth();
	static int GetHeight();
	static void SetWindowName(const char* name);
	static void SetWidthHeight(int w, int h);
	static void SetClear(float r, float g, float b, float a);
};

#endif