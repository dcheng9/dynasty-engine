#ifndef _GodCamera
#define _GodCamera

#include "AzulCore.h"
#include "..\..\Dynasty Engine\Game Object\GameObject.h"

class GodCamera : public GameObject
{
public:
	GodCamera();
	~GodCamera() = default;
	GodCamera(const GodCamera&) = delete;
	GodCamera& operator=(const GodCamera&) = delete;

	virtual void SceneEntry() override;
	virtual void SceneExit() override;

	void Update() override;

	virtual void KeyPressed(AZUL_KEY k) override;
	virtual void KeyReleased(AZUL_KEY k) override;

private:
	Vect camPos;
	float camRotXDeg;
	float camRotYDeg;
	Vect camUp;
	Vect camDir;
	float camTranSpeed = 5.0f;
	float camRotSpeed = 0.05f;

	bool moveUp;
	bool moveDown;
	bool moveLeft;
	bool moveRight;

	bool rotateUp;
	bool rotateDown;
	bool rotateLeft;
	bool rotateRight;

	bool zoomIn;
	bool zoomOut;
};

#endif _GodCamera