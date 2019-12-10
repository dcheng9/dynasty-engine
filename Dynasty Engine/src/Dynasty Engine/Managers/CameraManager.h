#ifndef _CameraManager
#define _CameraManager

#include "AzulCore.h"

class Camera;

///
///	\ingroup OtherManagerGroup
///
class CameraManager
{
private:
	Camera* currentCamera;

	friend class SceneManager;
	///
	/// \brief Clears the manager for deletion
	///
	void Delete();

public:
	~CameraManager();
	CameraManager();
	CameraManager(const CameraManager&) = delete;
	CameraManager& operator=(const CameraManager&) = delete;

	///
	/// \brief Set a new Camera for the current Scene
	///
	/// \param newCamera The new camera you want to change to
	/// 
	void SetCurrentCamera(Camera* newCamera);
	///
	/// \brief Updates the current camera
	///
	void UpdateCamera();
	///
	/// \brief Returns the current Scene's Camera
	///
	Camera* GetCurrentCamera();

};
#endif _CameraManager