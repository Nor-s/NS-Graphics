#ifndef _LEARN_GL_EXAMPLE_H_
#define _LEARN_GL_EXAMPLE_H_

#include <cmath>
#include <core/entity/component/components.h>
#include <core/scene/nsScene.h>


#include <core/gpu/gl/glGeometry.h>
#include <core/gpu/gl/glShader.h>
#include <core/gpu/gl/glBuffer.h>
#include <common/common.h>
#include <editor/app.h>
#include <imgui.h>
#include <editor/imgui/imguiComponents.h>

#include <nengine.h>

#define GLGEOMETRY_CAST(geo) static_cast<ns::GlGeometry*>(geo.get())

struct ExEntity
{
	std::unique_ptr<ns::Geometry> cube = nullptr;
	ns::Transform transform;
};

class Example
{
public:
	virtual ~Example()
	{
		inputController_.reset();
	}
	virtual const std::string& toString() = 0;
	virtual void destroy(){};
    virtual void content()=0;
	virtual bool update(double deltaTime)
	{
		return false;
	}
	virtual void drawUIWidgets(){}
	virtual void drawUIWindows(){}
	ns::InputController* getInputController()
	{
		return inputController_.get();
	}
	virtual void onWindowResize(const ns::Resolution& res)
	{
		if(mainCamera_)
		{
			mainCamera_->setRes(res);
		}
	}

	void initCameraInputController()
	{
		using namespace ns::editor;
		auto res = App::GetAppContext().res;
		// set camera
		mainScene_.init(res);
		mainCameraEntity_ = ns::Scene::CreateEntity(&mainScene_, "camera");
		auto& cameraComponent = mainCameraEntity_.addComponent<ns::CameraComponent>();

		mainCamera_	= &cameraComponent.camera;
		mainCameraTransform_ = &mainCamera_->transform;
		
		mainCameraTransform_->position = {100, 100, 100};
		mainCamera_->setRes(res);
		mainCamera_->setOrthoFactor(0.1f);
		mainCamera_->setTarget({0.0, 0.0, 0.0});
		mainCamera_->setFov(ns::math::ToRadian(45.0f));
		mainCamera_->setPerspective();

		// input controller
		App::SetCurrentInputController(inputController_.get());
		inputController_ = std::make_unique<ns::InputController>();
		inputController_->bindAction(
			ns::InputAction(ns::InputType::MOUSE_LEFT_DOWN),
			ns::InputTrigger::Started,this,
			&Example::moveStartCamera
		);
		inputController_->bindAction(
			ns::InputAction(ns::InputType::MOUSE_LEFT_DOWN),
			ns::InputTrigger::Triggered,this,
			&Example::moveCamera
		);
		inputController_->bindAction(
			ns::InputAction(ns::InputType::MOUSE_LEFT_DOWN),
			ns::InputTrigger::Ended,this,
			&Example::moveEndCamera
		);
		inputController_->bindAction(
			ns::InputAction(ns::InputType::MOUSE_WHEEL),
			ns::InputTrigger::Triggered, this,
			&Example::moveWheel
		);
	}
	void moveStartCamera(const ns::InputValue& value)
	{
		bIsDragStart_ = true;
		startMousePos_ = value.get<ns::Vec2>();
		beforeMousePos_ = value.get<ns::Vec2>();
		beforeCameraPos_ = mainCameraTransform_->position; 
		rotY_ = ns::Mat4();
		NS_LOG("start camera, x {}, y {}", startMousePos_.x, startMousePos_.y);
	}
	void moveCamera(const ns::InputValue& value)
	{		
		if (!bIsDragStart_) return;

		auto currentMousePos = value.get<ns::Vec2>();
		auto delta =  currentMousePos - startMousePos_;
		auto cacheDeltaY = currentMousePos.y - beforeMousePos_.y;
		beforeMousePos_ = currentMousePos;

		// TODO: delta time and speed
		delta.x*= -0.005f;
		delta.y*= -0.005f;

		auto at = mainCamera_->getTarget();
		auto up = mainCamera_->getUp();
		auto eye = beforeCameraPos_;
		auto relCameraPos = eye - at;

		auto forwardDir = ns::normalize(relCameraPos);
		auto rightDir = ns::normalize(ns::cross(up, forwardDir));
		auto upDir = ns::normalize(ns::cross(forwardDir, rightDir));

		auto rotY = ns::rotate(ns::Mat4(), rightDir, delta.y);
		auto rotX = ns::rotateY(ns::Mat4(), delta.x);
		auto nextPos = rotY * ns::Vec4(beforeCameraPos_, 1.0f);

		auto nextDot = static_cast<ns::Vec3>(ns::normalize(nextPos)) * ns::Vec3(0.0f, 1.0f, 0.0f);
		if(abs(nextDot) > 0.95f)
		{
			startMousePos_.y += cacheDeltaY;
			mainCameraTransform_->position =  rotX * rotY_ * ns::Vec4(beforeCameraPos_, 1.0f);
		 	return;
		}
		rotY_ = rotY;

		mainCameraTransform_->position =   rotX * rotY * ns::Vec4(beforeCameraPos_, 1.0f);

		NS_LOG("move camera, x {}, y {}", delta.x, delta.y);
	}
	void moveEndCamera(const ns::InputValue& value)
	{
		bIsDragStart_ = false;
	}
	void moveWheel(const ns::InputValue& value)
	{
		auto currentMousePos = value.get<ns::Vec2>();
		float speed = 1.0f;
		float x = value.get<float>();

		auto at = mainCamera_->getTarget();
		auto up = mainCamera_->getUp();
		auto eye = mainCameraTransform_->position;
		auto relCameraPos = eye - at;
		auto forwardDir = ns::normalize(relCameraPos);

		auto next = forwardDir*speed*x + relCameraPos;

		if(ns::length2(next) > 30.0f)
		{
			mainCameraTransform_->position = next + at;
		}

		NS_LOG("move wheel, x {}", x);
	}
	void drawCameraUI()
	{
		using namespace ns::editor;

		ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate);

		// camera
		ImGuiEx::DragPropertyXYZ("camera pos", mainCameraTransform_->position.value, 1.0f, -400.0f, 400.0f);
		ImGuiEx::DragPropertyXYZ("target pos", mainCamera_->getMutableTarget().value, 0.1f, -10.0f, 10.0f);

		// ortho camera
		auto windowRes = App::GetAppContext().res;
		auto ortho = mainCamera_->getOrthoFactor();

		ImGui::Text("window width: %d, window height: %d", windowRes.width, windowRes.height);

		ImGui::Checkbox("Is Ortho", &bIsOrtho_);
		mainCamera_->setMode(bIsOrtho_ ? ns::CameraMode::OrthoRH : ns::CameraMode::PerspectRH);

		ImGui::DragFloat("ortho_factor", &ortho, 0.001f, 0.001f, 1.0f);

		mainCamera_->setOrthoFactor(ortho);

		if(ImGui::IsWindowFocused())
		{
			bIsDragStart_ = false;
			App::SetCurrentInputController(nullptr);
		}
		else
		{
			App::SetCurrentInputController(inputController_.get());
		}
	}

protected:
	std::unique_ptr<ns::InputController> inputController_;
	ns::Scene mainScene_{};
	ns::Entity mainCameraEntity_;
	ns::Camera* mainCamera_{nullptr};

	// for camera
	ns::Transform* mainCameraTransform_;
	ns::Vec2 startMousePos_;
	ns::Vec2 beforeMousePos_;
	ns::Vec3 beforeCameraPos_;
	ns::Mat4 rotY_;
	ns::Mat4 rotX_;
	bool bIsOrtho_ = false;
	float cameraSpeed_ = 0.0001f;

	bool bIsDragStart_ = false;
};

#endif