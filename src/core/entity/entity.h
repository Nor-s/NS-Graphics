#ifndef _NS_GRAPHICS_CORE_SCENE_ENTITY_H_
#define _NS_GRAPHICS_CORE_SCENE_ENTITY_H_

#include <concepts>
#include <vector>
#include <memory>

#include "../common/common.h"
#include "component/component.h"

namespace ns
{

class Entity
{
public:
	virtual ~Entity() = default;

	virtual void onAwake(){}
	virtual void onStart(){}
	virtual void onEnable(){}
	virtual void onUpdate(){
		for(auto& component: components_)
		{
			component->update();
		}
	}
	virtual void onLateUpdate(){}
	virtual void onRender(){
		for(auto& component: components_)
		{
			component->render();
		}
	}
	virtual void onDisable(){}
	virtual void onDestroy(){}

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

    template <class T>
    T *getComponent()
    {
        for (const auto &component : components_)
        {
            if (component->getType() == T::type)
            {
                return static_cast<T *>(component.get());
            }
        }
        return nullptr;
    }
    template <typename T>
    T *addComponent()
    {
        if (auto *component = getComponent<T>(); component)
        {
            return component;
        }
        auto component = std::make_unique<T>();
        auto *ret = component.get();
        ret->owner_ = this;

        components_.push_back(std::move(component));
        return ret;
    }

protected:
	Transform transform_;
    std::vector<std::unique_ptr<Component>> components_;

};

class CameraEntity : public Entity
{
public:
	enum class Mode
	{
		OrthoRH,
		PerspectRH
	};

public:
	const Mat4 getView() const
	{
		return lookAtRH(transform_.position, target_, up_);
	}
	const Mat4 getProj() const
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
				return orthoRH(-orthoWidth, orthoWidth, -orthoHeight, orthoHeight, nearZ, farZ);
			case Mode::PerspectRH:
				return perspectiveRH(fovRadian_, height / width, nearZ, farZ);
			default:
				return orthoRH(-orthoWidth, orthoWidth, -orthoHeight, orthoHeight, nearZ, farZ);
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
	void setMode(Mode mode)
	{
		mode_ = mode;
	}
	void setFov(float radian)
	{
		fovRadian_ = radian;
	}
	void setPerspective()
	{
		setMode(Mode::PerspectRH);
	}
	void setOrtho()
	{
		setMode(Mode::OrthoRH);
	}

private:
	Vec3 target_{0.0f, 0.0f, 0.0f};
	Vec3 up_{0.0f, 1.0f, 0.0f};
	Mode mode_;
	Resolution res_;
	Vector2<float> orthoFactor_;
	float fovRadian_{M_PI / 4.0f};
};

}	 // namespace ns

#endif
