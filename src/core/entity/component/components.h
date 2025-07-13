#ifndef _NS_GRAPHICS_CORE_ENTITY_COMPONENTS_H_
#define _NS_GRAPHICS_CORE_ENTITY_COMPONENTS_H_

#include <memory>
#include "core/common/nsTransform.h"
#include "camera.h"
#include "core/gpu/geometry.h"
#include "callbackComponent.h"
#include "tags.h"
#include "nsMaterial.h"
#include "core/common/nsInterpolation.h"

namespace ns
{

class GlGeometry;

struct NameComponent
{
	NameComponent(std::string_view name) : name(name)
	{
	}
	std::string name{};
};

struct TransformComponent
{
	Transform transform{};
};
struct ColorComponent
{
	ns::Vec4 color;
};

struct GeometryComponent
{
	std::unique_ptr<Geometry> geometry{};
};

template <typename T>
struct InstancingComponent
{
	InstancingComponent(int instancingIdx, T& mat) : instancingIdx(instancingIdx), material(mat)
	{
	}
	int instancingIdx;
	T& material;
};

enum class TargetAnimationType 
{
	None,
	Linear,
	Overshoot,
};

struct SimpleTargetAnimationProp
{
 	float overshootFactor{1.70158};
};

template <typename T>
struct SimpleTargetAnimationComponent
{
	SimpleTargetAnimationComponent(TargetAnimationType animType, const T& source, const T& dest, float duration, const SimpleTargetAnimationProp& targetProp={}) 
	: animType(animType), source(source), dest(dest), duration(duration), targetProp(targetProp)
	{
		totalTime = 0.0f;
	}

	T Lerp(float deltaTime)
	{
		totalTime += deltaTime;
		float t = std::clamp(totalTime/duration, 0.0f, 1.0f);

		if (animType == TargetAnimationType::Overshoot)
			t = Interpolation::EaseOutBack(t, targetProp.overshootFactor);

		return Interpolation::Lerp(source, dest, t);
	}
	void reset()
	{
		totalTime = 0.0f;
	}
	T source;
	T dest;
	float duration{1.0f};
	TargetAnimationType animType{TargetAnimationType::Linear};
	float totalTime{0.0f};
	SimpleTargetAnimationProp targetProp{};
};

struct CameraComponent
{
	Camera camera{};
};

struct UpdateComponent
{
};

}	 // namespace ns

#endif