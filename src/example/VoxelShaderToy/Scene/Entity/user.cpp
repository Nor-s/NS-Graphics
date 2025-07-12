#include "user.h"


namespace vst
{

void User::setupInputController(ns::InputController* inputController)
{
	inputController->bindAction(ns::InputAction(ns::InputType::MOUSE_LEFT_DOWN), ns::InputTrigger::Started, this,
								&User::onMoveDragStart);

	inputController->bindAction(ns::InputAction(ns::InputType::MOUSE_LEFT_DOWN), ns::InputTrigger::Triggered, this,
								&User::onMoveDrag);

	inputController->bindAction(ns::InputAction(ns::InputType::MOUSE_WHEEL), ns::InputTrigger::Triggered, this,
								&User::onMouseWheel);

	camera_ =  &addComponent<ns::CameraComponent>().camera;
	camera_->setTarget({0.0f,0.0f,0.0f});
	camera_->setPerspective();
	camera_->transform.position = {1000.0f,1000.0f,1000.0f};
	r_transform_ = &camera_->transform;//getComponent<ns::TransformComponent>().transform;
}

void User::onMoveDragStart(const ns::InputValue& value)
{
	cameraControlData_.startMousePos = value.get<ns::Vec2>();
	cameraControlData_.beforeMousePos = value.get<ns::Vec2>();
	cameraControlData_.beforeCameraPos = r_transform_->position;
	cameraControlData_.rotY = ns::Mat4();
}

void User::onMoveDrag(const ns::InputValue& value)
{
	auto currentMousePos = value.get<ns::Vec2>();
    auto& cd = cameraControlData_;
	auto delta = currentMousePos - cd.startMousePos;
	auto cacheDeltaY = currentMousePos.y - cd.beforeMousePos.y;
	cd.beforeMousePos = currentMousePos;

	delta.x *= -cd.rotXSpeed;
	delta.y *= -cd.rotXSpeed;

	auto at = camera_->getTarget();
	auto up = camera_->getUp();
	auto eye = cd.beforeCameraPos;
	auto relCameraPos = eye - at;

	auto forwardDir = ns::normalize(relCameraPos);
	auto rightDir = ns::normalize(ns::cross(up, forwardDir));
	auto upDir = ns::normalize(ns::cross(forwardDir, rightDir));

	auto rotY = ns::rotate(ns::Mat4(), rightDir, delta.y);
	auto rotX = ns::rotateY(ns::Mat4(), delta.x);
	auto nextPos = rotY * ns::Vec4(cd.beforeCameraPos, 1.0f);

	auto nextDot = static_cast<ns::Vec3>(ns::normalize(nextPos)) * ns::Vec3(0.0f, 1.0f, 0.0f);
	if (abs(nextDot) > 0.95f)
	{
		cd.startMousePos.y += cacheDeltaY;
		camera_->transform.position = rotX * cd.rotY * ns::Vec4(cd.beforeCameraPos, 1.0f);
		return;
	}
	cd.rotY = rotY;

	camera_->transform.position = rotX * rotY * ns::Vec4(cd.beforeCameraPos, 1.0f);
}

void User::onMouseWheel(const ns::InputValue& value)
{
	static const float lengthThreshold = 30.0f;
	float x = value.get<float>();
	auto& at = camera_->getTarget();
	auto& eye = camera_->transform.position;

	auto cameraRelativePos = eye - at;
	auto forwardDir = ns::normalize(cameraRelativePos);

	auto factor = cameraControlData_.wheelSpeed;
	auto nextRelativePosition = forwardDir * factor * x + cameraRelativePos;

	if (ns::length2(nextRelativePosition) > lengthThreshold)
	{
		camera_->transform.position = nextRelativePosition + at;
	}
}

}	 // namespace vst