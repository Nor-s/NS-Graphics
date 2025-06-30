#include "cube.h"
#include <core/entity/component/component.h>
#include <core/entity/component/geometryComponent.h>

namespace vst
{

Cube::Cube()
{
    addComponent<ns::GeometryComponent>();
}

}	 // namespace vst