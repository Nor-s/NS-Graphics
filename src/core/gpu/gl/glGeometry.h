#ifndef _NS_GRAPHICS_CORE_GPU_GL_GL_GEOMETRY_H_
#define _NS_GRAPHICS_CORE_GPU_GL_GL_GEOMETRY_H_

#include "../geometry.h"
#include "glBuffer.h"

namespace ns
{

class GlGeometry: public Geometry
{
public:
    GlGeometry() = default;
    ~GlGeometry() = default;
    virtual void init(const GeometryInfo& info, const Layouts& layouts, const InstancingLayout& instancingLayout = {}) override;
    virtual void updateInstancingBuffer() override;
    GlMeshBuffer* getBuffer();

private:
	std::unique_ptr<GlMeshBuffer> buffer_;
};

}	 // namespace ns

#endif