#include "Visualizer.h"
#include "BoundingSphere.h"
#include "..\Managers\ModelManager.h"
#include "..\Managers\ShaderManager.h"
#include "..\Managers\SceneManager.h"
#include "..\Scene\CommandVisualizerRender.h"
#include "..\Terrain\TerrainCell.h"

Visualizer* Visualizer::singleInst = NULL;

Visualizer::~Visualizer()
{

}

Visualizer::Visualizer()
{
	DEFAULT_COLOR = { 0, 0, 0 };
	WFUnitSphere = new GraphicsObject_WireframeConstantColor(ModelManager::GetModel("modelBoundingSphere"), ShaderManager::GetShader("shaderConstColor"), DEFAULT_COLOR);
	WFUnitBox = new GraphicsObject_WireframeConstantColor(ModelManager::GetModel("modelBoundingBox"), ShaderManager::GetShader("shaderConstColor"), DEFAULT_COLOR);
}

void Visualizer::Delete()
{
	if (Instance().WFUnitSphere != NULL)
		delete Instance().WFUnitSphere;
	if (Instance().WFUnitBox != NULL)
		delete Instance().WFUnitBox;

	Instance().storage.clear();

	delete singleInst;
	singleInst = NULL;
}

void Visualizer::pRenderBS(CollisionVolume* cv, const Vect& col)
{
	Vect color = col;

	if (!cv->CheckColliding())
		WFUnitSphere->pWireColor->set(col);
	else
		WFUnitSphere->pWireColor->set(cv->GetCollidingColor());

	WFUnitSphere->SetWorld(cv->GetMatrix());
	WFUnitSphere->Render(SceneManager::GetCurrentCamera());

	cv->CollidingOff();
}

void Visualizer::pRenderAABBOBB(CollisionVolume* cv, const Vect& col)
{
	Vect color = col;

	if (!cv->CheckColliding())
		WFUnitBox->pWireColor->set(col);
	else
		WFUnitBox->pWireColor->set(cv->GetCollidingColor());

	WFUnitBox->SetWorld(cv->GetMatrix());
	WFUnitBox->Render(SceneManager::GetCurrentCamera());

	cv->CollidingOff();
}

void Visualizer::pRenderTerrainAABB(TerrainCell& cell)
{
	Matrix scale;
	Matrix trans;
	Matrix world;

	scale.set(SCALE, cell.GetMaxCorner() - cell.GetMinCorner());
	trans.set(TRANS, 0.5f * (cell.GetMaxCorner() + cell.GetMinCorner()));

	world = scale * trans;

	if (!cell.CheckColliding())
		WFUnitBox->pWireColor->set(Vect(0.0f, 0.0f, 1.0f, 0.0f));
	else
		WFUnitBox->pWireColor->set(cell.GetCollidingColor());

	WFUnitBox->SetWorld(world);
	WFUnitBox->Render(SceneManager::GetCurrentCamera());

	cell.CollidingOff();
}

void Visualizer::RenderBS(CollisionVolume* cv, const Vect& col)
{
	Instance().pRenderBS(cv, col);
}

void Visualizer::RenderAABBOBB(CollisionVolume* cv, const Vect& col)
{
	Instance().pRenderAABBOBB(cv, col);
}

void Visualizer::RenderTerrainAABB(TerrainCell& cell)
{
	Instance().pRenderTerrainAABB(cell);
}

void Visualizer::HighlightTerrain(const Vect& p)
{
	SceneManager::GetCurrentTerrain()->HighlightCell(p);
}

void Visualizer::HighlightTerrain(const BoundingSphere* cv)
{
	SceneManager::GetCurrentTerrain()->HighlightCellArea(cv);
}

void Visualizer::Register(CollisionVolume* cv, const Vect& col)
{
	Instance().storage.insert(new CommandVisualizerRender(cv, col));
}

void Visualizer::ProcessElements()
{
	for (CommandSet::iterator it = Instance().storage.begin(); it != Instance().storage.end(); it++)
	{
		(*it)->execute();
	}
}

void Visualizer::ClearVisualizer()
{
	for (CommandSet::iterator it = Instance().storage.begin(); it != Instance().storage.end(); it++)
	{
		delete (*it);
	}

	Instance().storage.clear();
}