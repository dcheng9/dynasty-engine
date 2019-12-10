#include "GodCamera.h"

#include "..\..\Dynasty Engine\Managers\ModelManager.h"
#include "..\..\Dynasty Engine\Managers\ShaderManager.h"
#include "..\..\Dynasty Engine\Managers\TextureManager.h"
#include "..\..\Dynasty Engine\Managers\CameraManager.h"
#include "..\..\Dynasty Engine\Managers\UpdatableManager.h"
#include "..\..\Dynasty Engine\Managers\DrawableManager.h"
#include "..\..\Dynasty Engine\Managers\SceneManager.h"

GodCamera::GodCamera()
{
	camPos = Vect(10.0f, 190.0f, -150.0f);
	camRotXDeg = 70.0f;
	camRotYDeg = 0.0f;
	camUp = Vect(0, 1, 0);
	camDir = Vect(0, 0, 1);

	moveUp = false;
	moveDown = false;
	moveLeft = false;
	moveRight = false;
	rotateUp = false;
	rotateDown = false;
	rotateLeft = false;
	rotateRight = false;
	zoomIn = false;
	zoomOut = false;
}

void GodCamera::SceneEntry()
{
	UpdateRegistration();
	KeyEventRegistration(KEY_ARROW_UP, KEY_PRESS);
	KeyEventRegistration(KEY_ARROW_DOWN, KEY_PRESS);
	KeyEventRegistration(KEY_ARROW_LEFT, KEY_PRESS);
	KeyEventRegistration(KEY_ARROW_RIGHT, KEY_PRESS);
	KeyEventRegistration(KEY_KP_8, KEY_PRESS);
	KeyEventRegistration(KEY_KP_2, KEY_PRESS);
	KeyEventRegistration(KEY_KP_4, KEY_PRESS);
	KeyEventRegistration(KEY_KP_6, KEY_PRESS);
	KeyEventRegistration(KEY_KP_ADD, KEY_PRESS);
	KeyEventRegistration(KEY_KP_SUBTRACT, KEY_PRESS);

	KeyEventRegistration(KEY_ARROW_UP, KEY_RELEASE);
	KeyEventRegistration(KEY_ARROW_DOWN, KEY_RELEASE);
	KeyEventRegistration(KEY_ARROW_LEFT, KEY_RELEASE);
	KeyEventRegistration(KEY_ARROW_RIGHT, KEY_RELEASE);
	KeyEventRegistration(KEY_KP_8, KEY_RELEASE);
	KeyEventRegistration(KEY_KP_2, KEY_RELEASE);
	KeyEventRegistration(KEY_KP_4, KEY_RELEASE);
	KeyEventRegistration(KEY_KP_6, KEY_RELEASE);
	KeyEventRegistration(KEY_KP_ADD, KEY_RELEASE);
	KeyEventRegistration(KEY_KP_SUBTRACT, KEY_RELEASE);
}

void GodCamera::SceneExit()
{
	UpdateDeregistration();
	KeyEventDeregistration(KEY_ARROW_UP, KEY_PRESS);
	KeyEventDeregistration(KEY_ARROW_DOWN, KEY_PRESS);
	KeyEventDeregistration(KEY_ARROW_LEFT, KEY_PRESS);
	KeyEventDeregistration(KEY_ARROW_RIGHT, KEY_PRESS);
	KeyEventDeregistration(KEY_KP_8, KEY_PRESS);
	KeyEventDeregistration(KEY_KP_2, KEY_PRESS);
	KeyEventDeregistration(KEY_KP_4, KEY_PRESS);
	KeyEventDeregistration(KEY_KP_6, KEY_PRESS);
	KeyEventDeregistration(KEY_KP_ADD, KEY_PRESS);
	KeyEventDeregistration(KEY_KP_SUBTRACT, KEY_PRESS);

	KeyEventDeregistration(KEY_ARROW_UP, KEY_RELEASE);
	KeyEventDeregistration(KEY_ARROW_DOWN, KEY_RELEASE);
	KeyEventDeregistration(KEY_ARROW_LEFT, KEY_RELEASE);
	KeyEventDeregistration(KEY_ARROW_RIGHT, KEY_RELEASE);
	KeyEventDeregistration(KEY_KP_8, KEY_RELEASE);
	KeyEventDeregistration(KEY_KP_2, KEY_RELEASE);
	KeyEventDeregistration(KEY_KP_4, KEY_RELEASE);
	KeyEventDeregistration(KEY_KP_6, KEY_RELEASE);
	KeyEventDeregistration(KEY_KP_ADD, KEY_RELEASE);
	KeyEventDeregistration(KEY_KP_SUBTRACT, KEY_RELEASE);
}

void GodCamera::Update()
{
	Matrix camRotX = Matrix(ROT_X, camRotXDeg);
	Matrix camRotY = Matrix(ROT_Y, camRotYDeg);

	Matrix camRot = camRotX * camRotY;

	if (moveUp)
		camPos += Vect(0, 1.0f, 0) * camRot * camTranSpeed;
	if (moveDown)
		camPos += Vect(0, -1.0f, 0) * camRot * camTranSpeed;
	if (moveLeft)
		camPos += Vect(1.0f, 0, 0) * camRot * camTranSpeed;
	if (moveRight)
		camPos += Vect(-1.0f, 0, 0) * camRot * camTranSpeed;

	if (rotateUp)
		camRotXDeg -= camRotSpeed;
	if (rotateDown)
		camRotXDeg += camRotSpeed;
	if (rotateLeft)
		camRotYDeg += camRotSpeed;
	if (rotateRight)
		camRotYDeg -= camRotSpeed;

	if (zoomIn)
		camPos += Vect(0, 0, 1.0f) * camRot * camTranSpeed;
	if (zoomOut)
		camPos += Vect(0, 0, -1.0f) * camRot * camTranSpeed;

	Vect lookAt = camPos + (camDir * camRot);
	SceneManager::GetCurrentCamera()->setOrientAndPosition(camUp * camRot, lookAt, camPos);
}

void GodCamera::KeyPressed(AZUL_KEY k)
{
	if (k == KEY_ARROW_UP)
		moveUp = true;
	else if (k == KEY_ARROW_DOWN)
		moveDown = true;
	else if (k == KEY_ARROW_LEFT)
		moveLeft = true;
	else if (k == KEY_ARROW_RIGHT)
		moveRight = true;

	if (k == KEY_KP_8)
		rotateUp = true;
	else if (k == KEY_KP_2)
		rotateDown = true;
	else if (k == KEY_KP_4)
		rotateLeft = true;
	else if (k == KEY_KP_6)
		rotateRight = true;

	if (k == KEY_KP_ADD)
		zoomIn = true;
	else if (k == KEY_KP_SUBTRACT)
		zoomOut = true;
}

void GodCamera::KeyReleased(AZUL_KEY k)
{
	if (k == KEY_ARROW_UP)
		moveUp = false;
	else if (k == KEY_ARROW_DOWN)
		moveDown = false;
	else if (k == KEY_ARROW_LEFT)
		moveLeft = false;
	else if (k == KEY_ARROW_RIGHT)
		moveRight = false;

	if (k == KEY_KP_8)
		rotateUp = false;
	else if (k == KEY_KP_2)
		rotateDown = false;
	else if (k == KEY_KP_4)
		rotateLeft = false;
	else if (k == KEY_KP_6)
		rotateRight = false;

	if (k == KEY_KP_ADD)
		zoomIn = false;
	else if (k == KEY_KP_SUBTRACT)
		zoomOut = false;
}