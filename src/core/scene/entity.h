#ifndef _NS_GRAPHICS_CORE_SCENE_ENTITY_H_
#define _NS_GRAPHICS_CORE_SCENE_ENTITY_H_

#include "../common/common.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace ns
{

class Entity
{
public:
	void setPosition(const Vec3& position)
	{
		transform_.position = position;
	}
	const Transform& getTransform() const
	{
		return transform_;
	}
	Transform& getMutableTransform()
	{
		return transform_;
	}

protected:
	Transform transform_;
};

class CameraEntity : public Entity
{
	enum class Mode
	{
		OrthoRH
	};

public:
	Mat4 getView() const
	{
		return lookAtRH(transform_.position, target_, up_);
	}
	Mat4 getProj() const
	{
		float width = static_cast<float>(res_.width);
		float height = static_cast<float>(res_.height);
		float halfWidth = width / 2.0f;
		float halfHeight = height / 2.0f;
		float nearZ = 1.0f;
		float farZ = 5e3f;
		float orthoWidth = static_cast<float>(halfWidth) / (orthoFactor_.x * 0.5f);
		float orthoHeight = static_cast<float>(halfHeight) / (orthoFactor_.y * 0.5f);

		switch (mode_)
		{
			case Mode::OrthoRH:
			default:
				return orthoRH(-orthoWidth, orthoWidth, -orthoHeight, orthoHeight, nearZ, farZ);
		};
	}
	void setRes(const Resolution& res)
	{
		res_ = res;
	}
	void setOrthoFactor(const Vector2<float>& res)
	{
		orthoFactor_ = res;
	}
	const Vector2<float> getOrthoFactor() const
	{
		return orthoFactor_;
	}
	void setTarget(const Vec3& target)
	{
		target_ = target;
	}
	const Vec3& getTarget() const
	{
		return target_;
	}
	Vec3& getMutableTarget()
	{
		return target_;
	}

private:
	Vec3 target_{0.0f, 0.0f, 0.0f};
	Vec3 up_{0.0f, 1.0f, 0.0f};
	Mode mode_;
	Resolution res_;
	Vector2<float> orthoFactor_;
};

}	 // namespace ns

#endif
