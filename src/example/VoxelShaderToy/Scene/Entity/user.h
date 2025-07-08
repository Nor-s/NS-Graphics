#ifndef _NS_GRAPHICS_SCENE_ENTITY_USER_H_
#define _NS_GRAPHICS_SCENE_ENTITY_USER_H_

#include <nengine.h>

namespace vst
{
class User : public ns::UserEntity
{
private:
    struct CameraControlData
    {
	    ns::Vec2 startMousePos{};
	    ns::Vec2 beforeMousePos{};
	    ns::Vec3 beforeCameraPos{};
	    ns::Mat4 rotY{};
	    ns::Mat4 rotX{};
        float wheelSpeed{1.0f};
        float rotXSpeed{0.005f};
        float rotYSpeed{0.005f};
    };

public:
	virtual void setupInputController(ns::InputController* inputController);

	void onMoveDragStart(const ns::InputValue&);
	void onMoveDrag(const ns::InputValue&);
	void onMouseWheel(const ns::InputValue&);

private:
	// for camera
	ns::Camera* camera_;
	ns::Transform* r_transform_ = nullptr;
    CameraControlData cameraControlData_;
};
}	 // namespace vst

#endif