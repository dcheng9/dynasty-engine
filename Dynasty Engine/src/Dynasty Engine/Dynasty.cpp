#include "AzulCore.h"
#include "Dynasty.h"

#include "Managers\ShaderManager.h"
#include "Managers\TextureManager.h"
#include "Managers\ModelManager.h"
#include "Managers\TerrainManager.h"
#include "Managers\CameraManager.h"
#include "Managers\SceneManager.h"
#include "Managers\TimeManager.h"
#include "Collider\Visualizer.h"

Dynasty* Dynasty::singleInst = NULL;

// Global variables just for the demo:

//-----------------------------------------------------------------------------
// Game::Initialize()
//		Allows the engine to perform any initialization it needs to before 
//      starting to run.  This is where it can query for any required services 
//      and load any non-graphic related content. 
//-----------------------------------------------------------------------------
void Dynasty::Initialize()
{
	this->GameInitialize();
}

//-----------------------------------------------------------------------------
// Game::LoadContent()
//		Allows you to load all content needed for your engine,
//	    such as objects, graphics, etc.
//-----------------------------------------------------------------------------
void Dynasty::LoadContent()
{
	//---------------------------------------------------------------------------------------------------------
	// Load Models, Shaders, Textures
	//---------------------------------------------------------------------------------------------------------

	this->LoadResources();
}

//-----------------------------------------------------------------------------
// Game::Update()
//      Called once per frame, update data, tranformations, etc
//      Use this function to control process order
//      Input, AI, Physics, Animation, and Graphics
//-----------------------------------------------------------------------------
void Dynasty::Update()
{
	SceneManager::Update();
}

//-----------------------------------------------------------------------------
// Game::Draw()
//		This function is called once per frame
//	    Use this for draw graphics to the screen.
//      Only do rendering here
//-----------------------------------------------------------------------------
void Dynasty::Draw()
{
	SceneManager::Draw();
}

//-----------------------------------------------------------------------------
// Game::UnLoadContent()
//       unload content (resources loaded above)
//       unload all content that was loaded before the Engine Loop started
//-----------------------------------------------------------------------------
void Dynasty::UnLoadContent()
{
	// Clear all managers
	SceneManager::Delete();
	Visualizer::Delete();
	ShaderManager::Delete();
	TextureManager::Delete();
	ModelManager::Delete();
	TerrainManager::Delete();
	TimeManager::Delete();

	DebugMsg::out("Game() ended\n");

	delete singleInst;
	singleInst = NULL;
}

void Dynasty::Run(){ Instance().run(); }
float Dynasty::GetTime(){ return Instance().GetTimeInSeconds(); }
int Dynasty::GetWidth(){ return Instance().getWidth(); }
int Dynasty::GetHeight(){ return Instance().getHeight(); }
void Dynasty::SetWindowName(const char* name){ Instance().setWindowName(name); }
void Dynasty::SetWidthHeight(int w, int h){ Instance().setWidthHeight(w, h); }
void Dynasty::SetClear(float r, float g, float b, float a){ Instance().SetClearColor(r, g, b, a); }


