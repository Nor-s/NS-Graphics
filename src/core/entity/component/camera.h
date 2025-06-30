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

		float orthoWidth = static_cast<float>(halfWidth) / (orthoFactor_.x * 0.5f);
		float orthoHeight = static_cast<float>(halfHeight) / (orthoFactor_.y * 0.5f);

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

	const Vector2<float> getOrthoFactor() const
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
	void setRes(const Resolution& res)
	{
		res_ = res;
	}
	void setOrthoFactor(const Vector2<float>& res)
	{
		orthoFactor_ = res;
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
    ShaderCameraInterop getShaderCamera()
    {
        return ShaderCameraInterop{
            .view = getView(),
            .proj = getProj(), 
            .worldPosition =transform.position,
            .nearZ = nearZ_,
            .up = up_,
            .farZ = farZ_,
            .atWorldPosition = target_,
            .fov = fovRadian_
        };
    }
    Transform transform{};

private:
	Vec3 target_{0.0f, 0.0f, 0.0f};
	Vec3 up_{0.0f, 1.0f, 0.0f};
	CameraMode mode_{};
	Resolution res_{};
	Vec2 orthoFactor_{};
	float fovRadian_{M_PI / 4.0f};
	float nearZ_ = 1.0f;
	float farZ_ = 5e3f;
};

}	 // namespace ns
#endif