#ifndef _NS_GRAPHICS_CORE_ENTITY_COMPONENT_CAMERA_H_
#define _NS_GRAPHICS_CORE_ENTITY_COMPONENT_CAMERA_H_

#include "components.h"
#include "../../common/common.h"
#include "../../common/nsTransform.h"
#include "../../gpu/shaderInterop.h"

namespace ns
{

enum class CameraMode
{
	OrthoRH,
	PerspectRH
};

class Camera
{
public:
	const Mat4 getView() const
	{
		return lookAtRH(transform.position, target_, up_);
	}
	const Mat4 getProj() const
	{
		float width = static_cast<float>(res_.width);
		float height = static_cast<float>(res_.height);
		float halfWidth = width / 2.0f;
		float halfHeight = height / 2.0f;

		float orthoWidth = static_cast<float>(width) * (orthoFactor_ );
		float orthoHeight = static_cast<float>(height) * (orthoFactor_);

		switch (mode_)
		{
			case CameraMode::OrthoRH:
				return orthoRH(-orthoWidth, orthoWidth, -orthoHeight, orthoHeight, nearZ_, farZ_);
			case CameraMode::PerspectRH:
				return perspectiveRH(fovRadian_, height / width, nearZ_, farZ_);
			default:
				return orthoRH(-orthoWidth, orthoWidth, -orthoHeight, orthoHeight, nearZ_, farZ_);
		};
	}

	const float getOrthoFactor() const
	{
		return orthoFactor_;
	}
	Vec3& getMutableTarget()
	{
		return target_;
	}
	const Vec3& getTarget() const
	{
		return target_;
	}
	const float getFov() const
	{
		return fovRadian_;
	}
	const Vec3 getUp() const
	{
		return up_;
	}
	const Resolution& getRes() const 
	{
		return res_;
	}
	void setRes(const Resolution& res)
	{
		res_ = res;
	}
	void setOrthoFactor(float factor)
	{
		orthoFactor_ = factor;
		orthoFactor_ = std::max(std::min(1.0f, orthoFactor_), 1.0f/res_.width);
	}
	void setTarget(const Vec3& target)
	{
		target_ = target;
	}
	void setMode(CameraMode mode)
	{
		mode_ = mode;
	}
	void setFov(float radian)
	{
		fovRadian_ = radian;
	}
	void setPerspective()
	{
		setMode(CameraMode::PerspectRH);
	}
	void setOrtho()
	{
		setMode(CameraMode::OrthoRH);
	}
	const ShaderCameraInterop getCameraInterop() const
	{
		return ShaderCameraInterop{.view = getView(),
								   .proj = getProj(),
								   .eyeWorldPosition = transform.position,
								   .nearZ = nearZ_,
								   .up = up_,
								   .farZ = farZ_,
								   .atWorldPosition = target_,
								   .fov = fovRadian_};
	}
	Transform transform{};

private:
	Vec3 target_{0.0f, 0.0f, 0.0f};
	Vec3 up_{0.0f, 1.0f, 0.0f};
	CameraMode mode_{};
	Resolution res_{};
	float orthoFactor_{};
	float fovRadian_{M_PI / 4.0f};
	float nearZ_ = 1.0f;
	float farZ_ = 5e3f;
};

}	 // namespace ns
#endif